#include "Objet.hpp"


void Objet::setMotsCles(const string& motsCles) {
	string mots = motsCles;
	do {
		string mot;
		mots.replace(0, mots.find(',') + 1, "  ");
		this->motsCles_.push_back((mots.substr(0, mot.find(','))));

	} while (contientString(mots, caractereEnString(',')));

	this->motsCles_.push_back(motsCles);
};



string Objet::regarder() const {
	return description_ + "\n";
};



pair <string, pair<string, char>> Objet::utiliser() const {

	cout << messageUtilisation_ << "\n";
	return make_pair("  ", make_pair("  ", ' '));
};
