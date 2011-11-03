C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

TARGET=protocol

protocol: protocol.cpp
	$(CPP) protocol.cpp -o protocol $(OFLAGS)

protocol1: protocol1.cpp
	$(CPP) protocol1.cpp -o protocol1 $(OFLAGS)

test_serial1: test_serial1.cpp
	$(CPP) test_serial1.cpp -o test_serial1 $(OFLAGS)

test_serial: test_serial.cpp
	$(CPP) test_serial.cpp -o test_serial $(OFLAGS)

kamera: kamera.cpp
	$(CPP) kamera.cpp -o kamera $(OFLAGS)

all: $(TARGET)
	@echo "All done"

