#pragma once
#include <string>
#include "gsl/span"
#include "ListeJeux.hpp"

class Developpeur
{
private:

	std::pair<std::string, ListeJeux> paireNomJeux_;

public:

	Developpeur(const std::string& name = "   ");
	~Developpeur();

	void addGames(ListeJeux& gameList);
	void display() const;
	const std::string& getName() const { return paireNomJeux_.first; }
	int countNbGameDevelopped(ListeJeux& gameList);
};