#!/usr/bin/env python3
import sys


def detect_packet(message: str, packet_lenght: int):
    for i in range(len(message)):
        if len(set(message[i : i + packet_lenght])) == packet_lenght:
            return i + packet_lenght


with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    f = f.read()
    print(detect_packet(f, 4))
    print(detect_packet(f, 14))
