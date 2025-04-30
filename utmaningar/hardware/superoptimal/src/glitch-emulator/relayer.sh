#!/bin/sh

# The main purpose of this script is to make sure that users
# may take their time filling in the parameters without
# blocking valuable computation resources. The heavy framefork
# is not started until the socat connection is made. It also
# makes sure the user gets some response that their connection
# to the server is working even though the service has built
# up an internal queue.

echo "[IMPORTANT]  Please. Do not spam or script connections!"

# Define the address and port of the socat listener
HOST="127.0.0.1"
PORT="4000"

# Create temporary named pipes for communication
IN_PIPE=$(mktemp -u)
mkfifo "$IN_PIPE"
OUT_PIPE=$(mktemp -u)
mkfifo "$OUT_PIPE"

# Strings to send to the listener
DELAY="1000"
PASSWORD="password"

# Ask for user input
echo -n "[powerglove] Enter the delay as number of instructions: "
read -p "" DELAY
echo -n "[powerglove] Enter the password: "
read -p "" PASSWORD

# Verify the inputs
if [ ${DELAY} -gt 100000 ]; then
  echo "[powerglove] Delay too long. Maximum 100000. Exiting..."
  exit 1
fi
if [ ${#PASSWORD} -gt 32 ]; then
  echo "[powerglove] Password too long. Maximum 32 characters. Exiting..."
  exit 1
fi

# Connecting an idle writer to the pipes so other writes don't cause EOFs
sleep 1000 >"$IN_PIPE" &
SLEEP_PID=$!

# Start socat connection and link it to the named pipes for input/output
echo "[powerglove] Trying to connect to glitcher module..."
socat - TCP4:$HOST:$PORT <"$IN_PIPE" >"$OUT_PIPE" &
SOCAT_PID=$!

# Write the delay and password to the named pipe
printf "%s\n" "$DELAY" >"$IN_PIPE"
printf "%s\n" "$PASSWORD" >"$IN_PIPE"

# Read all output until connection closes
cat <"$OUT_PIPE"

# Cleanup
kill $SOCAT_PID 2>/dev/null
kill $SLEEP_PID 2>/dev/null
rm "$IN_PIPE" "$OUT_PIPE"

# Exit
exit 0
