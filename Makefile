CPP=$(CROSS_COMPILE)g++ -Wall -g
OFLAGS=`pkg-config --libs --cflags opencv`

all:gafuso send_gafuso recv_gafuso camera_gafuso

send_gafuso:send_gafuso.cpp
	$(CPP) send_gafuso.cpp gafuso.o -o send_gafuso $(OFLAGS)

recv_gafuso:recv_gafuso.cpp
	$(CPP) recv_gafuso.cpp gafuso.o -o recv_gafuso $(OFLAGS)

camera_gafuso: camera_gafuso.cpp
	$(CPP) camera_gafuso.cpp gafuso.o -o camera_gafuso $(OFLAGS)

gafuso: gafuso.c
	$(CPP) -c gafuso.c $(OFLAGS)

remove:
	rm gafuso.o
