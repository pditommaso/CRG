FROM pditommaso/dkrbase
MAINTAINER Maria Chatzou <mxatzou@gmail.com>

RUN apt-get update --fix-missing && apt-get install -y libboost-all-dev

#RUN apt-get install -y git
#RUN git clone https://mariach@bitbucket.org/mariach/mega2.git

RUN apt-get install -y cmake

ADD src /mega/src
ADD doc /mega/doc
RUN mkdir /mega/build
ADD tests /mega/tests
ADD CMake* /mega/
ADD testsuit /mega/testsuit
ADD Versi* /mega/
ADD Homfam /mega/Homfam
ADD clustal-omega-1.2.0 /mega/clustal-omega-1.2.0

RUN cd mega/clustal-omega-1.2.0 && ./configure CFLAGS='-I/mega/clustal-omega-1.2.0/argtable2-13/include/' LDFLAGS='-L/mega/clustal-omega-1.2.0/argtable2-13/lib/' && make
RUN echo "alias clustalo='/mega/clustal-omega-1.2.0/src/clustalo'" >> ~/.bashrc

RUN cd mega/src/lib/HHalign/lib/ffindex/ && make clean && make
RUN cd mega/src/lib/HHalign/src && make clean && make NO_PNG=1
RUN export HHLIB="/mega/src/lib/HHalign"
RUN cd mega/build/ && cmake .. && make tea && make msaa
