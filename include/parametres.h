#ifndef VARIABLES
#define VARIABLES

#include <string>

//--------------------------------------------------------
// Constantes globales pour les réglages de la simulation
//--------------------------------------------------------

// Paramètres du monde
const std::string NOM_ELECTION = "Euro 2024";
// const unsigned int[] LISTE_CANDIDATS = {0, 3, 7}; // Petit problème à la compilation...
const unsigned int NB_CANDIDATS = 3; // Le nombre de candidats à l'élection
const unsigned int NB_ISOLOIRS = 3; // Le nombre d'isoloirs dans le bureau /MORE/ Et si on veut en rajouter/enlever ?
const unsigned int NB_BULLETINS = NB_CANDIDATS + 2; // Un bulletin par candidat + bulletins blancs et nuls
    //NOTE/ Bulletins blancs à l'indice [taille-2] et nuls à [taille-1]
const unsigned int QTT_BULLETINS_MIN = 2; // Le nombre minimum de bulletins différents qu'un électeur doit prendre à la table de décharge

static Random RAND = Random(); // Un unique générateur aléatoire pour le monde

// Durées
const unsigned int Dd = 3; // Temps max passé à la table de décharge
const unsigned int Di = 6; // Temps max passé dans l'isoloir
const unsigned int Dv = 4; // Temps max passé à la table de vote
    //NOTE/ Devraient plutôt être des durées maximales que des durées obligatoires
const unsigned int Tmax = 40; // Temps après lequel on n'accepte plus de nouvelles personnes dans le bureau

// Statistiques
const float P_ABS = 0.1; // Pourcentage d'abstention
const float P_BLANC = 0.35; // Pourcentage de votes blancs
const float P_NUL = 0.15; // Pourcentages de votes nuls (protestation contre le système politique)
    //NOTE/ Ne devrait pas être un pourcentage mais le choix par défaut de chaque électeur
    // s'il considère qu'aucun candidat ne lui correspond
const float D_POL = 3.0; // Divergence politique (distance max entre deux positions politiques)

// Politique
const unsigned int TENDANCE_SOC = 3; // Tendance de la politique (sociale ou économique, c.f. Electeur.h) au sein de la population
const unsigned int TENDANCE_ECO = 6;
const unsigned int DIV_SOC = 2; // Distance maximale à la tendance
const unsigned int DIV_ECO = 1;
const float PART_SOC = 0.5; // Part de la population sous la distance maximale
const float PART_ECO = 0.5;

// Développement
const bool DBUG_ACTIVE = false; // Affiche la trace de déboguage

#endif
