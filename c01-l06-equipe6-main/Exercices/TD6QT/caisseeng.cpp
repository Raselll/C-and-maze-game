/*
Travail pratique numéro:6
Fichier: caisseeng.cpp
Par: Farid Bakir 1908977, Tristan Tao 1951367, Rasel Chowdhury 2143023
Date de remise: 19/6/2022
Equipe numéro: 6
Description du programme:
Ce programme contient l'implementation des slots de notre modele.
*/
#include "caisseeng.hpp"
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <stdexcept>
CaisseEng::CaisseEng(QWidget* parent) : QMainWindow(parent)
{

}
void CaisseEng::ajouterItem(Article& item) 
{
    if (item.description_.size() == 0)
        throw std::logic_error("Il n'y a aucune description");
    else if (item.prix_ == 0)
        throw std::logic_error("Le prix est nul");

    totalAvantTaxes_ += item.prix_;
    listeArticle_.push_back(item);
    emit ajouterSignal();
}

void CaisseEng::retirerItem(Article* article)
{
    totalAvantTaxes_ -= article->prix_;
    auto it = std::remove_if(listeArticle_.begin(), listeArticle_.end(), [&](Article& a) { return &a == article; });
    listeArticle_.erase(it, listeArticle_.end());
    emit retirerSingnal();
}

void CaisseEng::reinitialiser()
{
    listeArticle_.clear();
    totalAvantTaxes_ = 0.00;
    emit reinitialiserSingnal();
}

double CaisseEng::calculerTotalTaxes(double taux)
{
    auto ajoutTaxes = [taux](double totalTaxes, Article article) {
        if (article.taxable_)
            totalTaxes += (article.prix_ * taux);
        return totalTaxes;
    };
    return std::accumulate(listeArticle_.begin(), listeArticle_.end(), 0.00, ajoutTaxes);
}

double CaisseEng::calculerTotal(double taux)
{
    float taxes = calculerTotalTaxes(taux);
    return totalAvantTaxes_ + taxes;
}