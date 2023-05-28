/**
* Fichier header pour la classe VilainHeros qui herite a la fois des classes de Heros et de Vilain.
* \file   VilainHeros.h
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#pragma once
#include <iostream>
#include "Vilain.h"
#include "Heros.h"

using namespace std;

class VilainHeros : public Heros, public Vilain
{
public:
	VilainHeros(const shared_ptr<Vilain>& vilain, const shared_ptr<Heros>& heros);
	void afficher(ostream& os) override;
};

void VilainHeros::afficher(ostream& os)
{
	Personnage::changerCouleur(os, 'J');
	Personnage::afficher(os);
	os << "Objectif : " << Vilain::getObjectif() << "\n";
	os << "Ennemi : " << Heros::getEnnemi() << "\n";
	os << "Allies : " << "\n";
	for (auto&& allie : Heros::getAllies())
		os << "  " << *allie << "\n";

	os << "Misision speciale : " << Vilain::getObjectif() + " dans le monde de " << Heros::getJeu() << "\n";
	os << "═════════════════════════════════════════════════════════════════════════" << "\n";

	Personnage::changerCouleur(os, 'B');
}


VilainHeros::VilainHeros(const shared_ptr<Vilain>& vilain, const shared_ptr<Heros>& heros) :
	Personnage(heros->getNom() + "-" + vilain->getNom(), heros->getJeu() + "-" + vilain-> getJeu()),
	Heros(*heros), Vilain(*vilain) {}
