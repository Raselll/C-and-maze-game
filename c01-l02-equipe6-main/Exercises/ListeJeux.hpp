#pragma once
#include "gsl/span"
// La déclaration suivante plutôt qu'un #include "Jeu.hpp" est nécessaire sinon il y aurait une boucle d'inclusion (ListeJeux.hpp > Jeu.hpp > ListeDesigners.hpp > Designer.hpp > ListeJeux.hpp), la boucle serait arrêtée par le "pragma once" mais ListeJeux ne serait alors pas déclaré lors de la compilation de Designer.
struct Jeu;  // Déclaration avancée ("forward declaration") pour pouvoir utilise le nom du type avant qu'il soit complètement défini.


struct ListeJeux
{
	int capacite;
	int nElements;
	Jeu** elements;
};

gsl::span<Jeu*> spanListeJeux(const ListeJeux& List);
void changeGameArraySize(ListeJeux& List, int newCapacity);
void addGame(ListeJeux& List, Jeu* Game);

