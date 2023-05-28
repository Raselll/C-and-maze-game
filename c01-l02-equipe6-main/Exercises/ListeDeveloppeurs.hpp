#pragma once
#include "Developpeur.hpp"
#include "gsl/span"

using namespace gsl;

class ListeDeveloppeurs
{
private:
	span<Developpeur*> spanListeDeveloppeurs() const { return span(elements_, nElements_); }
	void changeCapacity(int newCapacity);

	int capacity_;
	int nElements_;
	Developpeur** elements_ = 0;

public:
	ListeDeveloppeurs() = default;
	~ListeDeveloppeurs();

	void add(Developpeur* developpeur);
	void remove(const Developpeur* toRemove);

	void display() const;
};
