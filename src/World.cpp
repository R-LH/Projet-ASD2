#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "World.h"
#include "Random.h"

/* ------------------------
 * Constructeur
 */
World::World(std::string tracefile) {
    this->temps = 0;
    this->tracefile = tracefile;
    this->trace = "ELECTION '" + NOM_ELECTION + "'";

    // Initialisation de la population
    this->population = {
        new Electeur("A", "bic", 7, 3),
        new Electeur("B", "gad", 9, 1),
        new Electeur("C", "ann", 2, 10),
        new Electeur("D", "pol", 5, 9),
        new Electeur("E", "lam", 1, 1),
        new Electeur("F", "bul", 10, 9),
        new Electeur("G", "yap", 3, 4),
        new Electeur("X", "nel", 5, 5),
        new Electeur("Y", "rik", 2, 5),
        new Electeur("Z", "pat", 8, 3)
    };
    // Sélection des candidats
    std::vector<unsigned int> candidats = {0, 3, 7};
    this->se_presentent(candidats);
    // Initialisation du bureau de vote
    unsigned int bulletins_par_candidat = 5;
    this->bureau = Bureau(
        this->liste_candidats,
        this->population[2],
        bulletins_par_candidat,
        RAND.rand_btw(0, 600));
    std::string trace = "";
    trace += "\n";
    trace += "\nBUREAU n°" + std::to_string(this->bureau.get_numero());
    // Initialisation de la liste électorale avec la population
    trace += "\nLISTE ÉLECTORALE";
    this->bureau.get_liste_el_em()->initialiser(this->population);
    trace += this->bureau.get_liste_el_em()->afficher();
    // Affichage des paramètres de la simulation
    trace += "\n";
    trace += "\nPRÉPARATION DÉCHARGE";
    for (unsigned int i = 0; i < NB_CANDIDATS; i++) {
        trace += "\n    " + this->liste_candidats[i]->get_identite() + " : " + std::to_string(this->bureau.get_qtt_bulletins(i)) + " bulletins";
    }
    this->trace += trace;
    this->demarrer_simulation();
}

World::World() {}

/* ------------------------
 * Destructeur
 */
World::~World() {
   // Destruction des personnes
   for (Electeur* electeur : this->population) delete electeur;
}

/* ------------------------
 * Getter
 * Retourne le temps actuel écoulé depuis le début de la simulation
 */
unsigned int World::get_time() {return this->temps;}

/* ------------------------
 * Getter
 * Retourne le nom du fichier de trace
 */

std::string World::get_tracefile() {return this->tracefile;}

/* ------------------------
 * Getter
 * Retourne la position d'un candidat dans la liste des candidats
 */
unsigned int World::position_candidat(Electeur* candidat) {
    unsigned int i = 0;
    while (this->liste_candidats[i] != candidat && i < sizeof(this->liste_candidats)/sizeof(Electeur*)) i++;
    return i;
}

/* ------------------------
 * Getter
 * Permet de formater l'affichage d'un nombre flottant
 */
std::string World::custom_float_trunc(std::string in_str, unsigned int decimals) {
    std::string out_str = "";
    unsigned int i = 0; // Iterator
    unsigned int d = 0; // Decimal places
    while (i < in_str.size() && in_str[i] != '.') {
        out_str += in_str[i];
        i++;
    }
    if (decimals > 0) {
        out_str += '.';
        i++;
        while (i < in_str.size() && d < decimals) {
            out_str += in_str[i];
            i++; d++;
        }
    }
    return out_str;
}

/* ------------------------
 * Setter
 * Place un président à la table de vote
 */
void World::choisir_president(Electeur* e) {this->bureau.placer_president(e);}

/* ------------------------
 * Setter
 * Initialise la liste des candidats à l'élection
 */
void World::se_presentent(std::vector<unsigned int> candidats) {
    assert(this->population.size() >= NB_CANDIDATS && "error: too many candidates declared");
    if (candidats.size() < NB_CANDIDATS) { // Pas assez de candidats déclarés
        unsigned int nv_candidat; // Indice du nouveau candidat dans la population
        unsigned int j; // Itérateur
        bool nv_candidat_trouve;
        for (unsigned int i = candidats.size(); i < NB_CANDIDATS; i++) {
            nv_candidat_trouve = false;
            while (!nv_candidat_trouve) {
                // On prend une personne au hasard
                nv_candidat = RAND.rand_btw(0, this->population.size() - 1);
                j = 0;
                while (candidats[j] != nv_candidat && j < candidats.size()) j++;
                // Si la personne choisie n'est pas déjà candidate elle le devient
                if (j == candidats.size()) {
                    candidats.push_back(nv_candidat);
                    nv_candidat_trouve = true;
                }
            }
        }
    }
    for (unsigned int i = 0; i < NB_CANDIDATS; i++) { // S'il y en a trop, les derniers sont retirés
        // On récupère l'identité des candidats dont on a les identifiants
        this->liste_candidats[i] = this->population[candidats[i]];
        this->trace += "\n    Candidat n°" + std::to_string(i) + " : " + this->liste_candidats[i]->get_identite();
    }
    std::cout << "Problème ?\n";
}

/* ------------------------
 * Actionneur
 * Permet de truquer les élections
 */
void World::bourrer_les_urnes(Electeur* candidat, unsigned int quantite) {
    this->bureau.forcer_urne(position_candidat(candidat), quantite);
}


/* ------------------------
 * Simulation
 * Avance l'ensemble de la simulation d'un tick
 */
std::string World::tick_tock_goes_the_clock() {
    std::string trace = "";
    this->temps++;
    trace += "\nT = " + std::to_string(this->temps);
    for (unsigned int i = 0; i < this->population.size(); i++) {
        this->population[i]->decrement_time();
    }
    trace += this->bureau.gerer_tick(this->temps);
    return trace;
}

/* ------------------------
 * Simulation
 * Lance la simulation et récupère la trace des évènements
 */
void World::demarrer_simulation() {
    std::string trace = "";
    trace += "\n";
    trace += "\nOUVERTURE BUREAU n°" + std::to_string(this->bureau.get_numero());
    trace += "\nTMAX = " + std::to_string(Tmax);
    trace += "\n";
    for (unsigned int i = 0; i < this->population.size(); i++) {
        this->bureau.faire_entrer(this->population[i]);
    }
    while (this->temps < Tmax || this->bureau.get_nb_pers() > 0) {
        if (DBUG_ACTIVE) std::cout << "T = " << this->temps + 1; //DBUG/
        trace += this->tick_tock_goes_the_clock();
    }
    // Après la simulation...
    unsigned int nb_votes = 0;
    for (unsigned int i = 0; i < NB_BULLETINS; i++) nb_votes += this->bureau.get_resultat(i);
    unsigned int nb_electeurs = this->bureau.get_liste_el_em()->get_size();
    float taux_participation = 100 * nb_votes/nb_electeurs; //TODO/ Régler, l'arrondi ne marche pas
    trace += "\n";
    trace += "\nBUREAU n°" + std::to_string(this->bureau.get_numero()) + " : RESULTATS " + NOM_ELECTION;
    trace += "\nPRESIDENT : " + this->bureau.get_president()->get_identite();
    trace += "\n    nb electeurs : " + std::to_string(nb_electeurs);
    trace += "\n    nb votes : " + std::to_string(nb_votes);
    trace += "\n    participation : " + this->custom_float_trunc(std::to_string(taux_participation), 2) + " %";
    trace += "\n    abstention : " + this->custom_float_trunc(std::to_string(100 - taux_participation), 2) + " %";
    for (unsigned int i = 0; i < NB_CANDIDATS; i++) {
        trace += "\n    " + this->liste_candidats[i]->get_identite() + " : " + std::to_string(this->bureau.get_resultat(i))
            + " (" + this->custom_float_trunc(std::to_string(100*(float(this->bureau.get_resultat(i))/nb_votes)), 2) + " %)";
    }
    trace += "\n    blanc : " + std::to_string(this->bureau.get_resultat(NB_CANDIDATS))
        + " (" + this->custom_float_trunc(std::to_string(100*float(this->bureau.get_resultat(NB_CANDIDATS))/nb_votes), 2) + " %)";
    trace += "\n    nul : " + std::to_string(this->bureau.get_resultat(NB_CANDIDATS + 1))
        + " (" + this->custom_float_trunc(std::to_string(100*float(this->bureau.get_resultat(NB_CANDIDATS + 1))/nb_votes), 2) + " %)";
    this->trace += trace;
    // Écriture des résultats
    std::cout << "Écriture de la trace...\n";
    std::ofstream output(this->tracefile);
    output << this->trace;
    output.close();
}
