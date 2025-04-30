FROM alpine:edge AS build

RUN apk update
RUN apk add build-base gawk zip bmake
RUN cp /usr/bin/bmake /usr/bin/make

WORKDIR /tmp/smalltalk-3.2.5/
COPY smalltalk-3.2.5.tar.xz /tmp/
RUN tar -xf /tmp/smalltalk-3.2.5.tar.xz -C /tmp/
RUN ./configure CFLAGS='-static -D__GNU_LIBRARY__=1 -D__va_copy=va_copy -Wno-incompatible-pointer'
RUN make -k LDFLAGS='-static' || true
RUN mkdir /ctf/ && cp -r gst kernel gst.im /ctf/

FROM alpine:edge

WORKDIR /ctf/

RUN apk add socat
COPY download/server.st flag.txt /ctf/
COPY --from=build /ctf/ /ctf/
RUN chown 405:405 flag.txt

USER 405
EXPOSE 9723
ENTRYPOINT []
CMD ["socat", "-T600", "TCP-LISTEN:9723,reuseaddr,fork", "EXEC:./gst server.st"]
