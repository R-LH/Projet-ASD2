#include <iostream>
#include "World.h"
#include "Random.h"
#include "parametres.h"

int main() {
   // TODO
   // Code de simulation dans lequel on manipulera les personnes
   // via des pointeurs sur les éléments du vecteur vp.
   std::string launch = "";
   //std::cout << "\033\143"; // Efface le contenu de la console
   std::cout << "========== BIENVENUE DANS L'ESPACE DE SIMULATION ==========\n";
   std::cout << "Vous êtes sur le point de lancer la simulation suivante :\n";
   std::cout << "Type : Bureau de vote\n";
   std::cout << "Paramètres :\n";
   std::cout << "    Tmax = " << Tmax << " ticks\n";
   std::cout << "    Dd = " << Dd << " ticks\n";
   std::cout << "    Di = " << Di << " ticks\n";
   std::cout << "    Dv = " << Dv << " ticks\n";
   std::cout << "    pb = " << P_BLANC << " %\n";
   std::cout << "    pn = " << P_NUL << " %\n";
   std::cout << "    ni = " << NB_ISOLOIRS << " isoloirs\n";
   std::cout << "    dp = " << D_POL << "\n";
   std::cout << "===========================================================\n";
   std::cout << "Lancer la simulation (y/n): ";
   std::cin >> launch;
   if (launch == "y" || launch == "Y") {
      std::cout << "Lancement de la simulation...\n";
      World simulation = World("trace.txt");
      // simulation.demarrer_simulation(); // Automatique par le contructeur de World
      std::cout << "Simulation terminée\n";
   } else {
      std::cout << "Opération annulée\n";
      std::cout << "Extinction...\n";
   }
}
