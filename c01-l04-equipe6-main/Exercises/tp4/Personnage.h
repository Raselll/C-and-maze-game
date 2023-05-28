/**
* Header pour la classe Personnage qui herite de l'interface Affichable.
* \file   Personnage.h
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#pragma once
#include <iostream>

#include "Affichable.h"

using namespace std;

class Personnage : public Affichable
{
public:
	Personnage(const string& nom, const string& jeu) : nomPersonnage_(nom), jeuTitre_(jeu) {};
	void changerCouleur(ostream& os, char couleur) override;
	void afficher(ostream& os) override;

	string getNom() const { return nomPersonnage_; }
	string getJeu() { return jeuTitre_; }

private:
	string nomPersonnage_;
	string jeuTitre_;
};

void Personnage::changerCouleur(ostream& os, char couleur)
{
	// Blanc
	if (couleur == 'B') {
		os << "\n\033[37m";
	}
	// Rouge
	else if (couleur == 'R') {
		os << "\n\033[91m";
	}
	// vert
	else if (couleur == 'V') {
		os << "\n\033[92m";
	}
	// Jaune
	else if (couleur == 'J') {
		os << "\n\033[93m";
	}
	// Purple
	else if (couleur == 'B') {
		os << "\n\033[95m";
	}

	// Couleur par defaut
	else (os << "\n\033[30m");
}

void Personnage::afficher(ostream& os)
{
	os << "Nom : " << nomPersonnage_ << "\n";
	os << "Titre : " << jeuTitre_ << "\n";
}
