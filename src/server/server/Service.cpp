#include "../server.h"
#include <iostream>
using namespace server;
using namespace std;

Service::Service () {
}

HttpStatus Service::get (Json::Value& out, int id) const {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}

HttpStatus Service::post (const Json::Value& in, int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}

HttpStatus Service::put (Json::Value& out, const Json::Value& in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}

HttpStatus Service::remove (int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not implemented");
}
