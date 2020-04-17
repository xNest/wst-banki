#include "Konto.h"

Konto::Konto(string klient, string haslo, NUMER_RACHUNKU numer)
{
	this->klient = klient;
	this->haslo = haslo;
	this->rachunek = Rachunek(numer);
}

int Konto::Login(string klient, string haslo, int id)
{
	if (this->klient == klient && this->haslo == haslo)
	{
		this->id = id;
		return this->id;
	}

	return this->id;
}

bool Konto::Logout(int id)
{
	if (this->id == id && this->id != LOGIN_NIEMOZLIWY)
	{
		this->id = LOGIN_NIEMOZLIWY;
		return true;
	}

	return false;
}

bool Konto::Wplata(int id, double kwota)
{
	return this->rachunek.Wplata(kwota);
}

bool Konto::Wyplata(int id, double kwota)
{
	if (this->id == id && this->id != LOGIN_NIEMOZLIWY)
	{
		return this->rachunek.Wyplata(kwota);
	}

	return false;
}

double Konto::Stan(int id)
{
	if (this->id == id && this->id != LOGIN_NIEMOZLIWY)
	{
		return this->rachunek.Stan();
	}

	return 0;
}

bool Konto::Numer(NUMER_RACHUNKU numer)
{
	return this->rachunek.Numer() == numer;
}

bool Konto::Klient(string klient)
{
	return this->klient == klient;
}
