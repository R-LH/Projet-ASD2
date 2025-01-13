#ifndef RANDOM
#define RANDOM

class Random {
public:
    // Actions
    // Précondition : borne_inf < borne_sup
    int rand_btw(int borne_inf, int borne_sup);
    // Précondition : borne_inf < borne_sup
    double rand_btw(double borne_inf, double borne_sup);
    double percentage();
    int d(unsigned int nb_faces);

    // Constructeurs et destructeur
    Random();
    ~Random();
};

#endif
