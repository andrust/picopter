#!/usr/bin/env python

import zmq
from telemetry_pb2 import TelemetryRecord

def serializer(buf):
    return rec


def main():
    s = zmq.Context.instance().socket(zmq.SUB)
    s.connect("tcp://192.168.0.137:2000")
    s.set(zmq.SUBSCRIBE, "")
    while True:
        buf = s.recv()
        rec = TelemetryRecord()
        rec.ParseFromString(buf)
        print "Received ts: %lu, roll: %li, pitch: %li, yaw: %li" % (rec.timestamp, rec.roll, rec.pitch, rec.yaw)
        print rec.timestamp

if __name__ == "__main__":
    main()
