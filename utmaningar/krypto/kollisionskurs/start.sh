#!/bin/sh

# Start our fake /proc/uptime creator
/uptime_helper &

python app.py