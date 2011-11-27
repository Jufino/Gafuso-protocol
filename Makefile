C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

TARGET=protocol

protocol: protocol.cpp
	$(CPP) protocol.cpp -o protocol $(OFLAGS)

example: example.cpp
	$(CPP) example.cpp -o example $(OFLAGS)

example1: example1.cpp
	$(CPP) example1.cpp -o example1 $(OFLAGS)

test_serial1: testserial1.cpp
	$(CPP) test_serial1.cpp -o test_serial1 $(OFLAGS)

test_serial: test_serial.cpp
	$(CPP) test_serial.cpp -o test_serial $(OFLAGS)

kamera: kamera.cpp
	$(CPP) kamera.cpp -o kamera $(OFLAGS)

protocolTest: protocolTest.cpp
	$(CPP) protocolTest.cpp -o protocolTest -fno-stack-protector  $(OFLAGS) 

all: $(TARGET)
	@echo "All done"

