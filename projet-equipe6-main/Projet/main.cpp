//Auteurs: Bakir, Farid (1908977), Chowdhury, Rasel (2143023), et Tao, Tristan (1951367)
//Description: Fonction principale du jeu.
//Date: 16 juin 2022
//Crée le 30 mai 2022

#include "VueJeu.hpp"

int main() {

	unique_ptr<ControleurJeu> controleurJeu = make_unique<ControleurJeu>();
	unique_ptr<VueJeu> vueJeu = make_unique<VueJeu>(move(controleurJeu));
	bool estJeuEnCours;

	do {
		vueJeu->afficherInviteCommande();
		estJeuEnCours = vueJeu->lireCommande();
	} while (estJeuEnCours);

	return 0;
}
