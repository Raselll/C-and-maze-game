#include "Developpeur.hpp"
#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "gsl/span"
#include "debogage_memoire.hpp" 
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"

using namespace std;

Developpeur::Developpeur(const string& name)
{
	paireNomJeux_ = { name, ListeJeux{} };
}

Developpeur::~Developpeur()
{
	delete[] paireNomJeux_.second.elements;
}

void Developpeur::addGames(ListeJeux& gameList)
{
	changeGameArraySize(paireNomJeux_.second, countNbGameDevelopped(gameList));
	for (auto&& game : spanListeJeux(gameList))
	{
		if (game->developpeur == getName())
			addGame(paireNomJeux_.second, game);
	}
}

void Developpeur::display() const
{
	cout << "The game has been developped by : " << getName() << "\n";
	if (paireNomJeux_.second.nElements > 0) 
	{
		for (auto&& game : spanListeJeux(paireNomJeux_.second))
			cout << "Name of the games are : " << game->titre << "\t";
	}

	else
		cout << "No game has been found !" << "\n";
}

int Developpeur::countNbGameDevelopped(ListeJeux& gameList)
{
	unsigned int A = 0;

	for (auto&& Game : spanListeJeux(gameList))
	{
		if (Game->developpeur == getName())
			A++;
	}
	return A;
}

