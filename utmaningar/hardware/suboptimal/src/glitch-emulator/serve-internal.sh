#!/bin/sh
socat -T600 TCP-LISTEN:4000,reuseaddr,max-children=3,backlog=20,fork EXEC:"python3 glitch-emulator.py"
