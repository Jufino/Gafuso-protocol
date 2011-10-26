C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

TARGET=protocol

protocol: protocol.cpp
	$(CPP) protocol.cpp -o protocol $(OFLAGS)

test_serial: test_serial.cpp
	$(CPP) test_serial.cpp -o test_serial $(OFLAGS)

all: $(TARGET)
	@echo "All done"

