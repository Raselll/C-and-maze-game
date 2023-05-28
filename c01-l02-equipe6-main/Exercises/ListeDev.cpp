#include "ListeDeveloppeurs.hpp"
#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "gsl/span"
#include "debogage_memoire.hpp" 
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"

using namespace std;
using namespace iter;

ListeDeveloppeurs::~ListeDeveloppeurs()
{
	delete[] elements_;
}

void ListeDeveloppeurs::display() const
{
	for (const Developpeur* developpeur : spanListeDeveloppeurs())
		developpeur->display();
}

void ListeDeveloppeurs::add(Developpeur* developpeur)
{
	if (capacity_ == nElements_)
		changeCapacity(max(1, capacity_ * 2));
	elements_[nElements_++] = developpeur;
}

void ListeDeveloppeurs::remove(const Developpeur* toRemove)
{
	for (Developpeur*& developpeur : spanListeDeveloppeurs())
	{
			if (developpeur == toRemove) {
				if (nElements_ > 1) {
					developpeur = elements_[nElements_ - 1];
				} else {
					nElements_--;

			}
		}
	}
}

void ListeDeveloppeurs::changeCapacity(int newCapacity)
{
	Developpeur** newDevList = new Developpeur * [newCapacity];   
	for (int i : range(nElements_))           
		newDevList[i] = elements_[i];

	delete[] elements_;

	capacity_ = newCapacity;
	elements_ = newDevList;
}