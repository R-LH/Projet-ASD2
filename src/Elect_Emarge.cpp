#include <string>
#include "Elect_Emarge.h"

Elect_Emarge::Elect_Emarge() {
    std::set<emargement, CompBeta> liste_vide; // initialisation d'un set vide
    this->liste = liste_vide;
}

Elect_Emarge::~Elect_Emarge() {}

// ------------------------
// Getter
// Retourne la taille de la liste électorale d'émargement
unsigned int Elect_Emarge::get_size() {return this->liste.size();}

// ------------------------
// Retourne vrai si e existe dans la liste
bool Elect_Emarge::contains(emargement e) {
    return this->liste.count(e) > 0;
}

// ------------------------
// Vérifie qu'une personne est inscrite
// Complexité temporelle : O(log(n))
bool Elect_Emarge::est_electeur(Electeur* electeur) {
    emargement a,b;
    a.electeur = electeur;
    a.a_vote = true;
    b.electeur = electeur;
    b.a_vote = false;
    return this->contains(a) || this->contains(b);
}

// ------------------------
// Inscrit toutes les personnes présentes dans population dans la
// liste électorale d'émargement
void Elect_Emarge::initialiser(std::vector<Electeur*> population) {
    emargement e;
    for (unsigned int i = 0; i < population.size(); i++) {
        e.electeur = population[i];
        e.a_vote = false;
        this->liste.insert(e);
    }
}

// ------------------------
// Insère la personne passée en paramètre dans la liste électorale
// Complexité temporelle : O(log(n))
void Elect_Emarge::inserer(Electeur* electeur) {
    emargement e;
    e.a_vote = false;
    e.electeur = electeur;
    //On évite les doublons
    if(!this->est_electeur(electeur)){
        this->liste.insert(e);
    }
}

// ------------------------
// Complexité temporelle : O(log(n))
bool Elect_Emarge::a_vote(Electeur* electeur) {
    emargement e;
    e.a_vote = true;
    e.electeur = electeur;
    return this->contains(e);
};

// ------------------------
// Permet à un électeur de ne pas voter 2 fois de suite en mettant
// à jour l'état de son enregistrement emargement
void Elect_Emarge::emarger(Electeur* electeur) {
    emargement e;
    e.a_vote = false;
    e.electeur = electeur;
    this->liste.erase(e);
    e.a_vote = true;
    this->liste.insert(e);
};

// ------------------------
// Affiche tous les électeurs inscrits de la liste
std::string Elect_Emarge::afficher() {
    std::string trace = "";
    unsigned int i = 0;
    for (auto it = begin(this->liste); it != end(this->liste); it++) {
        trace += "\n    " + (*it).electeur->get_identite() + " (" + std::to_string(i) + ")";
        i++;
    }
    return trace;
}
