FROM ubuntu:noble

SHELL ["/bin/bash", "-c"]

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y --no-install-recommends install \
            git build-essential cmake gpg gpg-agent dirmngr software-properties-common && \
    echo "deb http://packages.gobysoft.org/ubuntu/release/ noble/" >> /etc/apt/sources.list.d/gobysoft_release.list && \
    apt-key adv --recv-key --keyserver keyserver.ubuntu.com 19478082E2F8D3FE && \
    apt-add-repository ppa:tes/lamss-moos10 && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && \
    apt-get install -y dccl4-apps python3-dccl4 python3-rich protobuf-compiler dccl4-compiler libdccl4-dev libmoos10-dev moos10-essential screen goby3-moos moosdb10 moos-ivp-apps psmisc && \
    rm -rf /var/lib/apt/lists/*

RUN cd /opt && git clone https://github.com/GobySoft/moos-dawg-24.git
