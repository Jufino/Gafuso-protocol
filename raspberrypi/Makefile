CPP=$(CROSS_COMPILE)g++ -Wall -g
TARGET=gafuso

exampleClient:exampleSendClient exampleRecvClient
exampleServer:exampleSendServer exampleRecvServer

gafuso:gafuso.c
	$(CPP) -c gafuso.c $(OFLAGS)

install: $(TARGET)
	$(CROSS_COMPILE)ar rcs lib$(TARGET).a $(TARGET).o
	install lib$(TARGET).a /usr/lib/lib$(TARGET).a
	install *.h /usr/include/
	rm lib$(TARGET).a
	rm $(TARGET).o

clean:
	rm /usr/lib/lib$(TARGET).a
	rm /usr/include/$(TARGET).h

exampleSendServer:exampleSendServer.cpp
	$(CPP) exampleSendServer.cpp -lgafuso -o exampleSendServer

exampleSendClient:exampleSendClient.cpp
	$(CPP) exampleSendClient.cpp -lgafuso -o exampleSendClient

exampleRecvServer:exampleRecvServer.cpp
	$(CPP) exampleRecvServer.cpp -lgafuso -o exampleRecvServer

exampleRecvClient:exampleRecvClient.cpp
	$(CPP) exampleRecvCli`:ent.cpp -lgafuso -o exampleRecvClient

