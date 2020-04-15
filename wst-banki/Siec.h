#pragma once
#include <vector>
#include "Bank.h"
#include "Definicje.h"

class Siec
{
private:
	vector<Bank*> siec; // kolekcja bankow (wektor wskaznikow na Bank)

public:
	Siec(); // Konstruktor
	void Rejestruj(NUMER_ROZLICZENIOWY_BANKU numer_rozliczeniowy_banku, NUMER_RACHUNKU numer_poczatkowy_rachunkow);
	// Zarejestruj nowy bank w sieci bankow
	Bank* Znajdz(NUMER_ROZLICZENIOWY_BANKU numer_rozliczeniowy_banku); // Znajdz bank
};
