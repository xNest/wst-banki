#pragma once
#include "Definicje.h"
#include "Siec.h"
#include "Bank.h"

class Klient
{
private:
	Siec* siec; // wskaznik na siec bankow
	Bank* bank; // wskaznik na bank klienta
	string klient; // identyfikator klienta
	string haslo; // haslo klienta
	NUMER_RACHUNKU numer; // numer rachunku klienta
	int id; // identyfikator  transaksji

public:
	Klient(string klient, string haslo); // Konstruktor
	bool Otworz(Siec* siec, NUMER_ROZLICZENIOWY_BANKU numer); // Otworz nowy rachunek
	bool Login(); // Rozpocznij transakcje
	bool Logout(); // Rozpocznij transakcje
	bool Wplac(double kwota); // Wplac kwote na wlasny rachunek
	bool Wyplac(double kwota); // Pobierz kwote z wlasnego rachunku
	bool Przelej(double kwota, NUMER_ROZLICZENIOWY_BANKU bank, NUMER_RACHUNKU rachunek); // Przelej kwote z wlasnego rachunku na obcy rachunek 
	double Stan(); // Zwroc aktualny stan rachunku
	NUMER_RACHUNKU Numer();
};
