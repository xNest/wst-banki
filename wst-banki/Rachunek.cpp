#include "Rachunek.h"

Rachunek::Rachunek()
{
	std::string accountNumber;

	for (int i = 0; i < 16; ++i)
	{
		accountNumber += std::to_string(rand() % 10);
	}

	this->numer = accountNumber;
	this->stan = 0.00;
}

Rachunek::Rachunek(NUMER_RACHUNKU numer)
{
	this->numer = numer;
	this->stan = 0.00;
}

bool Rachunek::Wplata(double kwota)
{
	this->stan += kwota;
	return true;
}

bool Rachunek::Wyplata(double kwota)
{
	if (this->stan - kwota > 0)
	{
		this->stan -= kwota;
		return true;
	}

	return false;
}

NUMER_RACHUNKU Rachunek::Numer()
{
	return this->numer;
}

double Rachunek::Stan()
{
	return this->stan;
}
