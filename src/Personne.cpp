/**
 * \file Personne.cpp
 * \author Laurent Granvilliers
 */

#include "Personne.h"

namespace elections {

int Personne::sid_ = 0;

Personne::Personne(const std::string& nom, const std::string& prenom)
      : nom_(nom), prenom_(prenom), id_(sid_++) {}

Personne::Personne() {}

std::string Personne::nom() const {return nom_;}
std::string Personne::prenom() const {return prenom_;}
int Personne::id() const {return id_;}

std::ostream& operator<<(std::ostream& os, const Personne& psn) {
   os << psn.nom() << " " << psn.prenom();
   return os;
}

} // namespace
