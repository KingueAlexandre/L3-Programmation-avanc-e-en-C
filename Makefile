FLAGS = -Wall -ansi -pedantic

all:
	make mytee
	make exo2
	make ppcm
	man fprintf | ./mytee doc.log | wc -l
	./exo2 24 2
	./ppcm 12 34 54 72 28 72 81 18 26
	gprof ./ppcm gmon.out

mytee: mytee.c
	gcc -o mytee mytee.c $(FLAGS) 

exo2: exo2.c
	gcc -o exo2 exo2.c $(FLAGS) 

ppcm: ppcm.c
	gcc -o ppcm ppcm.c $(FLAGS) -pg

clean:
	rm*. o
	rm  exe
