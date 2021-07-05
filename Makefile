#HEADERS = read-file.cpp

default: 
	gcc read-file.cpp -o readfile -ggdb -Wall -std=c++17 -lm -lstdc++
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
