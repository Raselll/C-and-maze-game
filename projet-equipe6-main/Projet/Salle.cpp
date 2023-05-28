#include "Salle.hpp"

string Salle::getNom() const { return nom_ + "\n"; }

string Salle::getDescription() const { return description_ + "\n"; }

void Salle::setDirections(const shared_ptr<Salle> nord, const shared_ptr<Salle> est, const shared_ptr<Salle> sud, const shared_ptr<Salle> ouest) {

    directions_.insert(pair<char, shared_ptr<Salle>>('N', nord));
    directions_.insert(pair<char, shared_ptr<Salle>>('E', est));
    directions_.insert(pair<char, shared_ptr<Salle>>('S', sud));
    directions_.insert(pair<char, shared_ptr<Salle>>('O', ouest));
}

void Salle::setDirection(const char& direction, const shared_ptr<Salle> salle) {
    directions_[direction] = salle;
}

shared_ptr<Objet> Salle::getObjet(const string cleObjet) {
    if (cleObjet == "") {
        shared_ptr<Objet> exception = make_shared<Objet>("EXCEPTION", "LEVEE LORSQUE OBJET N'EST PAS DANS SALLE", "HAHAH", "", -1, false);
        return exception;
    }
    return objets_.at(cleObjet);
}

shared_ptr<Objet> Salle::getVecObjet(const int indiceObjet)
{
    if(vecObjets_.size() > 0)
    {
        for(int i = 0; i < vecObjets_.size(); i++)
        {
            if(vecObjets_[i]->getIndice() == indiceObjet)
            {
                return vecObjets_[i];
                break;
            }
            else
            {
                return nullptr;
            }
        }
    }
    else
    {
        return nullptr;
    }
}

string Salle::getNomObjet(const string cleObjet) {
    return objets_.at(cleObjet)->getNom();
}

void Salle::ajouterObjet(shared_ptr<Objet> objet) {
    objets_.insert(make_pair(objet->getNom(), objet));
    vecObjets_.push_back(objet);
}

shared_ptr<Salle> Salle::getDirection(const char direction) const {
    return directions_.at(direction);
}

string Salle::regarder() const {
    string string = nom_ + "\n" + description_ + "\n";

    if (getDirection('N') != nullptr) { string += directions_.at('N')->nom_ + " est au Nord (N) \n "; };
    if (getDirection('E') != nullptr) { string += directions_.at('E')->nom_ + " est a l'Est (E) \n "; };
    if (getDirection('S') != nullptr) { string += directions_.at('S')->nom_ + " est au Sud (S) \n "; };
    if (getDirection('O') != nullptr) { string += directions_.at('O')->nom_ + " est a l'Ouest (O) \n "; };

    for (auto&& objet : objets_)
        if (objet.second->isAffichable()) {
            string += objet.second->getNom() + "\n" + objet.second->getDescription() + "\n";
        }


    return string;
}
