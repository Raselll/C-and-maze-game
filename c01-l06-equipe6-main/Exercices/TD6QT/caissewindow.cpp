/*
Travail pratique numéro:6
Fichier: caissewindow.cpp
Par: Farid Bakir 1908977, Tristan Tao 1951367, Rasel Chowdhury 2143023
Date de remise: 19/6/2022
Equipe numéro: 6
Description du programme:
Ce programme contient l'implementation des slots et signaux de notre vue.
*/

#include "caissewindow.hpp"
#include "ui_caissewindow.h"
#include "Article.hpp"
#include"caisseeng.hpp"
#include <QTimer>
#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <stdexcept>


caisseWindow::caisseWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui_(new Ui::caisseWindow)
{
	ui_->setupUi(this);
	setupUi();
	actualiser();
}
caisseWindow::~caisseWindow()
{
	delete ui_;
}

void caisseWindow::setupUi()
{
	connect(&caisse_, SIGNAL(ajouterSignal()), this, SLOT(actualiser()));
	connect(&caisse_, SIGNAL(retirerSingnal()), this, SLOT(actualiser()));
	connect(&caisse_, SIGNAL(reinitialiserSingnal()), this, SLOT(actualiser()));
	connect(ui_->ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
	connect(ui_->retirer, SIGNAL(clicked()), this, SLOT(retirer()));
	connect(ui_->reinitialiser, SIGNAL(clicked()), &caisse_, SLOT(reinitialiser()));
	ui_->lineEditPrix->setValidator(new QDoubleValidator(0, 9999, 2, this));

}

void caisseWindow::charger() 
{
	ui_->ItemListe->clear();
	for (auto& item : caisse_.listeArticle_)
	{
		QString str = QString::fromStdString(item.description_ + "\t")
			+ QString::number(item.prix_, 'f', 2);
		if (item.taxable_)
			str += "\t + Taxes";

		QListWidgetItem* itemQliste = new QListWidgetItem(str, ui_->ItemListe);
		itemQliste->setData(Qt::UserRole, QVariant::fromValue<Article*>(&item));
	}
}
void caisseWindow::actualiser()
{
	ui_->retirer->setDisabled(caisse_.listeArticle_.size() == 0);
	ui_->lineArticle->clear();
	ui_->lineEditPrix->clear();
	ui_->taxtable->setCheckState(Qt::Unchecked);

	QString sousTotal = QString::number(caisse_.totalAvantTaxes_, 'f', 2);
	QString taxes = QString::number(caisse_.calculerTotalTaxes(CaisseEng::tauxTax), 'f', 2);
	QString total = QString::number(caisse_.calculerTotal(CaisseEng::tauxTax), 'f', 2);

	ui_->totalAvantTax_2->setText(sousTotal);
	ui_->totalTax_2->setText(taxes);
	ui_->total_2->setText(total);
	charger();
}
void caisseWindow::ajouter() 
{
	Article item;
	item.description_ = ui_->lineArticle->text().toStdString();
	item.prix_ = ui_->lineEditPrix->text().toFloat();
	item.taxable_ = ui_->taxtable->isChecked();

	try
	{
		caisse_.ajouterItem(item);
	}
	catch (std::logic_error& erreur)
	{
		QMessageBox::critical(0, "Erreur", erreur.what());
	}

}
void caisseWindow::retirer() 
{
	if (caisse_.listeArticle_.size() != 0)
	{
		ui_->retirer->activateWindow();
		QListWidgetItem* item = ui_->ItemListe->currentItem();
		if (item != nullptr)
		{
			Article* ptrItem = item->data(Qt::UserRole).value<Article*>();
			caisse_.retirerItem(ptrItem);

		}
	}
}
