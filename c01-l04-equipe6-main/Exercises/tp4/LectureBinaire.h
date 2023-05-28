/**
* Header contenant les declarations des fonctions de lecture pour les classes Heros et Vilain.
* \file   LectureBinaire.h
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#pragma once
#include "Heros.h"
#include "Vilain.h"
#include "VilainHeros.h"

using namespace std;

using UInt8 = uint8_t;
using UInt16 = uint16_t;


UInt8 lireUint8(istream& fichier);
UInt16 lireUint16(istream& fichier);
string lireString(istream& fichier);
vector<shared_ptr<Heros>> lireHeros(istream& fichier);
vector<shared_ptr<Vilain>> lireVilain(istream& fichier);
