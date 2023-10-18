all:main

main:main.o complex.o
	g++ main.o complex.o -o main
main.o:main.cpp
	g++ main.cpp -c -o main.o
complex.o:complex.cpp
	g++ complex.cpp -c -o complex.o
clean:
	rm *.o main

