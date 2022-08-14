FROM ubuntu:jammy

LABEL maintainer="Masaya Sato <sato.masaya.dev@gmail.com>"
LABEL version="1.0"
LABEL description="The minimal image for C/C++ projects."

RUN DEBIAN_FRONTEND=noninteractive \
    apt update -y && \
    apt install --no-install-recommends -y gcc g++ clang make gdb valgrind git binutils libc6-dev sudo
RUN adduser --disabled-password --gecos '' jammy
RUN echo 'jammy ALL=(root) NOPASSWD:ALL' > /etc/sudoers.d/jammy

USER jammy

WORKDIR /home/jammy
