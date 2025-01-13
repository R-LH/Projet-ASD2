#ifndef ISOLOIRS
#define ISOLOIRS

#include "Electeur.h"
#include "parametres.h"

class Isoloirs {
private:
    unsigned int occ;
    unsigned int routeur[NB_ISOLOIRS];
    unsigned int tokens[NB_ISOLOIRS];
    Electeur* couloir[NB_ISOLOIRS]; // On considère un isoloir comme un pointeur vers un Electeur
public:
    // Getters
    unsigned int get_occ();
    Electeur* get_pers_at(int token);
    unsigned int get_routeur(unsigned int i);
    unsigned int get_tokens(unsigned int i);

    // Actions
    int ajouter_pers(Electeur* electeur); // Renvoie le token de l'isoloir
    // Précondition : token < NB_ISOLOIRS
    Electeur* enlever_pers(unsigned int token); // Renvoie l'adresse de l'électeur

    // Constructeur et destructeur
    Isoloirs();
    ~Isoloirs();
};

#endif
