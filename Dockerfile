FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    wget \
    gnupg \
    software-properties-common \
    cmake \
    ninja-build \
    && wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && apt-add-repository "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-17 main" \
    && apt-get update \
    && apt-get install -y clang-17 lld-17 llvm-17 \
    && rm -rf /var/lib/apt/lists/*

RUN ln -s /usr/bin/clang-17 /usr/bin/clang && \
    ln -s /usr/bin/clang++-17 /usr/bin/clang++ && \
    ln -s /usr/bin/clang-17 /usr/bin/clang-cl && \
    ln -s /usr/bin/lld-link-17 /usr/bin/lld-link && \
    ln -s /usr/bin/llvm-ml-17 /usr/bin/llvm-ml && \
    ln -s /usr/bin/llvm-rc-17 /usr/bin/llvm-rc && \
    ln -s /usr/bin/llvm-mt-17 /usr/bin/llvm-mt && \
    ln -s /usr/bin/llvm-ar-17 /usr/bin/llvm-lib

WORKDIR /workspace

# We will mount the source code and msvc_env into /workspace when we run the container
CMD ["/bin/bash", "-c", "cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -DCMAKE_BUILD_TYPE=Debug && cmake --build build"]