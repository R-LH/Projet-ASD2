#include <stdlib.h> // Pour utiliser srand() et rand()
#include <time.h> // Pour des nombres vraiment aléatoires
#include "Random.h"

// Constructeur et destructeur
Random::Random() {
    srand(time(NULL)); // Initialise le générateur de nombres aléatoires
}

Random::~Random() {}

// Actions
// ------------------------
// Renvoie un entier aléatoire compris entre borne_inf et borne_sup incluse
int Random::rand_btw(int borne_inf, int borne_sup) {
    double num = rand(); // Appelle le générateur (cette ligne doit être seule)
    return (int)((1 + borne_sup - borne_inf) * (num / RAND_MAX) + borne_inf);
}

// ------------------------
// Renvoie un réel aléatoire compris entre borne_inf et borne_sup exclue
double Random::rand_btw(double borne_inf, double borne_sup) {
    double num = rand();
    return (borne_sup - borne_inf) * (num / RAND_MAX) + borne_inf;
}

// ------------------------
// Renvoie un réel aléatoire compris entre 0.0 et 0.99
double Random::percentage() {
    double num = rand();
    return num / RAND_MAX;
}

// ------------------------
// Renvoie un entier aléatoire compris entre 1 et nb_faces
int Random::d(unsigned int nb_faces) {
    double num = rand(); return (int)(nb_faces * (num / RAND_MAX) + 1);
}
