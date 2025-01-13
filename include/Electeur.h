#ifndef ELECTEUR
#define ELECTEUR

#include <cmath> // Pour utiliser sqrt()
#include <string>
#include "Personne.h"
#include "Random.h"
#include "parametres.h"

class Electeur: public elections::Personne {
private:
    bool a_bulletin_de[NB_BULLETINS]; // Si la personne possède un bulletin du i-ème candidat
    unsigned int pos_social; // Position politique sociale [1 : libertaire -> 10 : autoritaire]
    unsigned int pos_eco; // Position politique économique [1 : socialiste -> 10 : capitaliste]
    unsigned int enveloppe; // Contiendra le vote de l'électeur
    unsigned int chronometre; // Pour garder le compte des durées

public:
    // Getters
    std::string get_identite();
    bool get_a_bulletin_de(unsigned int i);
    unsigned int get_pos_social();
    unsigned int get_pos_eco();
    unsigned int get_enveloppe();
    unsigned int get_chronometre();

    // Setters
    void set_chronometre(unsigned int temps);
    void decrement_time();

    // Simulation
    float distance_politique_a(Electeur* candidat);
    std::string prendre_bulletins(unsigned int* qtt_bulletins, Electeur** liste_candidats);
    std::string choisir_bulletin(Electeur** candidats);

    // Constructeurs et destructeur
    Electeur(std::string nom, std::string prenom, unsigned int pos_social, unsigned int pos_eco);
    Electeur(unsigned int pos_social, unsigned int pos_eco);
    Electeur();
    ~Electeur();
};

#endif
