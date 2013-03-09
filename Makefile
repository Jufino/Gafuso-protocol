C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

all:protocol 

lib: gafuso.o libserial.o libopencv.o

send_gafuso:send_gafuso.cpp
	$(CPP) send_gafuso.cpp gafuso.o libserial.o -o send_gafuso $(OFLAGS)

protocol:protocol.cpp
	$(CPP) protocol.cpp gafuso.o libserial.o -o protocol $(OFLAGS)

onlykamera: onlykamera.cpp
	$(CPP) onlykamera.cpp gafuso.o libopencv.o -o onlykamera $(OFLAGS)

test_ciara: test_ciara.cpp
	$(CPP) test_ciara.cpp gafuso.o libopencv.o -o test_ciara $(OFLAGS)

ciara: ciara.cpp
	$(CPP) ciara.cpp gafuso.o libopencv.o libserial.o  -o ciara $(OFLAGS)

gafuso.o: gafuso.c
	$(CPP) -c gafuso.c $(OFLAGS)

libserial.o: libserial.c
	$(CPP) -c libserial.c

libopencv.o: libopencv.c
	$(CPP) -c libopencv.c $(OFLAGS)

remove_lib:
	rm gafuso.o
	rm libserial.o
	rm libopencv.o
