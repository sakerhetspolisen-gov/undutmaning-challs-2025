FROM debian:bookworm-slim AS build-env

RUN apt-get update && apt-get install -y gcc make 

COPY status /status
WORKDIR /status

RUN make 

COPY uptime_helper /uptime_helper
WORKDIR /uptime_helper

RUN make

FROM python:3.10-slim

RUN apt-get update && apt-get -y upgrade && apt-get clean

RUN pip install flask

RUN useradd -m ctf
WORKDIR /home/ctf

RUN mkdir -p /home/ctf/jail/home/ops

# Libraries
RUN cp -R /usr/lib* /home/ctf/jail

# Let the ctf player have access to some common devices
RUN mkdir /home/ctf/jail/dev && \
    mknod /home/ctf/jail/dev/null c 1 3 && \
    mknod /home/ctf/jail/dev/zero c 1 5 && \
    mknod /home/ctf/jail/dev/random c 1 8 && \
    mknod /home/ctf/jail/dev/urandom c 1 9 && \
    chmod 666 /home/ctf/jail/dev/*

# Let the ctf player have access to some common programs
RUN mkdir /home/ctf/jail/bin && \
    cp /bin/sh /home/ctf/jail/bin && \
    cp /bin/ls /home/ctf/jail/bin && \
    cp /bin/pwd /home/ctf/jail/bin && \
    cp /bin/cat /home/ctf/jail/bin

RUN mkdir -p /home/ctf/jail/usr/bin && \
    cp /usr/bin/id /home/ctf/jail/usr/bin

# Skapa bilbioteket för vår fejk uptime
RUN mkdir -p /home/ctf/jail/proc && \
    touch /home/ctf/jail/proc/uptime

COPY uppdragsparametrar.json /home/ctf/jail/home/ops/

# Fixa rättigheter på hela trädet
RUN chown -R root:ctf /home/ctf/jail && \
    chmod -R 550 /home/ctf/jail

COPY --from=build-env --chown=1000:1000 /status/status /home/ctf/jail/home/ops/status    
COPY --from=build-env --chown=1000:1000 /uptime_helper/uptime_helper /uptime_helper

RUN chmod +x /uptime_helper && \
    chmod +x /home/ctf/jail/home/ops/status

RUN chmod 555 /home/ctf/jail/home/ops/status
RUN chown root:ctf /home/ctf/jail/home/ops/status

# Kopiera flask appen
COPY app /home/ctf/app
COPY crc16.py /home/ctf/app/crc16.py
WORKDIR /home/ctf/app

# Exponera port och starta applikationen
EXPOSE 8222

COPY start.sh /start.sh
RUN chmod +x /start.sh

CMD ["/start.sh"]
