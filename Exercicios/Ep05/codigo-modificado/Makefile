nomePrograma = integration

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

flags_compilacao = -Wall -O3 -mavx -march=native -lm $(debug_flags)

all: $(nomePrograma)

$(nomePrograma): labMonteCarlo.o utils.o
	$(CC) -o $(nomePrograma) labMonteCarlo.o utils.o $(flags_compilacao)

labMonteCarlo.o: labMonteCarlo.c
	$(CC) -c labMonteCarlo.c $(flags_compilacao)

utils.o: utils.c
	$(CC) -c utils.c $(flags_compilacao)

.PHONY: all clean purge dist

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge: clean
	@echo "Limpando tudo ..."
	@rm -f $(nomePrograma) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(nomePrograma) $(DISTDIR)
