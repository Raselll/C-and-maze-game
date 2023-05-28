#pragma once
#include <string>
#include <iostream>
using namespace std;


enum Command {
	NORD = 0, EST = 1, SUD = 2, OUEST = 3,
	REGARDER = 4, UTILISER = 5, SORTIR = 6, AIDE = 7
};

enum ObjetInteractif {
	PIANO = 0, INTERRUPTEUR = 1, LIVRE = 2, CORDE = 3, CLE = 4
};

static const int nObjetsTotal = 5;

inline static void afficherTexte(const string& texte1 = "", const string& texte2 = "", const string& texte3 = "") {
	cout << texte1 << texte2 << texte3 << endl;
}

inline static bool contientString(const string& chaineAParcourir, const string& chaineCherche) {
	int indice = (int)chaineAParcourir.find(chaineCherche);
	return indice >= 0 && indice < chaineAParcourir.length();
}




inline static string caractereEnString(char caracterATransformer) {
	string chaineARetourner;
	return chaineARetourner.append(1, caracterATransformer);
}

inline static string transformerEnMajuscule(const string& chaineMiniscule) {
	string chaineMajuscule = "";
	for (int i = 0; i < chaineMiniscule.length(); i++) {
		chaineMajuscule.append(1, (char)toupper(chaineMiniscule[i]));
	}
	return chaineMajuscule;
}

inline static bool contientUtiliser(string chaine) {
	string utiliser = "UTILISER";
	bool contientUtiliser = true;
	for (int i = 0; i < utiliser.length(); i++) {
		if (utiliser[i] != chaine[i]) {
			contientUtiliser = false;
			break;
		}
	}
	return contientUtiliser;
}

inline static bool contientRegarder(string chaine) {
	string regarder = "REGARDER";
	bool contientRegarder = true;
	for (int i = 0; i < regarder.length(); i++) {
		if (regarder[i] != chaine[i]) {
			contientRegarder = false;
			break;
		}
	}
	return contientRegarder;
}

static const char nordChar = 'N';
static const char sudChar = 'S';
static const char estChar = 'E';
static const char ouestChar = 'O';


static const int nCommandes = 8;
static const int nCommandeSupplementaires = 4;


static const string tableauCommande[nCommandes] = { "N","E","S","O","REGARDER","UTILISER","SORTIR","AIDE" };

static const string commandeSupplementaire[nCommandeSupplementaires] = { "NORD","EST","SUD","OUEST" };

static const string messageDePresention1 = ">>>> INF1015 MAISON HANTEE 2022 <<<<";
static const string messageDePresention2 = "  >>------- GOTY EDITION -------<<\n";
static const string inviteCommande_ = "> ";


static const string nomEntree = "--Entree Principale--";
static const string descriptionEntree = "Voici l'entree, elle est grande et on peut y trouver un placard pour y placer notre manteau.";

static const string nomSalon = "--Salon--";
static const string descriptionSalon = "Le salon est en desordre total. Il y a une quantite innombrable de feuilles toutes eparpillees sur le plancher.";

static const string nomCouloir = "--Couloir--";
static const string descriptionCouloir = "Le couloir est vraiment en desordre et plein de feuilles se retrouvent eparpillees sur le plancher.";

static const string nomPetiteChambre = "--Petite Chambre--";
static const string descriptionPetiteChambre = "Dans la petite chambre, il y a un lit completement defait, les murs sont recouvert d'un papier peint vert pistache et il y a une commode rempli de vetement.";

static const string nomCuisine = "--Cuisine--";
static const string descriptionCuisine = "La cuisine est delabre et des casseroles se trouve encore sur la cuisiniere. Le frigidaire est vide, mais le garde-manger est rempli de sacs de farine et de semoule.";

static const string nomSalleCachee = "--Salle Cachee--";
static const string descriptionSalleCachee = "Cette salle renferme de sombres secrets qui ne devrait jamais voir le jour";

static const string nomPiano = "PIANO";
static const string descriptionPiano = "Le piano est un Steinway Modele D.";
static const string messageUtilisationPiano = "En jouant le piano, la basse resonne dans le salon. Vous remarquez qu'il y a une cle doree sur le lutrin.";
static const string lieuActionPiano = "Test.";

static const string nomInterrupteur = "INTERRUPTEUR";
static const string descriptionInterrupteur = "L'interrupteur est a moitie casse.";
static const string messageUtilisationInterrupteur = "En utilisant l'interrupteur, la salle gronde. Des vibrations provenant de l'Est retentissent et une entree secrete se devoile vers une salle secrete et mysterieuse.";
static const string lieuActionInterrupteur = "Test.";

static const string nomLivre = "LIVRE";
static const string descriptionLivre = "Le livre semble en parfait etat...";
static const string messageUtilisationLivre = "Les pages se dechirent quand vous le feuilletez";
static const string lieuActionLivre = "Test.";

static const string nomCorde = "CORDE";
static const string descriptionCorde = "La corde est jaune et longue";
static const string messageUtilisationCorde = "Elle s'effrite quand vous la manipulez.";
static const string lieuActionCorde = "Test.";

static const string nomCle = "CLE";
static const string descriptionCle = "La cle est doree et dentelee.";
static const string messageUtilisationCle = "Une energie mysterieuse emane de la cle.";
static const string lieuActionCle = "Test.";

static const string empruntNord = "Emprunt du chemin menant vers le Nord!\n";
static const string empruntSud = "Emprunt du chemin menant vers le Sud!\n";
static const string empruntEst = "Emprunt du chemin menant vers l'Est!\n";
static const string empruntOuest = "Emprunt du chemin menant vers l'Ouest!\n";

static const string cheminImpossibleNord = "Il n'y a pas de salle au Nord!\n";
static const string cheminImpossibleSud = "Il n'y a pas de salle au Sud!\n";
static const string cheminImpossibleEst = "Il n'y a pas de salle a l'Est!\n";
static const string cheminImpossibleOuest = "Il n'y a pas de salle a l'Ouest!\n";

static const string sortie = "\nVous venez de quitter le jeux";

static const string listeCommande = "\nles differentes commandes sont: N, S, E, O, REGARDER, UTILISER, SORTIR ET AIDE";

static const string messageErreurCommande = "Erreur commande invalide\n";

static const string tableauObjet[nObjetsTotal] = { "PIANO","INTERRUPTEUR","LIVRE","CORDE","CLE" };

static const string messageSalleDebloque = "La salle cacher est maintenant debloque\n";

static const string messageErreurObjet = "L'objet n'existe pas!\n";

inline static string transformerIndiceEnObjet(int indiceObjet) {
	string nomObjet = "";
	if (indiceObjet >= 0) {
		nomObjet = tableauObjet[indiceObjet];
	}
	return nomObjet;
}

inline static int chaineContientObjet(string chaine) {
	int indiceObjet = -1;
	for (int i = 0; i < nObjetsTotal; i++) {
		if (contientString(chaine, tableauObjet[i])) {
			indiceObjet = i;
			break;
		}
	}
	return indiceObjet;
}

