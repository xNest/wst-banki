// wst-banki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "Siec.h"

#define MBANK "11402004"
#define ING "10501272"

int main()
{
	Siec* siec = new Siec();

	siec->Rejestruj(MBANK, "0000000000000000");
	siec->Rejestruj(ING, "0000000000000000");

	Bank* mbank = siec->Znajdz(MBANK);
	Bank* ing = siec->Znajdz(ING);

	NUMER_RACHUNKU klientA = mbank->Otworz("klientA", "hasloA");
	NUMER_RACHUNKU klientB = ing->Otworz("klientB", "hasloB");

	int klientASession = mbank->Login("klientA", "hasloA", klientA);
	int klientBSession = ing->Login("klientB", "hasloB",klientB);

	mbank->Wplac(klientA, klientASession, 100.00);
	mbank->Przelej(klientA, klientASession, 30, ing, klientB);

	ing->Wyplac(klientB, klientBSession, 10.00);

	std::cout << "Stan konta A: " << mbank->Stan(klientA,klientASession) << "\n";
	std::cout << "Stan konta B: " << ing->Stan(klientB, klientBSession) << "\n";

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
