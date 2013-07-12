C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

lib: gafuso.o 

send_gafuso:send_gafuso.cpp
	$(CPP) send_gafuso.cpp gafuso.o -o send_gafuso $(OFLAGS)

recv_gafuso:recv_gafuso.cpp
	$(CPP) recv_gafuso.cpp gafuso.o -o recv_gafuso $(OFLAGS)

camera_gafuso: camera_gafuso.cpp
	$(CPP) camera_gafuso.cpp gafuso.o -o camera_gafuso $(OFLAGS)

gafuso.o: gafuso.c
	$(CPP) -c gafuso.c $(OFLAGS)

remove_lib:
	rm gafuso.o
