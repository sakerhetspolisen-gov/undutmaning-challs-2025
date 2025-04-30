FROM python:3.13-slim-bookworm
RUN apt update
RUN apt install -y socat
RUN pip install pycryptodome
EXPOSE 3003
COPY src src
WORKDIR /src
CMD ["socat", "-T600", "TCP-LISTEN:3003,reuseaddr,fork", "EXEC:python3 algebra_challenge.py"]
