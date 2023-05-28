#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "message.h"
using namespace std;

class Objet {
public:
	Objet(const string& nom, const string& description, const string& messageUtilisation, const string& salleCourante, int indice, bool affichable)
		:nom_(nom), description_(description), messageUtilisation_(messageUtilisation), salleCourante_(salleCourante), indice_(indice), affichable_(affichable) { };

	pair <string, pair<string, char>> utiliser() const;
	string regarder() const;
	void setMotsCles(const string& motsCles);

	string getNom() const { return nom_/* + "\n"*/; }
	string getDescription() const { return description_ /* + "\n"*/; }
	string getMessageUtilisation() const { return messageUtilisation_ /* + "\n"*/; }
	string getSalleCourante() const { return salleCourante_ /* + "\n"*/; }
	bool isAffichable() { return affichable_; }
	void setAffichable(bool choice) { affichable_ = choice; }
	int getIndice() const { if(this == nullptr) { return -1; } else return indice_; }
	vector<string>& getMotsCles() { return motsCles_; }

private:
	string nom_;
	string description_;
	string messageUtilisation_;
	string salleCourante_;
	int indice_ = -1;
	bool affichable_;
	vector<string> motsCles_;

};
