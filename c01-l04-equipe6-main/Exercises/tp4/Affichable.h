/**
* Header pour la L'interface Affichable.
* \file   Affichable.h
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#pragma once
#include <iostream>

using namespace std;

class Affichable
{
public:
	virtual void changerCouleur(ostream& os, char couleur) = 0;
	virtual void afficher(ostream& os) = 0;
	virtual ~Affichable() = default;
};
