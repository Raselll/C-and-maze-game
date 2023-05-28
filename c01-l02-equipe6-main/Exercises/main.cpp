// Auteurs: Tao, Tristan (1951367) et Chowdhury, Rasel (2143023)
//
// Date: 2022-05-22

#include "Jeu.hpp"
#include "Designer.hpp"
#include "Developpeur.hpp"
#include "ListeJeux.hpp"
#include "ListeDesigners.hpp"
#include "ListeDeveloppeurs.hpp"
#include <iostream>
#include <fstream>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

using namespace std;
using namespace iter;
using namespace gsl;

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
gsl::span<Designer*> spanListeDesigners(const ListeDesigners& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion

Designer* findDesigner(const ListeJeux& gameList, string& name)
{
	for(const Jeu* game : spanListeJeux(gameList))
	{
		for(Designer* designer : spanListeDesigners(game->designers))
		{
			if(designer->nom == name)
			{
				return designer;
			}
			else
				return nullptr;     
		}
	}
}

Designer* lireDesigner(istream& fichier, ListeJeux& gameList)
{
	Designer designer = {}; 
	designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);

	Designer* alivedDesigner = findDesigner(gameList, designer.nom);
	if(alivedDesigner != nullptr)
	{
		cout << "New Designer created ! "<< "\n";
		return alivedDesigner;
	}
	
	cout << "Designer name : " << designer.nom << "\n";
	return new Designer(designer);
}

void changeGameArraySize(ListeJeux& gameList, int newCapacity)
{
	Jeu** newGameList = new Jeu * [newCapacity];	
	
	for(int i : range(gameList.nElements))
	{
		newGameList[i] = gameList.elements[i];
	}

	delete[] gameList.elements;

	gameList.elements = newGameList;
	gameList.capacite = newCapacity;
}

void addGame(ListeJeux& gameList, Jeu* addedGame)
{
	if(gameList.nElements == gameList.capacite)
	{
		if(gameList.capacite == 0)
		{
			changeGameArraySize(gameList, 1);
		}
		else
		{
			changeGameArraySize(gameList, gameList.capacite * 2);
		}
	}
	gameList.elements[gameList.nElements++] = addedGame;
}

void removeGame(ListeJeux& gameList, const Jeu* jeu)
{
	for(auto&& game : spanListeJeux(gameList))
	{
		if(game == jeu)
		{
			if(gameList.nElements > 1)
				game = gameList.elements[gameList.nElements - 1];
			gameList.nElements--;
		}
	}
}

Jeu* lireJeu(istream& fichier, ListeJeux& gameList)
{
	Jeu jeu = {};
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);
	
	Jeu* gamePtr = new Jeu(jeu);
	cout << "Allocation of: " << jeu.titre << " made" << "\n";
	gamePtr->designers.elements = new Designer* [gamePtr->designers.nElements];

	//cout << jeu.titre << endl;  
	
	for (auto&& designer : spanListeDesigners(gamePtr->designers)) {
		designer = lireDesigner(fichier, gameList);
		addGame(designer->listeJeuxParticipes, gamePtr);
	}
	return gamePtr; 
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	ListeJeux gameList = {};
	for(int n : range(nElements))
	{
		addGame(gameList, lireJeu(fichier, gameList)); 
	}

	return gameList; 
}

void destroyDesigner(Designer* designer)
{
	cout << "Destroying the designer named " << designer->nom << "\n";

	delete[] designer->listeJeuxParticipes.elements;
	delete designer;
}

bool stillParticipating(const Designer* designer)
{
	return designer->listeJeuxParticipes.nElements != 0;
}

void destroyGame(Jeu* game)
{
	for(Designer* designer : spanListeDesigners(game->designers))
	{
		removeGame(designer->listeJeuxParticipes, game);
		if(!stillParticipating(designer))
			destroyDesigner(designer);
	}
	cout << "Destruction of the following game : " << game->titre << "\n";

	delete[] game->designers.elements;
	delete game;
}

void destroyGameList(ListeJeux& gameList)
{
	for(Jeu* game : spanListeJeux(gameList))
	{
		destroyGame(game);
	}
	delete[] gameList.elements;
	cout << "Game list deleted !" << "\n";
}

void afficherDesigner(const Designer& d)
{
	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
			  << endl;
}

void displayGameInfos(const Jeu& game)
{
	cout << "Titre of the game : " << game.titre << "\n";
	cout << "Game developpers : " << game.developpeur << "\n";
	cout << "Year of publication : " << game.anneeSortie << "\n";
	cout << "Game designers : ";
	for(const Designer* designer : spanListeDesigners(game.designers))
		afficherDesigner(*designer);
}

void displayGameList(const ListeJeux& gameList)
{
	static const string lineSeparation = "\033[91m════════════════════════════════════════\033[0m\n";
	// Source : https://stackoverflow.com/questions/15580303/python-output-complex-line-with-floats-colored-by-value

	cout << lineSeparation << "\n";
	for(const Jeu* game : spanListeJeux(gameList))
	{
		displayGameInfos(*game);
		cout << lineSeparation << "\n";
	}
}

int main(int argc, char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion

	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	ListeJeux gameList = creerListeJeux("jeux.bin"); 

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	displayGameInfos(*gameList.elements[0]);
	cout << ligneSeparation << endl;

	displayGameList(gameList);

	ListeDeveloppeurs devList;
	Developpeur* square = new Developpeur("Square !");
	Developpeur* konami = new Developpeur("Konami !");
	Developpeur* nintendo = new Developpeur("Nintendo !");
	Developpeur* bidon = new Developpeur("Bidon !");

	square->addGames(gameList);
	konami->addGames(gameList);
	nintendo->addGames(gameList);
	bidon->addGames(gameList);
	devList.add(square);
	devList.add(konami);
	devList.add(nintendo);
	devList.add(bidon);
	devList.display();

	devList.remove(bidon);
	devList.display();
	cout << "There's still the existance of : " << bidon->getName() << "\n";

	delete square;
	delete konami;
	delete nintendo;
	delete bidon;

	destroyGameList(gameList);
}
