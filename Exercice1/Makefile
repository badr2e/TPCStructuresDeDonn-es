# Nom du fichier exécutable
EXE = elmourabitexo1

# Nom du fichier binaire
BINS = saveliste

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Règle de compilation par défaut
all: $(EXE)

# Liaison
$(EXE): elmourabitlisteint.c elmourabitexo1.c
	$(CC) $(CFLAGS) -o $@ $^

# Nettoyage des fichiers binaires et de l'exécutable
clean:
	rm -f $(EXE) $(BINS) *.o
