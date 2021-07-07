#HEADERS = read-file.cpp
EXEPATH=bin

##CC=gcc
#CC=clang-7
#FLAGS=-ggdb -std=c11 -pedantic

#all:
	#${CC} ${FLAGS} -c run.c
	#${CC} ${FLAGS} -c inc.c
	#${CC} ${FLAGS} -o run run.o inc.o

#clang:
	#clang read-file.cpp -o $(EXEPATH)/readfile -ggdb -Wall -std=c++17 -lm -lstdc++

default: 
	gcc read-file.cpp -o $(EXEPATH)/readfile -ggdb -Wall -std=c++17 -lm -lstdc++ -pedantic
	#strip readfile

#program.o: program.c $(HEADERS)
#program.o: program.c
	#gcc -c read-file.cpp -o program.o

#readfile: readfile.o
	#gcc readfile.o -o readfile -ggdb -Wall -std=c++17 -lm -lstdc++

#clean:
	#-rm -f program.o
	#-rm -f program

#clean:
	#rm -f *.c *.o all
