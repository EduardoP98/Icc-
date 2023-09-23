# PROGRAMA
PROG = interpola

# Compilador
CC = gcc

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

# Opção de depuração (pode ser definida externamente ou deixada em branco para desativar)
DEBUG ?=

ifeq ($(DEBUG),yes)
    debug_flags = -g -DDEBUG
else
    debug_flags =
endif

flags_compilacao = -Wall -O3 -mavx -march=native -lm -DLIKWID_PERFMON -llikwid $(debug_flags)

all: $(PROG)

$(PROG): main.o interpolacao_pol.o utils.o
	$(CC) -o $(PROG) main.o interpolacao_pol.o utils.o $(flags_compilacao) -I/usr/include -L/usr/lib

main.o: main.c
	$(CC) -c main.c $(flags_compilacao)

interpolacao_pol.o: interpolacao_pol.c
	$(CC) -c interpolacao_pol.c $(flags_compilacao) -I/usr/include -L/usr/lib

utils.o: utils.c
	$(CC) -c utils.c $(flags_compilacao) -I/usr/include -L/usr/lib

.PHONY: all clean purge dist

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge: clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
