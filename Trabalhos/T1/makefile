flags_compilacao = -Wall -O3 -mavx -march=native -lm #-DDEBUG  #-g#-DLIKWID_PERFMON -llikwid #-g
nomePrograma = ajustePol

all: $(nomePrograma)

$(nomePrograma): main.o sistema_linear.o utils.o tabela.o min_quadrados.o doubleType.o interval.o
	gcc -o $(nomePrograma) main.o sistema_linear.o utils.o tabela.o min_quadrados.o doubleType.o interval.o $(flags_compilacao) -I/usr/include -L/usr/lib

sistema_linear.o: sistema_linear.c 
	gcc -c sistema_linear.c $(flags_compilacao) -I/usr/include -L/usr/lib

main.o: main.c
	gcc -c main.c $(flags_compilacao) -I/usr/include -L/usr/lib

utils.o: utils.c 
	gcc -c utils.c $(flags_compilacao) -I/usr/include -L/usr/lib

tabela.o: tabela.c 
	gcc -c tabela.c $(flags_compilacao) -I/usr/include -L/usr/lib

min_quadrados.o: min_quadrados.c
	gcc -c min_quadrados.c $(flags_compilacao) -I/usr/include -L/usr/lib

doubleType.o: doubleType.c
	gcc -c doubleType.c $(flags_compilacao) -I/usr/include -L/usr/lib

interval.o: interval.c
	gcc -c interval.c $(flags_compilacao) -I/usr/include -L/usr/lib

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
		@rm -f *.o *.gch $(nomePrograma)
		@echo "Limpando tudo ..."
		