PROGRAM = qm
FILES.c = main.c qm.c
FILES.h = qm.h
FILES.o = $(FILES.c:.c=.o)
FLAGS = -c -o


all: $(PROGRAM)

$(PROGRAM): $(FILES.o)
	gcc -o $@ $(FILES.o)
	
main.o: main.c $(FILES.h)
	gcc $(FLAGS) main.o main.c

qm.o: qm.c $(FILES.h)
	gcc $(FLAGS) qm.o qm.c

clean:
	rm *.o; rm $(PROGRAM)