FROM ubuntu:26.04

RUN apt-get update && apt-get install -y curl \
    xz-utils build-essential g++ make && \
    apt-get clean