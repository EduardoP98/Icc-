flags_compilacao = -Wall -O3 -mavx -march=native -lm #-g
nomePrograma = perfEG

all: $(nomePrograma)

$(nomePrograma): main.o sistema_linear.o calc_time.o
	gcc -o $(nomePrograma) main.o sistema_linear.o calc_time.o $(flags_compilacao)

sistema_linear.o: sistema_linear.c 
	gcc -c sistema_linear.c $(flags_compilacao)

main.o: main.c 
	gcc -c main.c $(flags_compilacao)

calc_time.o: calc_time.c 
	gcc -c calc_time.c $(flags_compilacao)

purge:
	rm -f *.o *.gch $(nomePrograma)