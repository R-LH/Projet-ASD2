#ifndef WORLD
#define WORLD

#include <vector>
#include "Bureau.h"
#include "parametres.h"

class World {
private:
    unsigned int temps; // Temps discret écoulé depuis le début de la simulation
    std::string tracefile; // Le nom du fichier qui contiendra la trace d'exécution
    std::string trace; // La trace d'exécution
    std::vector<Electeur*> population; // La population du monde
    Electeur* liste_candidats[NB_CANDIDATS]; // La liste des candidats se présentant
    Bureau bureau; // Le bureau de vote dans lequel se déroule la simulation

public:
    // Getters
    unsigned int get_time();
    std::string get_tracefile();
    unsigned int position_candidat(Electeur* candidat);
    std::string custom_float_trunc(std::string in_str, unsigned int decimals);

    // Setters
    void choisir_president(Electeur* e);
    // Précondition : candidats.size() == NB_CANDIDATS
    void se_presentent(std::vector<unsigned int> candidats);

    // Actions
    // Précondition : candidat appartient à this->liste_candidats
    void bourrer_les_urnes(Electeur* candidat, unsigned int quantite);

    // Simulation
    std::string tick_tock_goes_the_clock();
    void demarrer_simulation();

    // Constructeur et destructeur
    World(std::string tracefile);
    World();
    ~World();
};

#endif
