#include "ControleurJeu.hpp"
#include "VueJeu.hpp"

void ControleurJeu::changerSalle(char direction, const string& message1, const string& message2) {
	auto salle = salleCourante_->getDirection(direction);
	if (salle != nullptr) {
		afficherTexte(message1);
		salleCourante_ = salle;
		afficherTexte(salleCourante_->regarder());
	}
	else {
		afficherTexte(message2);
	}
}

bool ControleurJeu::executerCommande(int indiceCommande, int indiceObjet) {
	bool estJeuEnCours = true;
	switch (indiceCommande) {

	case(NORD):

		changerSalle(nordChar, empruntNord, cheminImpossibleNord);
		break;

	case(EST):

		changerSalle(estChar, empruntEst, cheminImpossibleEst);
		break;

	case(SUD):

		changerSalle(sudChar, empruntSud, cheminImpossibleSud);
		break;

	case(OUEST):

		changerSalle(ouestChar, empruntOuest, cheminImpossibleOuest);
		break;

	case(REGARDER):

		afficherTexte(salleCourante_->regarder());
		break;

	case(UTILISER):
		/*if (salleCourante_->getNObjects() > 0 && salleCourante_->getObjet(transformerIndiceEnObjet(indiceObjet))->getIndice() == indiceObjet) {
			utiliserObjet(indiceObjet);
		}*/
		if(salleCourante_->getNObjects() > 0 && salleCourante_->getVecObjet(indiceObjet)->getIndice() == indiceObjet)
		{
			utiliserObjet(indiceObjet);
		}
		else {
			afficherTexte("Cet objet n'est pas dans cette salle! \n");
		}
		break;

	case(SORTIR):

		afficherTexte(sortie);
		estJeuEnCours = false;
		break;

	case(AIDE):

		afficherTexte(listeCommande);
		break;
	}
	return estJeuEnCours;
};

void ControleurJeu::ajouterSalle(shared_ptr<Salle> salle) { salles_.insert(make_pair(salle->getNom(), salle)); }

shared_ptr<Salle> ControleurJeu::getSalle(string cleSalle)
{
	return salles_.at(cleSalle);
}

void ControleurJeu::ajouterObjet(shared_ptr<Objet> objet)
{
	objets_.insert(make_pair(objet->getNom(), objet));
}

void ControleurJeu::utiliserObjet(int indiceObjet) {
	switch (indiceObjet) {

	case(PIANO):
	{
		creerNouvelObjet();
		break;
	}
	case(INTERRUPTEUR):
	{
		creerSalleCachee();
		break;
	}
	case(LIVRE):
		afficherTexte(messageUtilisationLivre);
		break;
	case(CORDE):
		afficherTexte(messageUtilisationCorde);
		break;
	case(CLE):
		afficherTexte(messageUtilisationCle);
		break;
	}
}

void ControleurJeu::setSalleCourante(shared_ptr<Salle> salle) { salleCourante_ = salle; }

shared_ptr<Salle> ControleurJeu::getSalleCourante() { return salleCourante_; }

void ControleurJeu::creerSalleCachee()
{
	shared_ptr<Salle> salleCachee = make_shared<Salle>(nomSalleCachee, descriptionSalleCachee);
	shared_ptr<Salle> couloir = this->getSalleCourante();
	salleCachee->setDirections(nullptr, nullptr, nullptr, couloir);
	couloir->setDirection('E', salleCachee);
	this->ajouterSalle(salleCachee);
	afficherTexte(messageUtilisationInterrupteur);
	afficherTexte(salleCourante_->regarder());
}

void ControleurJeu::creerNouvelObjet()
{
	shared_ptr<Objet> cle = make_shared<Objet>(nomCle, descriptionCle, messageUtilisationCle, lieuActionCle, 4, true);
	shared_ptr<Salle> salon = this->getSalleCourante();
	salon->ajouterObjet(cle);
	this->ajouterObjet(cle);
	afficherTexte(messageUtilisationPiano);
	afficherTexte(salleCourante_->regarder());
}
