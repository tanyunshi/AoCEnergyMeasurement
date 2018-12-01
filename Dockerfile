FROM ubuntu
RUN apt-get update && apt-get install -y g++ \
            git \
            cmake \
            python3
