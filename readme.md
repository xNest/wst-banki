**Banki - wersja podstawowa**

1. Bardzo krótko o programowaniu obiektowym

Programowanie obiektowe polega na tworzeniu programów, które składają się z obiektów. Obiekty charakteryzują się abstrakcją i hermetyzacją. Abstrakcja polega na modelowaniu najistotniejszych cech jakiegoś rzeczywistego pojęcia. Na przykład programowanie obiektowego może modelować arytmetykę liczb zespolonych albo usługi bankowe. Hermetyzacja polega na ukryciu danych i funkcji prywatnych oraz udostepnieniu danych i funkcji publicznych. Abstrakcja i hermetyzacja są rozwinięciem koncepcji abstrakcyjnych typów danych (typów tworzonych przez programistę) i modularyzacji programów. W programowaniu obiektowym dąży się także do wielokrotnego wykorzystania raz napisanego kodu. Jedna z dróg prowadzących do tego celu jest użycie programów generycznych, tzn. adaptowalnych do różnych typów danych.

Podstawową konstrukcją programowania obiektowego w C++ jest klasa. Jest to rozszerzenie znanej z języka C konstrukcji struct. Klasa zawiera dane i metody prywatne oraz dane i metody publiczne (hermetyzacja). Klasa może zawierać lub nawet wywodzić się z prostszych klas (dziedziczenie). Klasa rozróżnia deklaracje (nagłówki \*.h) i definicje (implementacje \*.cpp). _Klasa_ dla _obiektów_ jest tym, czym jest (abstrakcyjny) _typ danych_ dla _zmiennych_ w tradycyjnym programowaniu. C++ oferuje również kolekcje generyczne, takie jak wektor, które mogą przechowywać dane różnych typów.

Program Bankirealizuje dwa główne postulaty programowania obiektowego: abstrakcję i hermetyzację. Program składa się z (aktywnych) obiektów typu Klient, które korzystają z usług (pasywnych) obiektów typu Bank. Klasa Bank modeluje podstawowe usługi bankowe. Do implementacji sieci banków i listy kont bankowych wykorzystane są klasy generyczne vector i map.

1. Program Banki

Program Banki składa się z trzech części: usług bankowych zrealizowanych przez hierarchię klas Rachunek \&lt; Konto \&lt; Bank \&lt; Siec, z programu głównego, który korzysta z tych usług oraz z klasy pośredniczej Siec, która ułatwia programowi głównemu korzystanie z usług i ukrywa przed nim pewne szczegóły dostępu do kont.

  1. Definicje

W pliku nagłówkowymDefinicje.h zdefiniowano nazwy dwóch istotnych dla projektu zmiennych typustring: numeru rozliczeniowego banku (w przypadku polskich banków 8 znaków) i numeru rachunku (16 znaków). Definicje te nie są konieczne, mogą jednak ułatwić przyszłe rozszerzenia programu takie jak zastąpienie zwykłego numeru rachunku międzynarodowym numerem rachunku bankowego.

Oprócz tego zdefiniowane są tu dwie stałe numeryczne. Użycie nazwy zamiast wartości liczbowej powinno poprawić czytelność programu.

Inkluzja Definicje.h uwalnia pozostałe klasy projektu od inkluzji \&lt;string\&gt; i\&lt;iostream\&gt;.

```cpp
#include <string>
#include <iostream>

typedef string NUMER_ROZLICZENIOWY_BANKU; // numer rozliczeniowy banku (8 znakow)
typedef string NUMER_RACHUNKU; // numer rachunku (16 znakow)
const int WPLATA_MOZLIWA = 0;
const int LOGIN_NIEMOZLIWY = -1;
```

  1. Klasa Rachunek

Klasa Rachunek jest prostym kontenerem, którego prywatne dane to numer rachunku i aktualny stan rachunku. Każdy rachunek ma swój numer (parametr konstruktora). Publiczne metody umożliwiają wpłatę i wypłatę. Wpłata jest zawsze możliwa. Wypłata, która prowadzi do ujemnego stanu konta, jest odrzucana. Metody publiczne Numer()i Stan() informują odpowiednio o numerze i o aktualnym stanie rachunku.

```cpp
#include "Definicje.h"

class Rachunek
{
private:
  NUMER_RACHUNKU numer; // numer rachunku
  double stan; // aktualny stan rachunku
public:
  Rachunek(); // Standardowy konstruktor bez parametrow
  Rachunek(NUMER_RACHUNKU numer); // Konstruktor
  bool Wplata(double kwota); // Wplac kwote na rachunek
  bool Wyplata(double kwota); // Pobierz kwote z rachunku
  NUMER_RACHUNKU Numer(); // Pokaz numer rachunku
  double Stan(); // Pokaz stan rachunku
};
```

  1. Klasa Konto
Konto bankowe to rachunek klienta (jeden klient ma jeden rachunek). Klasa Konto zawiera klasę Rachunek, identyfikator i hasło klienta oraz identyfikator dostępu do rachunku. Parametrami konstruktora są identyfikator i hasło klienta oraz numer rachunku. Bezpieczny dostęp do rachunku gwarantuje metoda Login(), która sprawdza hasło klienta i zapamiętuje identyfikator dostępu. Klasa Kontopowtarza metody klasy wewnętrznej Rachunek „zapakowane&quot; w kod sprawdzający identyfikator dostępu. Metody Numer(numer) i Klient(klient) są funkcjami pomocnymi w znajdywaniu kont według różnych kryteriów (patrz klasa Bank).

```cpp
#include "Definicje.h"
#include "Rachunek.h"

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
```

  1. Klasa Bank

Klasa Bank jest centralną klasą projektu. Bank to kolekcja kont bankowych (dokładnie: wektor wskaźników na obiekt typu Konto). Wektor jest kolekcją bez klucza, dlatego znalezienie konta o danym numerze wymaga liniowego przeszukania wektora (iteracji po indeksie w prywatnej metodzie Znajdz()).

Parametrami konstruktora są numer rozliczeniowy banku i numer początkowy rachunków w tym banku. Metoda Otworz() otwiera nowe konto dla klienta banku: generuje numer nowego konta, tworzy obiekt klasy Konto i zapisuje go do wektora kont. Parametrami tej metody są identyfikator i hasło klienta.

Metoda Login() wymaga, żeby konto o podanym identyfikatorze klienta i podanym haśle już istniało i - jeśli tak jest - generuje identyfikator bezpiecznego dostępu.

Klasa Bankpowtarza metody publiczne klasy wewnętrznej Konto „zapakowane&quot; w kod znajdujący konto w wektorze kont.

Metoda Przelej()wymaga bardziej szczegółowego objaśnienia. Implementuje ona przelew kwoty z własnego konta na obce konto. Obce konto identyfikowane jest przez wskaźnik na obcy bank i numer rachunku w tym banku. Przelew jest realizowany w dwóch krokach. Najpierw kwota jest wypłacana z własnego konta (dostęp za pomocą publicznej metody Wyplac()). Następnie ta sama kwota jest wpłacana na obce konto za pomocą prywatnej metody Wplac(). Bank źródłowy staje się tu klientem banku docelowego, nie posiadając ani identyfikatora klienta ani jego hasła. Żeby rozwiązać problem dostępu, dopuszcza się wpłaty bez identyfikatora dostępu. Metoda Wplac() jest wewnątrz klasy Bank metodą prywatną, między obiektami typu Bank jest jednak widoczna (bank źródłowy woła metodę Wplac() banku docelowego).

```cpp
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
  bool Przelej(NUMER_RACHUNKU numer, int id, double kwota, Bank* bank, NUMER_RACHUNKU obcy_rachunek);
  // Przelej kwote z rachunku klienta na obcy rachunek
  double Stan(NUMER_RACHUNKU numer, int id); // Zwroc stan rachunku
  NUMER_ROZLICZENIOWY_BANKU Numer(); // Zwroc numer rozliczeniowy banku
};
```

  1. Klasa Siec

Sieć to kolekcja banków (dokładnie: wektor wskaźników na obiekt Bank). Metoda Rejestruj() tworzy nowy obiekt Bank i dodaje go do kolekcji banków. Metoda Znajdz() szuka w wektorze banku o podanym numerze rozliczeniowym.

```cpp

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
```

  1. Klasa Klient

Klasa Klient korzysta z usług klas Siec oraz Bank (deleguje wykonanie usług bankowych do odpowiednich klas). Celem klasy jest udostepnienie możliwie prostych w użyciu metod dla programu głównego. Klient jest definiowany przez identyfikator i hasło (parametry konstruktora). Klasa Klient ukrywa w części prywatnej identyfikator dostępu do konta.

```cpp
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
  bool Przelej(double kwota, NUMER_ROZLICZENIOWY_BANKU bank, NUMER_RACHUNKU rachunek);
  // Przelej kwote z wlasnego rachunku na obcy rachunek 
  double Stan(); // Zwroc aktualny stan rachunku
  NUMER_RACHUNKU Numer();
};
```

  1. Program główny main

Program główny składa się z obiektów typu Klient, które korzystają z usług obiektów typu Bank. W pierwszej części programu obiekt klasy Siecpośredniczy w tworzeniu obiektów typu Bank (metoda Rejestruj()). W drugiej części tworzone są obiekty typu Klient, które następnie korzystają z usług bankowych.
 W programie głównym zrealizowano przykładowy prosty scenariusz:

- dwa banki: mBank i ING
- dwóch klientów: A i B

- A wpłaca kwotę na własne konto
- A przekazuje kwotę na konto B

- B wypłaca kwotę ze swojego konta
- A i B informują o końcowym stanie swoich kont.
