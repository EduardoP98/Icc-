flags_compilacao = -Wall -O3 -mavx -march=native -lm -DLIKWID_PERFMON -llikwid #-g
nomePrograma = perfEG

all: $(nomePrograma)

$(nomePrograma): main.o sistema_linear.o utils.o
	gcc -o $(nomePrograma) main.o sistema_linear.o utils.o $(flags_compilacao) -I/usr/include -L/usr/lib

sistema_linear.o: sistema_linear.c 
	gcc -c sistema_linear.c $(flags_compilacao) -I/usr/include -L/usr/lib

main.o: main.c 
	gcc -c main.c $(flags_compilacao) -I/usr/include -L/usr/lib

utils.o: utils.c 
	gcc -c utils.c $(flags_compilacao) -I/usr/include -L/usr/lib

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
		@rm -f *.o *.gch $(nomePrograma)
		@echo "Limpando tudo ..."
		