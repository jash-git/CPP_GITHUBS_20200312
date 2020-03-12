#ifdef __linux__

#include <unistd.h>
#include <sys/socket.h>

#include "CNConfig.h"
#include "SocketBase.h"
#include "MemoryPool.h"
#include "EventActions.h"

using namespace cppnet;

CSocketBase::CSocketBase() : _add_event_actions(false), _event_actions(nullptr), 
                             _pool(new base::CMemoryPool(__mem_block_size, __mem_block_add_step)) {
    memset(_ip, 0, __addr_str_len);
}

CSocketBase::CSocketBase(std::shared_ptr<CEventActions>& event_actions) : _add_event_actions(false), _event_actions(event_actions), 
                             _pool(new base::CMemoryPool(__mem_block_size, __mem_block_add_step)) {
    memset(_ip, 0, __addr_str_len);
}

CSocketBase::~CSocketBase() {
    close(_sock);
}
#endif // __linux__
