/**
* Header pour la classe Vilain qui herite de la classe Personnage.
* \file   Vilain.h
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#pragma once
#include <iostream>
#include "Personnage.h"

using namespace std;

class Vilain : virtual public Personnage
{
public:
	Vilain(const string& nom, const string& jeu, const string& objectif) : Personnage(nom, jeu), objectif_(objectif) {};
	Vilain(const Vilain& autre);
	void afficher(ostream& os) override;

	string getObjectif() const { return objectif_; }

private:
	string objectif_;
};

Vilain::Vilain(const Vilain& autre) : Personnage(autre)
{
	objectif_ = autre.objectif_;
}

void Vilain::afficher(ostream& os)
{
	Personnage::afficher(os);
	Personnage::changerCouleur(os, 'V');
	os << "Objectif : " << objectif_ << "\n";
	os << "═════════════════════════════════════════════════════════════════════════" << "\n";

}
