FROM ubuntu:22.04
WORKDIR /home/ns-3-dev

ENV TZ=America/Sao_Paulo \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y git build-essential libboost-all-dev pybind11-dev cmake sqlite sqlite3 libsqlite3-dev protobuf-compiler python3 python3-pip doxygen sphinx
RUN git clone https://gitlab.com/nsnam/ns-3-dev.git -l /home/ns-3-dev
RUN git -C /home/ns-3-dev/ checkout -b ns-3.40 ns-3.40
RUN git clone https://github.com/felip-T/ns3-oran /home/ns-3-dev/contrib/oran
RUN git clone https://github.com/felip-T/ns3-ai /home/ns-3-dev/contrib/ai
RUN pip install gymnasium stable_baselines3
RUN cp /home/ns-3-dev/contrib/oran/setupDocker.sh /home/ns-3-dev/
RUN cp /home/ns-3-dev/contrib/oran/run-rl-handover-example.sh /home/ns-3-dev/

