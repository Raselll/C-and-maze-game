/*
Travail pratique numéro:6
Fichier: caissewindow.hpp
Par: Farid Bakir 1908977, Tristan Tao 1951367, Rasel Chowdhury 2143023
Date de remise: 19/6/2022
Equipe numéro: 6
Description du programme:
Ce programme contient les slots de notre vue.
*/

#ifndef CAISSEWINDOW_HPP
#define CAISSEWINDOW_HPP
#include"caisseeng.hpp"
#include <QMainWindow>
#include<memory>

Q_DECLARE_METATYPE(Article*);
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
    class caisseWindow;
}
QT_END_NAMESPACE

class caisseWindow : public QMainWindow
{
    Q_OBJECT

public:
    caisseWindow(QWidget* parent = nullptr);
    ~caisseWindow();
    void charger();
public slots:
    void ajouter();
    void retirer();
    void actualiser();


private:
    Ui::caisseWindow* ui_;
    void setupUi();
    
    CaisseEng caisse_;
};
#endif 
