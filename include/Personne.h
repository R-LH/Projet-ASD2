/**
 * \file Personne.h
 * \author Laurent Granvilliers
 */

#ifndef PERSONNE
#define PERSONNE

#include <iostream>
#include <string>

namespace elections {

/**
 * Une personne est définie par un nom, un prénom et un identifiant unique
 *
 * L'identifiant unique est généré automatiquement.
 */
class Personne {
public:
   /**
    * Constructeur.
    * \param nom    nom de la personne
    * \param prenom prénom de la personne
    */
   Personne(const std::string& nom, const std::string& prenom);

   /**
    * Constructeur.
    * Pour chaîner les constructeurs de la classe Electeur.
    */
   Personne();

   /**
    * Accesseur.
    * \return le nom
    */
   std::string nom() const;

   /**
    * Accesseur.
    * \return le prénom
    */
   std::string prenom() const;

   /**
    * Accesseur.
    * \return l'identifiant
    */
   int id() const;

private:
   std::string nom_, prenom_;
   int id_;
   static int sid_;

public:
   /**
    * Définition d'une relation d'ordre sur les personnes selon l'ordre
    * alphabétique des noms, puis l'ordre alphabétique des prénoms, puis
    * l'ordre croissant des identifiants.
    *
    * Exemple pour trier un vecteur :
    * \code{.cpp}
    * std::vector<Personne*> v;
    * CompAlpha comp;
    * ...
    * std::sort(v.begin(), v.end(), comp);
    * \endcode
    *
    * Exemple pour définir un ensemble ordonné :
    * \code{.cpp}
    * std::set<Personne*, CompAlpha> ens;
    * \endcode
    */
   struct CompAlpha {
      // Opérateur de comparaison entre deux personnes
      bool operator()(Personne* p1, Personne* p2) const {
         if (p1->nom() < p2->nom()) return true;
         if (p1->nom() > p2->nom()) return false;
         if (p1->prenom() < p2->prenom()) return true;
         if (p1->prenom() > p2->prenom()) return false;
         return (p1->id() < p2->id());
      }
   };

   // Opérateur d'égalité entre deux personnes
   bool operator==(const Personne &p) const {
      return this->id() == p.id();
}

   // Opérateur de différence entre deux personnes
   bool operator!=(const Personne &p) const {
      return this->id() != p.id();
   }
};



/**
 * Écriture sur un flux de sortie.
 * \param os un flux de sortie
 * \param psn une personne
 * \return le flux donné en entrée os
 */
std::ostream& operator<<(std::ostream& os, const Personne& psn);

} // namespace

#endif
