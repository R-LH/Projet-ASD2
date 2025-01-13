# Commandes utiles (pour le terminal Linux)
Pour configurer Git :
```
git config --global user.email "nom.prénom@etu.univ-nantes.fr"
git config --global user.name "Prénom"
```

Pour faciliter l'utilisation :
*Dans ~/.bash_aliases*
```
git() {
    if [[ $@ == "all" ]]; then
        command git add * && git status
    else
        command git "$@"
    fi
}
```

## Pour créer un répertoire local du projet (une seule fois) :
```
git clone https://gitlab.univ-nantes.fr/E223011D/asd2.git
```

## Pour accéder au répertoire local :
```
cd asd2
```

## Pour voir les différences et mettre à jour le répertoire local :
```
git diff
git pull https://gitlab.univ-nantes.fr/E223011D/asd2.git
```
**Note :** l'adresse URL est optionnelle

## Pour mettre à jour le répertoire Git :
```
git add <nom_du_premier_fichier> <nom_du_deuxième_fichier> etc...
git rm -r <nom du premier répertoire/fichier> <nom du second répertoire/fichier> etc...
```
_ou bien `git add -A` pour prendre tous les fichiers du répertoire local (attention aux changements non désirés) ; puis :_
```
git status
git commit -m "<Message synthétique décrivant le changement>"
git push https://gitlab.univ-nantes.fr/E223011D/asd2.git <nom_de_la_branche>
```
**Note :** l'adresse URL est optionnelle sauf quand il faut spécifier la branche
**Note :** spécifier la branche est optionnel comme il s'agit de _main_ par défaut
**Note :** `git status` sert à consulter l'état du répertoire local, il est optionnel mais conseillé

_et enfin pour nettoyer l'aire de stockage :_
```
git reset
```

## Pour créer une branche :
```
git checkout -b <nom_de_la_branche>
```

## Pour se placer sur une branche existante :
```
git checkout <nom_de_la_branche>
```

## Pour supprimer les changements (et non les fichiers) faits sur une branche :
```
git checkout .
```

## Pour fusionner une branche avec la branche principale :
```
git checkout main
git merge <nom_de_la_branche>
```
**Note :** une concertation préalable avec les autres membres de l'équipe est fortement conseillée

## Pour supprimer une branche :
```
git branch -d <nom_de_la_branche>
```

# Exemples de _programming tags_
### Liste non exhaustive :
```
TAG.....................Un marqueur de base
 ├── NOTE................Précision sur le code
 │    ├── WARN...........Attention
 │    ├── TEMP...........Partie temporaire
 │    └── BACK...........Version antérieure du code
 ├── TODO................Planification des tâches à réaliser
 │    ├── FIXME..........Quelque chose à réparer
 │    │    ├── BUG.......Un problème avec ce code
 │    │    └── XXX.......Ça marche, on ne sait pas trop comment, potentiellement problématique
 │    └── MORE...........Piste d'amélioration du code
 └── OPTI................Code optimisé mais pas très lisible (à éviter généralement)
      └── HACK...........Passe ton chemin si tu ne comprend pas
```
