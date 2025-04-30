FROM docker.io/antmicro/renode:latest

USER root
RUN apt-get update && apt install --no-install-recommends git socat mono-runtime libmono-2.0-1 mono-devel -y && rm -rf /var/lib/apt/lists/*
USER developer

RUN pip install 'pyrenode3[all] @ git+https://github.com/antmicro/pyrenode3.git@70e493c881bf317983953479961ae1b2482e351a'

WORKDIR /glitch-emulator
COPY ./glitch-emulator ./

EXPOSE 3100

ENV PARALLEL_RENODE_INSTANCES=1

CMD ["/bin/sh", "startup.sh"]
