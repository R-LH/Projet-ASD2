#include <cassert>
#include <iostream>
#include "Bureau.h"

// Constructeurs
Bureau::Bureau(
        Electeur** liste_candidats,
        Electeur* president,
        unsigned int bulletins_par_candidat,
        unsigned int numero) {
    this->liste_candidats = liste_candidats;
    this->isoloirs = Isoloirs();
    this->president = president;
    // On initialise l'urne et la quantité de bulletins sur la table de décharge
    unsigned int i;
    for (i = 0; i < NB_BULLETINS; i++) {
        this->qtt_bulletins[i] = bulletins_par_candidat;
        this->urne[i] = 0;
    }
    for (i = 0; i < NB_ISOLOIRS; i++) {
        this->registre_isoloirs[i] = false;
    }
    for (i = 0; i < sizeof(this->tables)/sizeof(espace); i++) {
        this->tables[i].est_libre = true;
    }
    // Aucun bulletin nul de disponible sur la table de décharge
    this->qtt_bulletins[sizeof(this->qtt_bulletins)/sizeof(unsigned int)] = 0;
    this->files = {
        FileElecteurs(10), // 0: Avant la table de décharge (arrivée des électeurs)
        FileElecteurs(10), // 1: Avant les isoloirs
        FileElecteurs(10) // 2: Avant la table de vote
    };
    this->liste_el_em = Elect_Emarge();
    this->est_ouvert = true;
    this->nb_pers_inside = 0;
    this->numero = numero;
}

Bureau::Bureau(Electeur** liste_candidats, Electeur* president) {
    Bureau(liste_candidats, president, 5, 258);
}

Bureau::Bureau() {}

// Destructeur
Bureau::~Bureau() {
}

// Getters
unsigned int Bureau::get_qtt_bulletins(int i) {return this->qtt_bulletins[i];}
Electeur* Bureau::get_president() {return this->president;}
bool Bureau::a_vote(Electeur* e) {return this->liste_el_em.a_vote(e);}
Elect_Emarge* Bureau::get_liste_el_em() {return &this->liste_el_em;}
bool Bureau::get_est_ouvert() {return this->est_ouvert;}
unsigned int Bureau::get_nb_pers() {return this->nb_pers_inside;}
unsigned int Bureau::get_numero() {return this->numero;}
unsigned int* Bureau::get_urne() {return this->urne;}
unsigned int Bureau::get_resultat(unsigned int i) {return this->urne[i];}

// Setters
void Bureau::initialiser_qtt_bulletins(unsigned int i, unsigned int number) {if (i <= NB_CANDIDATS) this->qtt_bulletins[i] = number;}
void Bureau::placer_president(Electeur* president) {this->president = president;}
void Bureau::forcer_urne(unsigned int i, unsigned int quantite) {if (i < NB_BULLETINS) this->urne[id_candidat] += quantite;}
void Bureau::faire_voter(Electeur* e) {this->urne[e->get_enveloppe()] += 1;}
void Bureau::faire_entrer(Electeur* e) {
    if (RAND.percentage() >= P_ABS) {
        this->files[0].ajouter(e);
        if(DBUG_ACTIVE) std::cout << e->get_identite() << " ajouté\n";
    }
}

// Simulation
//NOTE/ Chaque espace considère la première personne de chaque file comme étant
// dans l'espace (les premières personnes pour les isoloirs)
std::string Bureau::gerer_tick(unsigned int temps) {
    std::string trace = "";
    trace += this->gerer_decharge();
    trace += this->gerer_isoloirs();
    trace += this->gerer_vote();
    // Ceux qui arrivent juste à temps peuvent tout de même rentrer
    if (temps == Tmax) {
        trace += "\n    FERMETURE ENTRÉE";
        this->est_ouvert = false;
    }
    return trace;
}

std::string Bureau::gerer_decharge() {
    std::string trace = "";
    // S'il y a un électeur et que celui-ci a atteint le temps limite dans l'espace de décharge
    if (!this->tables[0].est_libre && this->tables[0].electeur->get_chronometre() == 0) {
        trace += "\n    DÉCHARGE";
        trace += "\n        " + this->tables[0].electeur->get_identite() + " sort";
        // L'électeur va dans la file d'attente pour les isoloirs
        this->files[1].ajouter(this->tables[0].electeur);
        this->tables[0].est_libre = true;
    }
    if (this->tables[0].est_libre && this->est_ouvert) {
        if (this->files[0].get_occupation() > 0) trace += "\n    ENTRÉE";
        // Tant que la personne suivante n'est pas inscrite sur les listes électorales, elle est écartée
        while (this->files[0].get_occupation() > 0 && !this->liste_el_em.est_electeur(this->files[0].get_first())) {
            trace += "\n        " + this->files[0].extraire()->get_identite() + " est refusé(e)";
        }
        // S'il reste des personnes dans la file et que le bureau est ouvert, l'électeur
        // suivant est admis dans l'espace de décharge et choisit plusieurs bulletins
        if (this->files[0].get_occupation() > 0) {
            this->tables[0].electeur = this->files[0].extraire();
            this->tables[0].est_libre = false;
            this->tables[0].electeur->set_chronometre(Dd);
            trace += "\n        " + this->tables[0].electeur->get_identite() + " entre";
            trace += "\n    DÉCHARGE";
            trace += "\n        " + this->tables[0].electeur->get_identite() + " entre";
            this->nb_pers_inside++;
            trace += this->tables[0].electeur->prendre_bulletins(this->qtt_bulletins, this->liste_candidats);
        }
    }
    if (DBUG_ACTIVE) std::cout
    << "\n    NB_PERS = " << this->nb_pers_inside
    << "\n    D = " << !this->tables[0].est_libre; //DBUG/
    return trace;
}

std::string Bureau::gerer_isoloirs() {
    std::string trace = "";
    bool en_tete_affiche = false;
    // Sortent de l'isoloir ceux qui y sont resté Di ticks
    for (unsigned int i = 0; i < NB_ISOLOIRS; i++) {
        if (this->registre_isoloirs[i] && this->isoloirs.get_pers_at(i)->get_chronometre() == 0) {
            if (!en_tete_affiche) {
                trace += "\n    ISOLOIRS";
                en_tete_affiche = true;
            }
            trace += "\n        " + this->isoloirs.get_pers_at(i)->get_identite() + " sort";
            this->files[2].ajouter(this->isoloirs.enlever_pers(i));
            this->registre_isoloirs[i] = false;
        }
    }
    // Rentrent ensuite les électeurs qui attendent devant, sous réserve d'isoloirs disponibles
    int token;
    if (!en_tete_affiche && this->files[1].get_occupation() > 0) trace += "\n    ISOLOIRS";
    while (this->files[1].get_occupation() > 0 && this->isoloirs.get_occ() < NB_ISOLOIRS) {
        token = this->isoloirs.ajouter_pers(this->files[1].extraire());
        trace += "\n        " + this->isoloirs.get_pers_at(token)->get_identite() + " entre";
        trace += this->isoloirs.get_pers_at(token)->choisir_bulletin(this->liste_candidats);
        this->isoloirs.get_pers_at(token)->set_chronometre(Di);
        this->registre_isoloirs[token] = true;
    }
    if (DBUG_ACTIVE) {
        std::cout << "\n    R = ["; //DBUG/
        for (unsigned int i=0;i<NB_ISOLOIRS-1;i++) std::cout << this->isoloirs.get_routeur(i) << ", ";
        std::cout << this->isoloirs.get_routeur(NB_ISOLOIRS-1) << "]";
        std::cout << "\n    T = ["; //DBUG/
        for (unsigned int i=0;i<NB_ISOLOIRS-1;i++) std::cout << this->isoloirs.get_tokens(i) << ", ";
        std::cout << this->isoloirs.get_tokens(NB_ISOLOIRS-1) << "]";
        std::cout << "\n    I = ["; //DBUG/
        for (unsigned int i=0;i<NB_ISOLOIRS-1;i++) std::cout << this->registre_isoloirs[i] << ", ";
        std::cout << this->registre_isoloirs[NB_ISOLOIRS-1] << "]";

    }
    return trace;
}

std::string Bureau::gerer_vote() {
    std::string trace = "";
    // S'il y a un électeur et que celui-ci a atteint le temps limite à la table de vote
    if (!this->tables[1].est_libre && this->tables[1].electeur->get_chronometre() == 0) {
        // L'électeur sort du bureau
        trace += "\n    SORTIE";
        trace += "\n        " + this->tables[1].electeur->get_identite() + " sort";
        this->tables[1].est_libre = true;
        this->nb_pers_inside--;
    }
    // On fait entrer l'électeur suivant
    /* /TODO/
    * vérifier présence président
    */
    if (this->tables[1].est_libre && this->files[2].get_occupation() > 0) {
        this->tables[1].electeur = this->files[2].extraire();
        this->tables[1].est_libre = false;
        this->tables[1].electeur->set_chronometre(Dv);
        trace += "\n    VOTE";
        trace += "\n        " + this->tables[1].electeur->get_identite() + " a voté";
        this->faire_voter(this->tables[1].electeur);
        this->liste_el_em.emarger(this->tables[1].electeur);
    }
    if (DBUG_ACTIVE) std::cout << "\n    V = " << !this->tables[1].est_libre << std::endl; //DBUG/
    return trace;
}
