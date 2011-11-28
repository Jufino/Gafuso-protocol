C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

all:protocol 

lib: libtime.o libspec.o libprotocol.o libsocket.o libserial.o libopencv.o libfile.o

protocol: protocol.cpp
	$(CPP) protocol.cpp -o protocol libtime.o libspec.o libprotocol.o libsocket.o libserial.o $(OFLAGS)

kamera:

libtime.o: libtime.c
	$(CPP) -c libtime.c

libspec.o: libspec.c
	$(CPP) -c libspec.c

libprotocol.o: libprotocol.c
	$(CPP) -c libprotocol.c

libsocket.o: libsocket.c
	$(CPP) -c libsocket.c $(OFLAGS)

libserial.o: libserial.c
	$(CPP) -c libserial.c

libopencv.o: libopencv.c
	$(CPP) -c libopencv.c $(OFLAGS)

libfile.o: libfile.c
	$(CPP) -c libfile.c

remove_lib:
	rm libtime.o
	rm libspec.o
	rm libprotocol.o
	rm libsocket.o
	rm libserial.o
	rm libopencv.o
	rm libfile.o 

remove:
	rm protocol.o

