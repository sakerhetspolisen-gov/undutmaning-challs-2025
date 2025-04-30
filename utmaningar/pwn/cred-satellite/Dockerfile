FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y qemu-system-x86 qemu-utils socat cpio gzip curl xinetd

RUN useradd -m ctf
WORKDIR /home/ctf

# Copy hosting files
COPY ./host/ctf.xinetd /etc/xinetd.d/ctf
COPY ./host/banner_fail /etc/banner_fail
COPY ./host/start.sh ./start.sh

# Copy challenge files
COPY ./src/* /home/ctf/
# Default all files to read only
RUN chown -R root:ctf /home/ctf
RUN chmod 644 *
# Make scripts executable
RUN chmod +x *.sh
# Allow repacking of filesystem
RUN chmod 666 ./initramfs.cpio.gz

EXPOSE 31341

CMD ./start.sh
