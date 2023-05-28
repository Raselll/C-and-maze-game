#include "VueJeu.hpp"

void VueJeu::initialiser() {

	presentationJeu();

	shared_ptr<Salle> entree = make_shared<Salle>(nomEntree, descriptionEntree);
	shared_ptr<Salle> salon = make_shared<Salle>(nomSalon, descriptionSalon);
	shared_ptr<Salle> cuisine = make_shared<Salle>(nomCuisine, descriptionCuisine);
	shared_ptr<Salle> petiteChambre = make_shared<Salle>(nomPetiteChambre, descriptionPetiteChambre);
	shared_ptr<Salle> couloir = make_shared<Salle>(nomCouloir, descriptionCouloir);


	entree->setDirections(couloir, salon, nullptr, nullptr);
	salon->setDirections(nullptr, nullptr, nullptr, entree);
	cuisine->setDirections(nullptr, nullptr, couloir, nullptr);
	petiteChambre->setDirections(nullptr, couloir, nullptr, nullptr);
	couloir->setDirections(cuisine, nullptr, entree, petiteChambre);

	shared_ptr<Objet> piano = make_shared<Objet>(nomPiano, descriptionPiano, messageUtilisationPiano, lieuActionPiano, 0, true);
	shared_ptr<Objet> interrupteur = make_shared<Objet>(nomInterrupteur, descriptionInterrupteur, messageUtilisationInterrupteur, lieuActionInterrupteur, 1, true);
	shared_ptr<Objet> livre = make_shared<Objet>(nomLivre, descriptionLivre, messageUtilisationLivre, lieuActionLivre, 2, true);
	shared_ptr<Objet> corde = make_shared<Objet>(nomCorde, descriptionCorde, messageUtilisationCorde, lieuActionCorde, 3, true);

	salon->ajouterObjet(piano);
	couloir->ajouterObjet(interrupteur);
	cuisine->ajouterObjet(livre);
	petiteChambre->ajouterObjet(corde);

	controleur_->ajouterSalle(entree);
	controleur_->ajouterSalle(salon);
	controleur_->ajouterSalle(cuisine);
	controleur_->ajouterSalle(petiteChambre);
	controleur_->ajouterSalle(couloir);

	controleur_->ajouterObjet(piano);
	controleur_->ajouterObjet(interrupteur);
	controleur_->ajouterObjet(livre);
	controleur_->ajouterObjet(corde);

	controleur_->setSalleCourante(entree);

	cout << controleur_->getSalleCourante()->regarder() << endl;
}




void VueJeu::afficherInviteCommande() {
	cout << inviteCommande_;
}



void VueJeu::presentationJeu() {
	afficherTexte(messageDePresention1);
	afficherTexte(messageDePresention2);
}

int VueJeu::indiceCommande(const string& chaineAchercher) {

	string chaineRechercher = transformerEnMajuscule(chaineAchercher);
	int indiceCommande = -1;

	if (contientUtiliser(chaineRechercher)) {
		indiceCommande = UTILISER;
	}
	if (contientRegarder(chaineRechercher)) {
		indiceCommande = REGARDER;
	}
	else {

		for (int i = 0; i < nCommandes; i++) {

			if (chaineRechercher == tableauCommande[i]) {
				indiceCommande = i;
				break;
			}
		}
	}
	return indiceCommande;
}

string VueJeu::transformerEnCommandeStandard(const string& chaineATransformer) {
	string chaine = transformerEnMajuscule(chaineATransformer);

	for (int i = 0; i < nCommandeSupplementaires; i++) {
		if (chaine == commandeSupplementaire[i]) {
			chaine = chaine[0];
			break;
		}
	}
	return chaine;
}


pair<int, int> VueJeu::validerEntree() {
	string chaineUtilisateur = "";
	pair<int, int> indiceCommandeObjet = { -1,-1 };

	do {
		getline(cin >> ws, chaineUtilisateur);

		chaineUtilisateur = transformerEnCommandeStandard(chaineUtilisateur);

		indiceCommandeObjet.first = indiceCommande(chaineUtilisateur);

		if (indiceCommandeObjet.first == -1) {
			afficherTexte(messageErreurCommande);
			afficherInviteCommande();
		}
		else {

			if (indiceCommandeObjet.first == REGARDER and chaineUtilisateur.size() > 8)
			{
				string nomObjet = chaineUtilisateur.substr(9);
				if (nomObjet == "PIANO" ) {
					afficherTexte(nomPiano);
					afficherTexte(descriptionPiano);
					afficherInviteCommande();
					lireCommande();
				}
				if (nomObjet == "INTERRUPTEUR") {
					afficherTexte(nomInterrupteur);
					afficherTexte(descriptionInterrupteur);
					afficherInviteCommande();
					lireCommande();
				}
				if (nomObjet == "LIVRE") {
					afficherTexte(nomLivre);
					afficherTexte(descriptionLivre);
					afficherInviteCommande();
					lireCommande();
				}
				if (nomObjet == "CORDE") {
					afficherTexte(nomCorde);
					afficherTexte(descriptionCorde);
					afficherInviteCommande();
					lireCommande();
				}
				if (nomObjet == "") {
					controleur_->getSalleCourante()->regarder();
				}
				else {
					afficherTexte(messageErreurObjet);
					afficherInviteCommande();
					lireCommande();
				}
				indiceCommandeObjet.second = indiceObjet(nomObjet);
			}
			if (indiceCommandeObjet.first == UTILISER and chaineUtilisateur.size() > 8) {
				string nomObjet = chaineUtilisateur.substr(9);

				indiceCommandeObjet.second = indiceObjet(nomObjet); 
			}
		}

	} while (indiceCommandeObjet.first == -1);

	return  indiceCommandeObjet;
}


int VueJeu::indiceObjet(const string& chaineAchercher) {
	string chaineRechercher = transformerEnMajuscule(chaineAchercher);

	int indiceObjet = -1;

	for (int i = 0; i < nObjetsTotal; i++) {
		if (contientString(tableauObjet[i], chaineRechercher)) {
			indiceObjet = i;
			break;
		}
	}
	return indiceObjet;
}


bool VueJeu::lireCommande() {

	pair<int, int> entree = validerEntree();
	return controleur_->executerCommande(entree.first, entree.second);
}
