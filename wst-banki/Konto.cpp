#include "Definicje.h"
#include "Konto.h"
#include "Rachunek.h"

#include <string>

using namespace std;

class Konto
{
private:
	Rachunek rachunek; // rachunek (wywoluje standardowy konstruktor)
	string klient; // identyfikator klienta
	string haslo; // haslo klienta
	int id = LOGIN_NIEMOZLIWY; // identyfikator dostepu do konta 

public:
	Konto(string klient, string haslo, NUMER_RACHUNKU numer); // Konstruktor 
	int Login(string klient, string haslo, int id); // Bezpieczny dostep do konta
	bool Logout(int id); // Koniec dostepu do konta
	bool Wplata(int id, double kwota); // Wplac na konto
	bool Wyplata(int id, double kwota); // Wyplac z konta
	double Stan(int id); // Zwroc stan konta
	bool Numer(NUMER_RACHUNKU numer); // Porownaj numer rachunku
	bool Klient(string klient); // Porownaj identyfikator klienta
};
