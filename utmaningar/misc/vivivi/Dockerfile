FROM alpine:edge@sha256:f4b9f111e2c5290552a920590dd48dc58f5ea1cacda6e25b0a2718974d090cf0

RUN apk update && \
	apk add shadow python3 neovim py3-pynvim socat

# neovim 0.10.2
WORKDIR /ctf
RUN useradd -M -d /ctf/ ctf

WORKDIR /ctf
COPY levels /ctf/levels
COPY a.py /ctf/
RUN chown -R ctf:ctf /ctf/ && chmod -R 750 /ctf
USER ctf

EXPOSE 4711

CMD ["/usr/bin/socat", "-T600", "TCP-LISTEN:4711,reuseaddr,fork", "EXEC:'python3 a.py'"]


