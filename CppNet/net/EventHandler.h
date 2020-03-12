#ifndef HEADER_NET_EVENTHANDLER
#define HEADER_NET_EVENTHANDLER

#include <memory>
#include <atomic>

#include "CppDefine.h"
#include "SocketImpl.h"
#include "AcceptSocket.h"
#include "PoolSharedPtr.h"

#define INVALID_TIMER   -1

namespace cppnet {
    enum EVENT_FLAG {
        EVENT_READ          = 0x0001,        //read event
        EVENT_WRITE         = 0x0002,        //write event
        EVENT_ACCEPT        = 0x0004,        //accept event
        EVENT_TIMER         = 0x0008,        //timer event
        EVENT_CONNECT       = 0x0010,        //connect event
        EVENT_DISCONNECT    = 0x0020,        //disconnect event

        EVENT_TIMER_ALWAYS  = 0x0040,       //timer always check

        ERR_CONNECT_BREAK   = 0x0080,       //connect break
        ERR_CONNECT_FAILED  = 0x0100,       //connect faild
        ERR_CONNECT_CLOSE   = 0x0200,       //connect close
        ERR_TIME_OUT        = 0x0400,       //time out

        EVENT_ERR_MAX       = 0x0800        //max event flag define
    };

    class Cevent {
    public:
        void*                        _data = nullptr;
        int                          _event_flag_set = 0;
    };

    struct CTimerEvent {
        int                         _event_flag;
        uint64_t                    _timer_id;
        unsigned int                _interval;
        void*                       _timer_param;
        std::function<void(void*)>  _timer_call_back;   // only timer event
        base::CMemWeakPtr<CEventHandler>  _event;
    };

    class CBuffer;
    class CEventHandler : public Cevent {
    public:
        base::CMemSharePtr<base::CBuffer>    _buffer;
        base::CMemWeakPtr<CSocketImpl>       _client_socket;
        int                                  _off_set;                //read or write size
    };

    class CAcceptEventHandler : public Cevent {
    public:
        base::CMemSharePtr<CSocketImpl>      _client_socket;
        base::CMemSharePtr<CAcceptSocket>    _accept_socket = nullptr;
    };
}

#endif