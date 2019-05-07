proj645: main.o processor.o traceParse.o
	g++ -g -std=c++11 -Wall main.o processor.o traceParse.o -o proj645

main.o: main.cpp processor.h processor.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

processor.o: processor.h processor.cpp
	g++ -g -std=c++11 -Wall -c processor.cpp

traceParse.o: traceParse.h traceParse.cpp
	g++ -g -std=c++11 -Wall -c traceParse.cpp

clean:
	rm *.o proj645