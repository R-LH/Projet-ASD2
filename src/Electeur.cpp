#include "Electeur.h"

// Constructeurs et destructeur
Electeur::Electeur(std::string nom, std::string prenom, unsigned int pos_social, unsigned int pos_eco)
    : Personne (nom, prenom) { // Appel au constructeur de la super classe
    for (unsigned int i = 0 ; i < sizeof(this->a_bulletin_de) ; i++) {
        this->a_bulletin_de[i] = false;
    }
    this->pos_social = pos_social;
    this->pos_eco = pos_eco;
}

Electeur::Electeur(unsigned int pos_social, unsigned int pos_eco) {
    Electeur("M", "karl", pos_social, pos_eco); // Identité par défaut
}

Electeur::Electeur() {
    Electeur(1, 1); // Position politique par défaut
}

Electeur::~Electeur() {}

// Getters
std::string Electeur::get_identite() {return this->nom() + " " + this->prenom();}
bool Electeur::get_a_bulletin_de(unsigned int i) {return this->a_bulletin_de[i];}
unsigned int Electeur::get_pos_social() {return this->pos_social;}
unsigned int Electeur::get_pos_eco() {return this->pos_eco;}
unsigned int Electeur::get_enveloppe() {return this->enveloppe;}
unsigned int Electeur::get_chronometre() {return this->chronometre;}

// Setters
void Electeur::set_chronometre(unsigned int temps) {this->chronometre = temps;}
void Electeur::decrement_time() {if (this->chronometre > 0) this->chronometre--;}

// Simulation
// ------------------------
// Donne la distance de l'électeur à un candidat sur le plan politique
float Electeur::distance_politique_a(Electeur* candidat) {
    unsigned int a = this->pos_social - candidat->get_pos_social();
    unsigned int b = this->pos_eco - candidat->get_pos_eco();
    return sqrt(a*a + b*b);
}

// ------------------------
// Prend quelques bulletins parmi ceux disponibles
std::string Electeur::prendre_bulletins(unsigned int* qtt_bulletins, Electeur** liste_candidats) {
    std::string trace = "";
    unsigned int qtt_prise = 0;
    for (unsigned int i = 0; i < NB_CANDIDATS; i++) {
        // S'il reste des bulletins et que le candidat nous plaît, on prend un bulletin
        if (qtt_bulletins[i] > 0 && this->distance_politique_a(liste_candidats[i]) < D_POL) {
            if (qtt_prise < 3) { // On ne prend pas non plus un bulletin de chaque candidat...
                trace += "\n        " + this->get_identite() + " prend " + liste_candidats[i]->get_identite();
                this->a_bulletin_de[i] = true;
                qtt_prise ++;
            }
        }
    }
    // Si on n'en a pas pris assez, on en prend d'autres au hasard
    while (qtt_prise < QTT_BULLETINS_MIN) {
        int choix = RAND.rand_btw(0, NB_CANDIDATS-1);
        // On n'avait pas encore pris de bulletin pour ce candidat
        if (!this->get_a_bulletin_de(choix)) {
            trace += "\n        " + this->get_identite() + " prend " + liste_candidats[choix]->get_identite();
            this->a_bulletin_de[choix] = true;
            qtt_prise++;
        }
    }
    trace += "\n        " + this->get_identite() + " prend BLANC";
    this->a_bulletin_de[NB_BULLETINS - 2] = true;
    return trace;
}

// ------------------------
// Retourne la trace des évènements
std::string Electeur::choisir_bulletin(Electeur** candidats) {
    std::string trace = "";
    // Il y a une probabilité pour que l'électeur vote blanc ou nul
    double tirage = RAND.percentage();
    if (tirage < P_NUL) { // Vote nul
        trace += "\n        " + this->get_identite() + " choisit NUL";
        this->enveloppe = NB_CANDIDATS + 1;
    } else {
        tirage -= P_NUL;
        if (tirage < P_BLANC) { // Vote blanc
            trace += "\n        " + this->get_identite() + " choisit BLANC";
            this->enveloppe = NB_CANDIDATS;
        } else {
            // On recherche quel candidat est le plus proche de la position politique de l'électeur
            unsigned int choix = NB_CANDIDATS - 1; // Choix par défaut
            float dist_choix = D_POL;
            float current_dist;
            for (unsigned int i = 0; i < NB_CANDIDATS; i++) {
                if (this->get_a_bulletin_de(i)) { // Si l'électeur a un bulletin du i-ème candidat
                    current_dist = this->distance_politique_a(candidats[i]);
                    if (current_dist < dist_choix && current_dist < D_POL) {
                        choix = i;
                        dist_choix = current_dist;
                    }
                }
            }
            trace += "\n        " + this->get_identite() + " choisit " + candidats[choix]->get_identite();
            this->enveloppe = choix;
        }
    }
    return trace;
}
