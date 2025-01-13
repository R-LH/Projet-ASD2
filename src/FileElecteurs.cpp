#include <cstring> // Pour utiliser memcpy
#include "FileElecteurs.h"

//MORE/ utiliser listes chaînées ?

// Constructeurs et destructeur
FileElecteurs::FileElecteurs(unsigned int taille) {
    this->capa = taille;
    this->occ = 0;
    this->premier = 0;
}

FileElecteurs::FileElecteurs() {
    FileElecteurs(10); // Valeur arbitraire
}

FileElecteurs::~FileElecteurs() {}

// Getters
Electeur* FileElecteurs::get_first() {
    return this->contenu[this->premier];
}

Electeur* FileElecteurs::get_at_pos(unsigned int indice) {
    return this->contenu[this->premier + indice];
}

unsigned int FileElecteurs::get_occupation() {return this->occ;}

// Actions
void FileElecteurs::ajouter(Electeur* electeur) {
    if (occ == capa) this->agrandir();
    this->contenu[(this->premier + this->occ) % this->capa] = electeur;
    this->occ++;
}

void FileElecteurs::agrandir() {
    const unsigned int longueur = this->capa * 2;
    Electeur* new_contenu[longueur];
    this->capa = longueur;

    // Recopie de l'ancien contenu dans le nouveau tableau, à partir de 0
    memcpy(new_contenu, this->contenu, sizeof(this->contenu) * sizeof(int));
    for (unsigned int i = 0 ; i < longueur ; i++) {
        new_contenu[i] = this->contenu[(this->premier + i) % this->capa];
    }
    this->premier = 0;
}

Electeur* FileElecteurs::extraire() {
    Electeur* electeur_sortant = this->contenu[this->premier];
    this->premier = (this->premier + 1) % this->capa;
    this->occ--;
    return electeur_sortant;
}
