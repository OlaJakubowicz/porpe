CC = g++
LIBS          = -L/opt/local/lib/ -lboost_thread-mt
INCLUDE       = -I/opt/local/include   
OPTS          = -o
CLASS_BUILD   = -c
DEBUG         = -Wall -g
FREAKING_SHIT = -ansi
HITLER_FLAG   = --pedantic
FILEZ         = main.cpp Server.cpp ../lib/Socket.cpp WorkerQueue.cpp

all:
	@$(CC) $(OPTS) main main.cpp Server.cpp WorkerQueue.cpp ../lib/Socket.cpp $(INCLUDE) $(LIBS)
	@cp main ../bin/server
	@rm main
	@echo "Build"
	
here:
	$(CC) $(OPTS) main $(FILEZ) $(FREAKING_SHIT)
	
holy_shit:
	$(CC) $(OPTS) main $(FILEZ) $(FREAKING_SHIT) $(HITLER_FLAG)
	
clean:
	@rm *.o
	@echo "Cleaned"

