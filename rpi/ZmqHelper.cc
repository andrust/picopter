#include "ZmqHelper.h"

zmq::socket_t ZmqHelper::create(zmq::socket_type t) {
    return zmq::socket_t(zmqCtx(), t);
}

ZmqHelper::~ZmqHelper() {
    zmqCtx().close();
}

zmq::context_t& ZmqHelper::zmqCtx() {
    static zmq::context_t ctx(1);
    return ctx;
}

