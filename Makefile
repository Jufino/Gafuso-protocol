C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

all:protocol 

lib: libtime.o libspec.o gafuso.o libserial.o libopencv.o libfile.o gpio.o

test:test.cpp
	$(CPP) test.cpp libtime.o libspec.o gafuso.o libserial.o gpio.o -o test $(OFLAGS)

protocol:protocol.cpp
	$(CPP) protocol.cpp libtime.o libspec.o gafuso.o libserial.o gpio.o -o protocol $(OFLAGS)

test:test.cpp
	$(CPP) test.cpp libtime.o gafuso.o -o test $(OFLAGS)

onlykamera: onlykamera.cpp
	$(CPP) onlykamera.cpp libtime.o gafuso.o libopencv.o libfile.o -o onlykamera $(OFLAGS)

test_ciara: test_ciara.cpp
	$(CPP) test_ciara.cpp libtime.o gafuso.o libopencv.o libfile.o -o test_ciara $(OFLAGS)

ciara: ciara.cpp
	$(CPP) ciara.cpp libtime.o gafuso.o libopencv.o libfile.o libserial.o  -o ciara $(OFLAGS)

libtime.o: libtime.c
	$(CPP) -c libtime.c

libspec.o: libspec.c
	$(CPP) -c libspec.c

gafuso.o: gafuso.c
	$(CPP) -c gafuso.c

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
	rm gafuso.o
	rm libserial.o
	rm libopencv.o
	rm libfile.o 
	rm gpio.o

remove:
	rm protocol.o

