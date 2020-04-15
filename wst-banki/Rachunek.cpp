#include "Rachunek.h"

Rachunek::Rachunek()
{
}

Rachunek::Rachunek(NUMER_RACHUNKU numer)
{
	this->numer = numer;
	/* Assign default amount*/
	this->stan = 100.00;
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
