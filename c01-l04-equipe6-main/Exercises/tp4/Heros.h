/**
* Header pour la classe Heros qui herite de la classe Personnage.
* \file   Heros.h
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#pragma once
#include <vector>
#include <memory>
#include <iostream>

#include "Personnage.h"

using namespace std;

class Heros : virtual public Personnage
{
public:
	Heros(const string& nom, const string& jeu, unsigned nAllies, string& ennemi) : Personnage(nom, jeu), nAllie_(nAllies), ennemi_(ennemi) {}
	Heros(const Heros& autre);
	void afficher(ostream& os) override;
	void ajouterAllies(shared_ptr<string> nom) { listeAllie_.push_back(nom); }

	string getEnnemi() const { return ennemi_; }
	vector<shared_ptr<string>> getAllies() const { return listeAllie_; }

private:
	unsigned nAllie_;
	string ennemi_;
	vector<shared_ptr<string>> listeAllie_;
};

void Heros::afficher(ostream& os)
{
	Personnage::afficher(os);
	Personnage::changerCouleur(os, 'R');
	os << "Ennemi : " << ennemi_ << "\n\n";
	os << "Allie : " << "\n";
	for (auto&& allies : listeAllie_) 
	{
		os << "  " << *allies << "\n";
	}
	os << "═════════════════════════════════════════════════════════════════════════" << "\n";

}

Heros::Heros(const Heros& autre) : Personnage(autre)
{
	ennemi_ = autre.ennemi_;
	nAllie_ = autre.nAllie_;
	for (auto&& allie : autre.listeAllie_)
		listeAllie_.push_back(allie);
}
