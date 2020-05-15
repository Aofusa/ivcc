FROM ubuntu:20.04
RUN apt update && apt -y install --no-install-recommends \
    gcc make git binutils libc6-dev \
    && apt clean \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /root
CMD ["/bin/bash"]