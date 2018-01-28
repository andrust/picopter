#pragma once

#include <zmq.hpp>

class ZmqHelper {
public:
    static zmq::socket_t create(zmq::socket_type t);
    ZmqHelper() = default;
    ~ZmqHelper();

private:
    static zmq::context_t& zmqCtx();
};
