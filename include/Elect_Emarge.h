#ifndef ELECT_EMARGE
#define ELECT_EMARGE
#include <set>
#include <vector>
#include "Personne.h"
#include "Electeur.h"
#include "parametres.h"

class Elect_Emarge {
private:
    // Enregistrement pour éviter les fraudes
    struct emargement{
        Electeur* electeur;
        bool a_vote;
    };

    // Opérateur pour comparer deux emargements
    struct CompBeta {
      bool operator()(emargement e1, emargement e2) const {
        Electeur* p1;
        Electeur* p2;
        p1=e1.electeur;
        p2=e2.electeur;
        if (p1->nom() < p2->nom()) return true;
        if (p1->nom() > p2->nom()) return false;
        if (p1->prenom() < p2->prenom()) return true;
        if (p1->prenom() > p2->prenom()) return false;
        return (p1->id() < p2->id());
      }
    };

    // Attributs
    std::set<emargement, CompBeta> liste ; // Liste d'Emargement et Electoral trié dans l'odre alphabétique

public:
    // Getters
    unsigned int get_size();

    // Actions
    void initialiser(std::vector<Electeur*> population); // Initialise la liste à partir d'un vecteur
    void inserer(Electeur* electeur); // Insère la personne passée en paramètre
    bool est_electeur(Electeur* electeur); // Vérifie la présence d'une personne sur la liste électorale
    bool a_vote(Electeur* electeur); // Vérifie si une personne a signé la liste d'émargement
    void emarger(Electeur* electeur); //Fait Emerger une personne
    bool contains(emargement e); // Vérifie qu'un électeur est bien inscrit
    std::string afficher();

    // Constructeur et destructeur
    Elect_Emarge();
    ~Elect_Emarge();
};

#endif
