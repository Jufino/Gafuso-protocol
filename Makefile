C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

all:protocol 

lib: libtime.o libspec.o libprotocol.o libsocket.o libserial.o libopencv.o libfile.o gpio.o

protocol: protocol.cpp
	$(CPP) protocol.cpp libtime.o libspec.o libprotocol.o libsocket.o libserial.o gpio.o -o protocol $(OFLAGS)

kamera: kamera.cpp
	$(CPP) kamera.cpp libtime.o libprotocol.o libsocket.o libopencv.o libfile.o -o kamera $(OFLAGS)

onlykamera: onlykamera.cpp
	$(CPP) onlykamera.cpp libtime.o libprotocol.o libsocket.o libopencv.o libfile.o -o onlykamera $(OFLAGS)

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

gpio.o: gpio.c
	$(CPP) -c gpio.c

remove_lib:
	rm libtime.o
	rm libspec.o
	rm libprotocol.o
	rm libsocket.o
	rm libserial.o
	rm libopencv.o
	rm libfile.o 
	rm gpio.o

remove:
	rm protocol.o

