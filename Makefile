# Ceci est un Makefile automatique co-créé par Eichodea
# Commandes disponibles :
#   make        lance la compilation
#   make all    idem
#   make clean  nettoie le répertoire

# --------------------
#     DÉCLARATIONS
# --------------------

# Compilateur g++ pour le C++
CC = g++

# Options du compilateur
#   -g          insère des informations de déboguage dans l'exécutable
#   -Wall       affiche tous les warnings lors de la compilation
#   -std=c++14  impose la norme C++14 du langage
CFLAGS = -g -Wall -std=c++14

# Chemins des différents fichiers à inclure à la compilation
#   > Changer les noms selon l'organisation du projet
#   ./
#    ├── include/
#    │    └── *.h
#    ├── src/
#    │    └── *.cpp
#    ├── obj/
#    │    └── *.o
#    └── Makefile
INC_DIR  = include
SRC_DIR  = src
OBJ_DIR  = obj
INCLUDES = -I$(INC_DIR)

# Programme exécutable
TARGET = main

# Fichiers issus de la compilation composant le programme exécutable
#   > on appelle les .o des fichiers objets, ils contiennent le code
#     exécutable des opérations dans les fichiers sources (.cpp) associés
#   > on crée pour chaque fichier source un fichier objet du même nom
OBJ = $(shell ls $(SRC_DIR)/*.cpp | awk -F'[/.]' '{print "$(OBJ_DIR)/"$$(NF-1)".o"}')

# ---------------
#     ACTIONS
# ---------------

# La cible (ou les cibles s'il y en a plusieurs)
#   ./$(TARGET) pour exécuter le programme
all: check_obj \
	$(TARGET);

# Vérification de l'existence du répertoire objet
check_obj:
	@if [ ! -d "$(OBJ_DIR)/" ]; then \
		echo "Creating $(OBJ_DIR)/ directory..."; \
		mkdir $(OBJ_DIR); \
	fi;

# Génération de l'exécutable (édition de liens)
#   > sur la première ligne on a la cible (main) suivie de ":" suivie
#     de la dépendance (liste de fichiers), ce qui signifie que si un fichier
#     objet est modifié alors le programme exécutable sera généré à nouveau
#   > sur la troisième ligne on a l'instruction de compilation
#	> "@" devant les commandes désactive leur affichage dans la console,
#     un seul par bloc est suffisant
#	> "\" exécute toutes les commandes en une seule fois, fortement recommandé
#   > il DOIT y avoir une tabulation ou plusieurs en début de ligne
$(TARGET): $(OBJ)
	@echo "Building links..."; \
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET); \
	echo "-- Finished --";

# Compilation de main.cpp générant le fichier objet main.o
#   > sur la première ligne on a la cible (main.o) suivie de ":" suivie
#     de la dépendance (liste de fichiers), ce qui signifie que si on modifie
#     main.cpp ou un autre fichier alors le fichier main.cpp sera compilé à nouveau
#   > sur la deuxième ligne on a l'instruction de compilation
#   > il DOIT y avoir une tabulation ou plusieurs en début de ligne
$(OBJ_DIR)/$(TARGET).o: $(SRC_DIR)/$(TARGET).cpp
	@echo "Compiling $(SRC_DIR)/$(TARGET).cpp..."; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/$(TARGET).cpp -o $(OBJ_DIR)/$(TARGET).o;

# Compilation de tous les codes sources et génération des fichiers objets
#   > "%" groupe les noms des fichiers correspondants au pattern
#     "$*" permet de les lire un par un
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	@echo "Compiling $(SRC_DIR)/$*.cpp..."; \
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$*.o $(INCLUDES) -c $(SRC_DIR)/$*.cpp;

# Cible pour nettoyer le répertoire du projet
#   > sur la première ligne on vérifie si le répertoire objet
#     et la cible existent, si non on les supprime
clean:
	@if [ ! -d "$(OBJ_DIR)/" ] && [ ! -f "$(TARGET)" ]; then \
		echo "No files were to clean"; \
	else \
		echo "Cleaning files..."; \
		if [ -d "$(OBJ_DIR)/" ]; then \
			rm -f $(OBJ_DIR)/*.o; \
			rmdir $(OBJ_DIR); \
		fi; \
		if [ -f "$(TARGET)" ]; then \
			rm -f $(TARGET); \
		fi; \
		echo "-- Finished --"; \
	fi;
