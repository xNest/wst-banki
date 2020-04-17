#include "Klient.h"

Klient::Klient(string klient, string haslo)
{
	this->klient = klient;
	this->haslo = haslo;
}

bool Klient::Otworz(Siec* siec, NUMER_ROZLICZENIOWY_BANKU numer)
{
	this->siec = siec;
	
	this->bank = this->siec->Znajdz(numer);
	this->numer = bank->Otworz(this->klient, this->haslo);
	
	return true;
}

bool Klient::Login()
{
	this->id = this->bank->Login(this->klient, this->haslo, this->numer);

	if (this->id != LOGIN_NIEMOZLIWY)
	{
		return true;
	}

	return false;
}

bool Klient::Logout()
{
	return this->bank->Logout(this->numer, this->id);
}

bool Klient::Wplac(double kwota)
{
	return this->bank->Wplac(this->numer, this->id, kwota);
}

bool Klient::Wyplac(double kwota)
{
	return this->bank->Wyplac(this->numer, this->id, kwota);
}

bool Klient::Przelej(double kwota, NUMER_ROZLICZENIOWY_BANKU bank, NUMER_RACHUNKU rachunek)
{
	return this->bank->Przelej(this->numer, this->id, kwota, this->siec->Znajdz(bank), rachunek);
}

double Klient::Stan()
{
	return this->bank->Stan(this->numer, this->id);
}

NUMER_RACHUNKU Klient::Numer()
{
	return this->numer;
}
