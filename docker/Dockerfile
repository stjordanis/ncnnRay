ARG EMSCRIPTEN_VERSION=1.38.40
FROM trzeci/emscripten:sdk-tag-${EMSCRIPTEN_VERSION}-64bit as emscripten_base

# ------------------------------------------------------------------------------
# Entries in this section is required to move Emscripten SDK to another base image

# Any arbitrary base image of choice
FROM ubuntu:bionic

# Source /emsdk_portable contains every emscripten tool.
# It's not recommended to change destination path
COPY --from=emscripten_base /emsdk_portable /emsdk_portable

# Fallback in case Emscripten isn't activated.
# This will let use tools offered by this image inside other Docker images (sub-stages) or with custom / no entrypoint
ENV EMSDK /emsdk_portable
ENV EMSCRIPTEN=${EMSDK}/emscripten/sdk

ENV EM_DATA ${EMSDK}/.data
ENV EM_CONFIG ${EMSDK}/.emscripten
ENV EM_CACHE ${EM_DATA}/cache
ENV EM_PORTS ${EM_DATA}/ports

# Fallback in case Emscripten isn't activated
# Expose Major tools to system PATH, so that emcc, node, asm2wasm etc can be used without activation
ENV PATH="${EMSDK}:${EMSDK}/emscripten/sdk:${EMSDK}/llvm/clang/bin:${EMSDK}/node/current/bin:${EMSDK}/binaryen/bin:${PATH}"

# Use entrypoint that's coming from emscripten-slim image. It sets all required system paths and variables
ENTRYPOINT ["/emsdk_portable/entrypoint"]

# ------------------------------------------------------------------------------
# This section contain an arbitrary code for image customization

RUN echo "Start emscripten-ubuntu compilation" \
    &&  echo "## Create a standard user: emscripten:emscripten" \
    &&  groupadd --gid 1000 emscripten \
    &&  useradd --uid 1000 --gid emscripten --shell /bin/bash --create-home emscripten \
    \
    &&  echo "## Update and install packages" \
    &&  apt-get -qq -y update && apt-get -qq install -y --no-install-recommends \
        wget \
        git-core \
        ca-certificates \
        build-essential \
        python \
        python-pip \
        python3 \
        python3-pip \
        wget \
        curl \
        zip \
        unzip \
        git \
        ssh-client \
        ca-certificates \
        build-essential \
        make \
        cmake \
        ant \
&&  echo "\n## Done"

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Copy this Dockerimage into image, so that it will be possible to recreate it later
COPY Dockerfile /emsdk_portable/dockerfiles/trzeci/emscripten-ubuntu/

# ------------------------------------------------------------------------------

RUN apt-get update \
 && apt-get install -y \
    sudo git bash \
    build-essential git gfortran \
    cmake curl wget unzip libreadline-dev libjpeg-dev libpng-dev ncurses-dev \
    imagemagick gnuplot gnuplot-x11 libssl-dev libzmq3-dev graphviz \
    autoconf automake build-essential libass-dev libtool  pkg-config texinfo zlib1g-dev cmake mercurial \
    libjpeg-dev libpng-dev libtiff-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libx265-dev libnuma-dev libatlas-base-dev libopus-dev libvpx-dev gfortran unzip

# Install CMake 3.14
RUN apt-get purge -y cmake


ARG CMAKE=cmake-3.17.1.tar.gz
RUN wget https://github.com/Kitware/CMake/releases/download/v3.17.1/${CMAKE}
RUN tar xvzf ${CMAKE} && cd cmake* && ./bootstrap --parallel=$(nproc)
RUN cd cmake* && make -j$(nproc) && make install

RUN ln -s /usr/local/share/cmake-3.17/ /usr/bin/cmake

EXPOSE 6006 3838 8787 8888 8786 9786 8788 5432 8000 7800 9999 7842 22 3122

WORKDIR /src

RUN apt-get update \
 && apt-get install -y nano htop libx11-dev libgl1-mesa-dev libglu1-mesa-dev libjack0 libjack-dev libasound2-dev libgtk2.0-dev xorg-dev

