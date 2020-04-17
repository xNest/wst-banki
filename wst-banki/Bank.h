#pragma once
#include <vector>
#include "Definicje.h"
#include "Konto.h"

class Bank
{
private:
	NUMER_ROZLICZENIOWY_BANKU numer; // numer banku
	NUMER_RACHUNKU numer_poczatkowy_rachunkow; // numer poczatkowy rachunkow w tym banku
	int kolejny_numer_rachunku; // kolejny numer rachunku
	int kolejny_numer_transakcji; // kolejny numer transakcji (id)

	vector<Konto*> konta; // kolekcja kont (wektor wskaznikow na konto)

	bool Wplac(NUMER_RACHUNKU numer, double kwota); // Wplac kwote na obcy rachunek	
	Konto* Znajdz(NUMER_RACHUNKU numer); // Znajdz konto z numerem rachunku

public:
	Bank(NUMER_ROZLICZENIOWY_BANKU numer_rozliczeniowy_banku, NUMER_RACHUNKU numer_pierwszego_rachunku); // Konstruktor

	NUMER_RACHUNKU Otworz(string klient, string haslo); // Otworz nowy rachunek
	int Login(string klient, string haslo, NUMER_RACHUNKU numer); // Login klienta
	bool Logout(NUMER_RACHUNKU numer, int id);
	bool Wplac(NUMER_RACHUNKU numer, int id, double kwota); // Wplac kwote na rachunek klienta
	bool Wyplac(NUMER_RACHUNKU numer, int id, double kwota); // Pobierz kwote z rachunku klienta
	bool Przelej(NUMER_RACHUNKU numer, int id, double kwota, Bank* bank, NUMER_RACHUNKU obcy_rachunek); // Przelej kwote z rachunku klienta na obcy rachunek
	double Stan(NUMER_RACHUNKU numer, int id); // Zwroc stan rachunku
	NUMER_ROZLICZENIOWY_BANKU Numer(); // Zwroc numer rozliczeniowy banku
};
