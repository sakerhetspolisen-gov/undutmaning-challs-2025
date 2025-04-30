FROM python:3.13-slim-bookworm
RUN apt update
RUN apt install -y socat
RUN pip install numpy
RUN pip install scipy
EXPOSE 3000
COPY src src
WORKDIR /src
CMD ["/bin/sh", "serve.sh"]
