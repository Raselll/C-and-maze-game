#pragma once
#include "salle.hpp"
#include <memory>
#include <map>
#include "message.h"

class ControleurJeu {
public:

	void ajouterSalle(shared_ptr<Salle> salle);
	void ajouterObjet(shared_ptr<Objet> objet);
	void utiliserObjet(int indiceObjet);
	bool executerCommande(int indiceCommande, int indiceObjet);
	shared_ptr<Salle> getSalleCourante();
	shared_ptr<Salle> getSalle(string cleSalle);
	void setSalleCourante(shared_ptr<Salle>);
	void changerSalle(char direction, const string& message1, const string& message2);
	void creerSalleCachee();
	void creerNouvelObjet();

private:

	map<string, shared_ptr<Salle>> salles_;
	shared_ptr<Salle> salleCourante_;
	map<string, shared_ptr<Objet>> objets_;
};
