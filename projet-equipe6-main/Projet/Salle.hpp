#pragma once
#include <map>
#include "Objet.hpp"
class Salle {
public:

	Salle(const string& nom, const string& description) :
		nom_(nom), description_(description) {};

	void setDirections(const shared_ptr<Salle> nord, const shared_ptr<Salle> est, const shared_ptr<Salle> sud, const shared_ptr<Salle> ouest);
	void setDirection(const char& direction, const shared_ptr<Salle> salle);
	void ajouterObjet(shared_ptr<Objet> objet);
	shared_ptr<Objet> getObjet(const string cleObjet);
	string getNomObjet(const string cleObjet);
	shared_ptr<Objet> getVecObjet(const int indiceObjet);
	int getNObjects() { return (int)objets_.size(); }
	string regarder() const;
	string getNom() const;
	string getDescription() const;
	shared_ptr<Salle> getDirection(const char direction) const;

private:

	string nom_;
	string description_;
	vector<shared_ptr<Objet>> vecObjets_;
	map<string, shared_ptr<Objet>> objets_;
	map<char, shared_ptr<Salle>> directions_;
};
