FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential libjpeg-dev clang

COPY . /repo
WORKDIR /repo
RUN ./configure --prefix=/install
RUN make -j8
RUN make install
RUN clang++ /repo/mayhem/fuzz_delete_file.cpp -fsanitize=fuzzer,address misc.o -o /fuzz

FROM ubuntu:20.04 as package
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libjpeg-dev
COPY --from=builder /install /install
COPY --from=builder /fuzz /fuzz_delete_file
