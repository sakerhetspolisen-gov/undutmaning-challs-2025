#!/bin/sh
socat -T600 TCP-LISTEN:3100,reuseaddr,fork EXEC:"python3 relayer.py"
