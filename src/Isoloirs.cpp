#include "Isoloirs.h"

// Constructeur
Isoloirs::Isoloirs() {
    this->occ = 0;
    for (unsigned int i = 0 ; i < NB_ISOLOIRS ; i++) {
        this->tokens[i] = i;
        this->routeur[i] = i;
    }
}

// Destructeur
Isoloirs::~Isoloirs() {}

// Getters
unsigned int Isoloirs::get_occ() {return this->occ;}
Electeur* Isoloirs::get_pers_at(int token) {return this->couloir[this->routeur[token]];}
unsigned int Isoloirs::get_routeur(unsigned int i) {return this->routeur[i];}
unsigned int Isoloirs::get_tokens(unsigned int i) {return this->tokens[i];}

// Actions
int Isoloirs::ajouter_pers(Electeur* electeur) {
    int token;
    if (this->occ == NB_ISOLOIRS) {
        token = -1; // Aucun isloir de libre
    } else {
        token = this->tokens[this->occ]; // Le numéro de l'isoloir
        this->couloir[this->occ] = electeur;
        this->occ++;
    }
    return token;
}

Electeur* Isoloirs::enlever_pers(unsigned int token) {
    this->occ--;
    // Variables
    unsigned int cle_token = this->routeur[token];
    Electeur* electeur = this->couloir[cle_token];
    unsigned int token_dernier = this->tokens[this->occ];
    // On déplace le dernier id dans l'espace de celui qui part
    this->couloir[cle_token] = this->couloir[this->occ];
    // On échange les deux tokens correspondants
    this->tokens[this->occ] = token;
    this->tokens[cle_token] = token_dernier;
    // On échange les clés correspondant aux tokens
    this->routeur[token] = this->routeur[token_dernier];
    this->routeur[token_dernier] = cle_token;
    // On retourne l'adresse de l'électeur parti
    return electeur;
}
