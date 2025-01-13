#ifndef FILEELECTEURS
#define FILEELECTEURS

//NOTE/ On utilise un tableau circulaire
//MORE/ Utiliser un std::vector<Electeur*> pour la SDC ?

#include "Electeur.h"
#include "parametres.h"

class FileElecteurs {
private:
    unsigned int capa; // Capacité maximale de la file
    unsigned int occ; // L'occupation de la file
    unsigned int premier; // Indice de l'électeur en tête de la file
    Electeur* contenu[10]; // Le tableau dynamique de la file
public:
    // Getters
    Electeur* get_first();
    Electeur* get_at_pos(unsigned int indice);
    unsigned int get_occupation();

    // Actions
    void ajouter(Electeur* electeur);
    void agrandir();
    Electeur* extraire();

    // Constructeurs et destructeur
    FileElecteurs(unsigned int taille);
    FileElecteurs();
    ~FileElecteurs();
};

#endif
