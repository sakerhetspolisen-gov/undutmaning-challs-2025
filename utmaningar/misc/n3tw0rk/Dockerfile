# Build the binaries in a separate container
FROM debian:bookworm-slim AS build-env
COPY build /build
WORKDIR /build

RUN apt-get update && apt-get install -y gcc make bison libjson-c-dev pkg-config
RUN make clean
RUN make MUD_LIB=/mud/lib BINDIR=/mud/bin

WORKDIR /build/util
RUN make

# Create the actual game container (without the build stuff)
FROM debian:bookworm-slim

# Install dependencies and fix locale settings
RUN apt-get update && apt-get install -y locales libjson-c5 && rm -rf /var/lib/apt/lists/* \
	&& localedef -i en_US -c -f ISO-8859-1 -A /usr/share/locale/locale.alias en_US.ISO-8859-1 \
    && apt-get clean
ENV LANG=en_US.ISO-8859-1

# Create and set up the user that will run the game process
RUN adduser --disabled-password --gecos "" mud
USER mud

WORKDIR /mud

# Copy the game binaries into the game container
COPY --from=build-env --chown=mud:mud /build/driver /mud/bin/driver
COPY --from=build-env --chown=mud:mud /build/util/hname /mud/bin/hname
RUN chmod a+x /mud/bin/driver /mud/bin/hname
COPY --chown=mud:mud ./lib /mud/lib

# Expose the game port
EXPOSE 3011

# Start the game
CMD ["/mud/bin/driver","-N"]