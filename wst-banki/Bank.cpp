#include "Bank.h"

Bank::Bank(NUMER_ROZLICZENIOWY_BANKU numer_rozliczeniowy_banku, NUMER_RACHUNKU numer_pierwszego_rachunku)
{
	this->numer = numer_rozliczeniowy_banku;
	this->numer_poczatkowy_rachunkow = numer_pierwszego_rachunku;
	this->kolejny_numer_rachunku = 1;
	this->kolejny_numer_transakcji = 1;
}

NUMER_RACHUNKU Bank::Otworz(string klient, string haslo)
{
	NUMER_RACHUNKU accountNumber = to_string(
		atoi(this->numer_poczatkowy_rachunkow.c_str()) + this->kolejny_numer_rachunku);
	Konto* konto = new Konto(klient, haslo, accountNumber);

	this->konta.push_back(konto);
	this->kolejny_numer_rachunku++;

	return accountNumber;
}


int Bank::Login(string klient, string haslo, NUMER_RACHUNKU numer)
{
	int sessionId = this->Znajdz(numer)->Login(klient, haslo, this->kolejny_numer_transakcji);

	if (sessionId > 0)
	{
		this->kolejny_numer_transakcji++;
	}

	return sessionId;
}

bool Bank::Logout(NUMER_RACHUNKU numer, int id)
{
	return this->Znajdz(numer)->Logout(id);
}


bool Bank::Wplac(NUMER_RACHUNKU numer, int id, double kwota)
{
	return this->Znajdz(numer)->Wplata(id, kwota);
}

bool Bank::Wyplac(NUMER_RACHUNKU numer, int id, double kwota)
{
	return this->Znajdz(numer)->Wyplata(id, kwota);
}

bool Bank::Przelej(NUMER_RACHUNKU numer, int id, double kwota, Bank* bank, NUMER_RACHUNKU obcy_rachunek)
{
	Konto* konto = this->Znajdz(numer);
	Konto* konto2 = bank->Znajdz(obcy_rachunek);
	if (konto && konto2 && konto->Wyplata(id, kwota) && konto2->Wplata(NULL, kwota))
	{
		return true;
	}

	return false;
}


double Bank::Stan(NUMER_RACHUNKU numer, int id)
{
	return this->Znajdz(numer)->Stan(id);
}

NUMER_ROZLICZENIOWY_BANKU Bank::Numer()
{
	return this->numer;
}


bool Bank::Wplac(NUMER_RACHUNKU numer, double kwota)
{
	return this->Znajdz(numer)->Wplata(NULL, kwota);
}

Konto* Bank::Znajdz(NUMER_RACHUNKU numer)
{
	return *find_if(this->konta.begin(), this->konta.end(), [numer](Konto* p)
	{
		return p->Numer(numer);
	});
}
