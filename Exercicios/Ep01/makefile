flags_compilacao = -Wall -O3 -mavx -march=native -lm
nomePrograma = exe1

all: $(nomePrograma)

$(nomePrograma): main.o floatType.o
	gcc -o $(nomePrograma) main.o floatType.o $(flags_compilacao)

floatType.o: floatType.c 
	gcc -c floatType.c $(flags_compilacao)

main.o: main.c 
	gcc -c main.c $(flags_compilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)