FROM ubuntu:22.04

# Install build dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    libjpeg-dev

# Copy source code
COPY . /app

# Build the project
RUN cd /app && mkdir build && cd build && \
cmake .. && make
