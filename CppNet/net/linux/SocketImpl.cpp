#ifdef __linux__

#include <unistd.h>
#include <sys/uio.h>
#include <sys/epoll.h>
#include <sys/socket.h>

#include "Log.h"
#include "Buffer.h"
#include "Runnable.h"
#include "CNConfig.h"
#include "LinuxFunc.h"
#include "SocketImpl.h"
#include "CppNetImpl.h"
#include "EventHandler.h"
#include "EventActions.h"

using namespace cppnet;

CSocketImpl::CSocketImpl(std::shared_ptr<CEventActions>& event_actions) : CSocketBase(event_actions){
    _read_event = base::MakeNewSharedPtr<CEventHandler>(_pool.get());
    _write_event = base::MakeNewSharedPtr<CEventHandler>(_pool.get());

    _read_event->_data = _pool->PoolNew<epoll_event>();
    ((epoll_event*)_read_event->_data)->events = 0;
    _read_event->_buffer = base::MakeNewSharedPtr<base::CBuffer>(_pool.get(), _pool);

    _write_event->_data = _pool->PoolNew<epoll_event>();
    ((epoll_event*)_write_event->_data)->events = 0;
    _write_event->_buffer = base::MakeNewSharedPtr<base::CBuffer>(_pool.get(), _pool);
}

CSocketImpl::~CSocketImpl() {
    base::LOG_DEBUG("close a socket, socket : %d, TheadId : %lld", _sock, std::this_thread::get_id());

    if (IsInActions()) {
        _event_actions->DelEvent(_sock);
    }
    
    // release res
    if (_read_event && _read_event->_data) {
        epoll_event* temp = (epoll_event*)_read_event->_data;
        _pool->PoolDelete<epoll_event>(temp);
        _read_event->_data = nullptr;
    }
    if (_write_event && _write_event->_data) {
        epoll_event* temp = (epoll_event*)_write_event->_data;
        _pool->PoolDelete<epoll_event>(temp);
        _write_event->_data = nullptr;
    }
}

void CSocketImpl::SyncRead() {
    if (!_read_event->_client_socket) {
        _read_event->_client_socket = memshared_from_this();
    }

    if (_event_actions) {
        _read_event->_event_flag_set |= EVENT_READ;
        _event_actions->AddRecvEvent(_read_event);
    }
}

void CSocketImpl::SyncWrite(const char* src, uint32_t len) {
    if (!_write_event->_client_socket) {
        _write_event->_client_socket = memshared_from_this();
    }

    _write_event->_event_flag_set |= EVENT_WRITE;

    //can't send now
    if (_write_event->_buffer->GetCanReadLength() > 0) {
        _write_event->_buffer->Write(src, len);
        if (_event_actions) {
            _event_actions->AddSendEvent(_write_event);
        }

    } else {
        // try send now
        _write_event->_buffer->Write(src, len);
        Send(_write_event);
    }
}

void CSocketImpl::SyncConnection(const std::string& ip, uint16_t port) {
    if (ip.length() > 16) {
        base::LOG_ERROR("a wrong ip! %s", ip.c_str());
        return;
    }
    strcpy(_ip, ip.c_str());
    _port = port;

    if (!_read_event->_client_socket){
        _read_event->_client_socket = memshared_from_this();
    }

    if (_event_actions) {
        _read_event->_event_flag_set |= EVENT_CONNECT;
        _event_actions->AddConnection(_read_event, ip, port);
    }
}

void CSocketImpl::SyncDisconnection() {
    if (!_read_event->_client_socket) {
        _read_event->_client_socket = memshared_from_this();
    }

    if (_event_actions) {
        _read_event->_event_flag_set |= (EVENT_DISCONNECT | ERR_CONNECT_CLOSE);
        _event_actions->AddDisconnection(_read_event);
    }
}

void CSocketImpl::PostTask(std::function<void(void)>& func) {
    _event_actions->PostTask(func);
}

void CSocketImpl::Recv(base::CMemSharePtr<CEventHandler>& event) {
    if (!event->_client_socket) {
        base::LOG_WARN("the event with out socket");
        return;
    }
    auto socket_ptr = event->_client_socket.Lock();
    if (!socket_ptr) {
        base::LOG_WARN("the event'socket is destroyed");
        return;
    }
    int err = event->_event_flag_set;
    if (event->_event_flag_set & EVENT_TIMER) {
        err |= ERR_TIME_OUT;
        event->_event_flag_set &= ~EVENT_TIMER;

    //get a connection event
    } else if (event->_event_flag_set & EVENT_CONNECT) {
        event->_event_flag_set &= ~EVENT_CONNECT;

    } else if (event->_event_flag_set & EVENT_DISCONNECT) {
        event->_event_flag_set &= ~EVENT_DISCONNECT;

    } else {
        if (event->_event_flag_set & EVENT_READ) {
            event->_off_set = 0;
            //read all data.
            uint32_t expand_buff_len = __linux_read_buff_expand_len;
            for (;;) {
                int expand = 0;
                if (event->_buffer->GetFreeLength() == 0) {
                    expand = expand_buff_len;
                    if (expand_buff_len < __linux_read_buff_expand_max) {
                        expand_buff_len *= 2;
                    }
                }

                std::vector<base::iovec> io_vec;
                int buff_len = event->_buffer->GetFreeMemoryBlock(io_vec, expand);
                int recv_len = 0;
                recv_len = readv(socket_ptr->GetSocket(), (iovec*)&*io_vec.begin(), io_vec.size());
                if (recv_len < 0) {
                    if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR) {
                        break;

                    } else if (errno == EBADMSG || errno == ECONNRESET) {
                        err |= ERR_CONNECT_BREAK;
                        base::LOG_ERROR("recv filed! %d", errno);
                        break;

                    } else {
                        err |= ERR_CONNECT_BREAK;
                        base::LOG_ERROR("recv filed! %d", errno);
                        break;
                    }
                } else if (recv_len == 0) {
                    err |= ERR_CONNECT_CLOSE;
                    base::LOG_DEBUG("socket read 0 to close! %d", socket_ptr->GetSocket());
                    break;
                }
                event->_buffer->MoveWritePt(recv_len);
                event->_off_set += recv_len;
                // read all
                if (recv_len < buff_len) {
                    break;
                }
            }
        }
    }
    CCppNetImpl::Instance()._ReadFunction(event, err);
}

void CSocketImpl::Send(base::CMemSharePtr<CEventHandler>& event) {
    if (!event->_client_socket) {
        base::LOG_WARN("the event with out socket");
        return;
    }
    auto socket_ptr = event->_client_socket.Lock();
    if (!socket_ptr) {
        base::LOG_WARN("the event'socket is destroyed");
        return;
    }

    int err = event->_event_flag_set;
    if (event->_event_flag_set & EVENT_TIMER) {
        err |= ERR_TIME_OUT;
        event->_event_flag_set &= ~EVENT_TIMER;

    } else {
        event->_off_set = 0;
        while(event->_buffer && event->_buffer->GetCanReadLength() > 0) {
            std::vector<base::iovec> io_vec;
            int data_len = event->_buffer->GetUseMemoryBlock(io_vec, __linux_write_buff_get);
            int res = writev(socket_ptr->GetSocket(), (iovec*)&*io_vec.begin(), io_vec.size());
            if (res >= 0) {
                event->_buffer->Clear(res);
                event->_off_set += res;

            } else {
                if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR) {
                    //can't send complete
                    if (res < data_len) {
                        _event_actions->AddSendEvent(_write_event);
                    }

                } else if (errno == EBADMSG) {
                    err |= ERR_CONNECT_BREAK;
                    base::LOG_ERROR("send filed! %d", errno);
                    break;

                } else {
                    err |= ERR_CONNECT_CLOSE;
                    base::LOG_ERROR("send filed! %d", errno);
                    break;
                }
            }
        }
        CCppNetImpl::Instance()._WriteFunction(event, err);
    }
}
#endif
