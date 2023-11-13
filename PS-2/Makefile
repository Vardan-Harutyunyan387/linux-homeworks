All: interactive-shell 

interactive-shell: interactive-shell.o
	g++ interactive-shell.o -o interactive-shell

interactive-shell.o: interactive-shell.cpp
	g++ -c interactive-shell.cpp -c

clean:
	rm *.o interactive-shell *.log