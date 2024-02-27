all: signal-echo signal_sender

signal-echo: signal-echo.o 
	g++ signal-echo.o  -o signal-echo 

signal_sender: signal_sender.o 
	g++ signal_sender.o   -o signal_sender

signal-echo.o: signal-echo.cpp 
	g++ signal-echo.cpp -c -o signal-echo.o

signal_sender.o: signal_sender.cpp 
	g++ signal_sender.cpp -c -o signal_sender.o


clean:
	rm *.o signal-echo signal_sender