/*
Travail pratique numéro:6
Fichier: Article.hpp
Par: Farid Bakir 1908977, Tristan Tao 1951367, Rasel Chowdhury 2143023
Date de remise: 19/6/2022
Equipe numéro: 6
Description du programme:
Ce programme contient la structure Article qu'on utilise pour creer les articles
*/
#pragma once
#include<string>
struct Article {
    std::string description_;
    double prix_ = 0;
    bool taxable_ = false;
};

