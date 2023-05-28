/*
Travail pratique numéro:6
Fichier: caisseeng.hpp
Par: Farid Bakir 1908977, Tristan Tao 1951367, Rasel Chowdhury 2143023
Date de remise: 19/6/2022
Equipe numéro: 6
Description du programme:
Ce programme contient les slots et les signaux de notre modele, ainsi que la declaration du vecteur
dans lequel on stocke nos articles
*/

#ifndef CAISSEENG_HPP
#define CAISSEENG_HPP

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<string>
#include "Article.hpp"
class CaisseEng : public QMainWindow
{
    Q_OBJECT
public:
    explicit CaisseEng(QWidget* parent = nullptr);
    static inline const double tauxTax = 0.1475;
    double totalAvantTaxes_ = 0.00;
    std::vector<Article> listeArticle_;

public slots:
    void ajouterItem(Article& item);
    void retirerItem(Article* item);
    double calculerTotalTaxes(double taux);
    double calculerTotal(double taux);
    void reinitialiser();

signals:
    void ajouterSignal();
    void retirerSingnal();
    void reinitialiserSingnal();
};


#endif 
