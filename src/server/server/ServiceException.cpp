#include "../server.h"

using namespace server;
using namespace std;

ServiceException::ServiceException (HttpStatus status, string msg)
    : msg(msg),httpStatus(status) {    
}

HttpStatus ServiceException::status () const {
    return httpStatus;
}

const char* ServiceException::what () const  {
    return msg.c_str();
}
