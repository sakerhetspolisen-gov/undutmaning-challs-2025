FROM amd64/ubuntu:22.04
RUN apt-get update && apt-get -y dist-upgrade && apt-get install -y lib32z1 xinetd

RUN useradd -m ctf

WORKDIR /home/ctf

RUN mkdir -p /home/ctf/chroot_jail/home/checklist

# Libraries
RUN cp -R /usr/lib* /home/ctf/chroot_jail

# Let the ctf player have access to some common devices
RUN mkdir /home/ctf/chroot_jail/dev && \
    mknod /home/ctf/chroot_jail/dev/null c 1 3 && \
    mknod /home/ctf/chroot_jail/dev/zero c 1 5 && \
    mknod /home/ctf/chroot_jail/dev/random c 1 8 && \
    mknod /home/ctf/chroot_jail/dev/urandom c 1 9 && \
    chmod 666 /home/ctf/chroot_jail/dev/*

# Let the ctf player have access to some common programs
RUN mkdir /home/ctf/chroot_jail/bin && \
    cp /bin/sh /home/ctf/chroot_jail/bin && \
    cp /bin/ls /home/ctf/chroot_jail/bin && \
    cp /bin/pwd /home/ctf/chroot_jail/bin && \
    cp /bin/cat /home/ctf/chroot_jail/bin

RUN mkdir -p /home/ctf/chroot_jail/usr/bin && \
    cp /usr/bin/id /home/ctf/chroot_jail/usr/bin

COPY ./ctf.xinetd /etc/xinetd.d/ctf
COPY ./start.sh /start.sh
RUN echo "Blocked by xinetd" > /etc/banner_fail

RUN chmod +x /start.sh

# Read-only for the ctf player
COPY ./run/ /home/ctf/chroot_jail/
RUN mv /home/ctf/chroot_jail/flag /home/ctf/chroot_jail/home/checklist/flag
RUN chown -R root:ctf /home/ctf/chroot_jail && \
    chmod -R 750 /home/ctf/chroot_jail && \
    chmod 444 /home/ctf/chroot_jail/home/checklist/flag

EXPOSE 31340

CMD /start.sh
