CPPFLAGS= -c -g -Iinc -Wall -pedantic -std=c++17 

__start__: clear SortApp
	./SortApp

SortApp: 
	g++ -o SortApp src/main.cpp inc/CSV.h  inc/List.h inc/ListElement.h inc/ListException.h -lpthread

clear:
	rm -f obj/*.o SortApp
