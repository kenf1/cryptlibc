FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y curl \
    xz-utils \
    build-essential \
    gcc \
    g++ \
    make \
    && apt-get clean