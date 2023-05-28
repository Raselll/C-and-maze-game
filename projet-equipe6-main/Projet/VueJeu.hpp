#pragma once
#include "ControleurJeu.hpp"


class VueJeu {
public:

	VueJeu(unique_ptr<ControleurJeu> controleur) : controleur_(move(controleur)) {
		initialiser();
	};
	void initialiser();
	void presentationJeu();
	bool lireCommande();
	void afficherInviteCommande();

private:

	string transformerEnCommandeStandard(const string& chaineATransformer);

	pair<int, int> validerEntree();
	int indiceCommande(const string& chaineAchercher);

	int indiceObjet(const string& chaineAchercher);

	unique_ptr<ControleurJeu> controleur_;
};

