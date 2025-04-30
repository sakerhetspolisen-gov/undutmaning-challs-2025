FROM debian:stable-slim
RUN apt update && apt install -y socat

WORKDIR /app
COPY laskeblask .
COPY flag.txt .

EXPOSE 2048
CMD ["socat", "-T60", "TCP-LISTEN:2048,reuseaddr,fork", "EXEC:./laskeblask"]
