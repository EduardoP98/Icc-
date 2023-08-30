flags_compilacao = -Wall -O3 -mavx -march=native #-g
nomePrograma = perfEG

all: $(nomePrograma)

$(nomePrograma): main.o sistema_linear.o
	gcc -o $(nomePrograma) main.o sistema_linear.o $(flags_compilacao)

sistema_linear.o: sistema_linear.c 
	gcc -c sistema_linear.c $(flags_compilacao)

main.o: main.c 
	gcc -c main.c $(flags_compilacao)

purge:
	rm -f *.o *.gch $(nomePrograma)