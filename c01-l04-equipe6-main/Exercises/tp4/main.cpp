/**
* Programme qui initialise une liste de heros et de vilains. Exercices sur l'affichage de ceux-ci ainsi que leur attributs. Creation d'une classe avec heritage multiple. Heritage 
* a partir d'une interface "Affichable".
* \file   main.cpp
* \author Bakir, Farid (1908977), Chowdhury, Rasel (2143023) et Tao, Tristan (1951367)
* \date   05 juin 2022
* Créé le 01 juin 2022
*/

#include <fstream>
#include "bibliotheque_cours.hpp"
#include "LectureBinaire.h"

using namespace std;

using UInt8 = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(std::istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(std::istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

std::string lireString(std::istream& fichier)
{
	std::string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), std::streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

vector<shared_ptr<Heros>> lireHeros(istream& fichier)
{
	unsigned nHeros = lireUint16(fichier);
	vector<shared_ptr<Heros>> vecHeros;
	for (unsigned i = 0; i < nHeros; i++)
	{
		string nom = lireString(fichier);
		string jeuTitre = lireString(fichier);
		string ennemi = lireString(fichier);
		unsigned nAllies = lireUint8(fichier);
		shared_ptr<Heros> herosPtr = make_shared<Heros>(nom, jeuTitre, nAllies, ennemi);
		for (unsigned j = 0; j < nAllies; j++)
		{
			string nomAllie = lireString(fichier);
			herosPtr->ajouterAllies(make_unique<string>(nomAllie));
		}
		vecHeros.push_back(herosPtr);
	}
	return vecHeros;
}

vector<shared_ptr<Vilain>> lireVilain(istream& fichier)
{
	unsigned nVilains = lireUint16(fichier);
	vector<shared_ptr<Vilain>> vecVilain;
	for (unsigned j = 0; j < nVilains; j++)
	{
		string nom = lireString(fichier);
		string jeuTitre = lireString(fichier);
		string objectif = lireString(fichier);

		shared_ptr<Vilain> vilainPtr = make_shared<Vilain>(nom, jeuTitre, objectif);
		vecVilain.push_back(vilainPtr);
	}
	return vecVilain;
}

int main()
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	ifstream fichierHeros("heros.bin", ios::binary);
	ifstream fichierVilains("vilains.bin", ios::binary);
	fichierHeros.exceptions(ios::failbit);
	fichierVilains.exceptions(ios::failbit);

	vector<shared_ptr<Vilain>> vecVilain(lireVilain(fichierVilains));
	vector<shared_ptr<Heros>> vecHeros(lireHeros(fichierHeros));
	vector<shared_ptr<Personnage>> vecPersonnage;

	for(auto&& hero : vecHeros)
	{
		hero->afficher(cout);
		vecPersonnage.push_back(hero);
	}
		

	for(auto&& vilain : vecVilain)
	{
		vilain->afficher(cout);
		vecPersonnage.push_back(vilain);
	}

	VilainHeros vilainsheros(vecVilain[3], vecHeros[3]);
	vecPersonnage.push_back(make_shared<VilainHeros>(vilainsheros));

	for (auto&& personnage : vecPersonnage)
		personnage->afficher(cout);
}
