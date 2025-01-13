#ifndef BUREAU
#define BUREAU

#include <vector>
#include "Isoloirs.h"
#include "FileElecteurs.h"
#include "Electeur.h"
#include "Elect_Emarge.h"
#include "parametres.h"

class Bureau {
private:
    // Un enregistrement pour tout type d'espace de base à l'intérieur du bureau
    struct espace {
        Electeur* electeur;
        bool est_libre;
    };
    // Table de décharge (1 personne à la fois)
    unsigned int qtt_bulletins[NB_BULLETINS]; // Le nombre de bulletins restants par candidat plus les bulletins blancs
    // Isoloirs
    Isoloirs isoloirs;
    bool registre_isoloirs[NB_ISOLOIRS];
    // Table de vote (1 personne à la fois)
    Electeur* president;
    // Listes
    Elect_Emarge liste_el_em;
    Electeur** liste_candidats;
    unsigned int urne[NB_BULLETINS];
    // Espaces d'attentes
    std::vector<FileElecteurs> files;
    espace tables[2]; // Une table de décharge et une de vote
    // État du bureau
    bool est_ouvert;
    unsigned int nb_pers_inside;
    unsigned int numero;

public:
    // Getters
    unsigned int get_qtt_bulletins(int i);
    Electeur* get_president();
    bool a_vote(Electeur* e);
    Elect_Emarge* get_liste_el_em();
    bool get_est_ouvert();
    unsigned int get_nb_pers();
    unsigned int get_numero();
    unsigned int* get_urne();
    unsigned int get_resultat(unsigned int i);

    // Setters
    // Initialise manuellement un nombre de bulletins pour un candidat
    // Précondition : i <= NB_CANDIDATS (on peut initialiser les bulletins blancs)
    void initialiser_qtt_bulletins(unsigned int i, unsigned int number);
    void placer_president(Electeur* president);
    // Précondition : i < NB_BULLETINS (on peut forcer les bulletins blancs et nuls)
    void forcer_urne(unsigned int i, unsigned int quantite);
    void faire_voter(Electeur* e);
    void faire_entrer(Electeur* e);

    // Simulation
    // Retournent la trace des évènements
    std::string gerer_tick(unsigned int temps);
    std::string gerer_decharge();
    std::string gerer_isoloirs();
    std::string gerer_vote();

    // Constructeurs et destructeur
    Bureau(
        Electeur** liste_candidats,
        Electeur* president,
        unsigned int bulletins_par_candidat,
        unsigned int numero);
    Bureau(Electeur** liste_candidats, Electeur* president);
    Bureau();
    ~Bureau();
};

#endif
