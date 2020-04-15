**Banki - wersja podstawowa**

1. Bardzo krótko o programowaniu obiektowym

Programowanie obiektowe polega na tworzeniu programów, które sk³adaj¹ siê z obiektów. Obiekty charakteryzuj¹ siê abstrakcj¹ i hermetyzacj¹. Abstrakcja polega na modelowaniu najistotniejszych cech jakiegoœ rzeczywistego pojêcia. Na przyk³ad programowanie obiektowego mo¿e modelowaæ arytmetykê liczb zespolonych albo us³ugi bankowe. Hermetyzacja polega na ukryciu danych i funkcji prywatnych oraz udostepnieniu danych i funkcji publicznych. Abstrakcja i hermetyzacja s¹ rozwiniêciem koncepcji abstrakcyjnych typów danych (typów tworzonych przez programistê) i modularyzacji programów. W programowaniu obiektowym d¹¿y siê tak¿e do wielokrotnego wykorzystania raz napisanego kodu. Jedna z dróg prowadz¹cych do tego celu jest u¿ycie programów generycznych, tzn. adaptowalnych do ró¿nych typów danych.

Podstawow¹ konstrukcj¹ programowania obiektowego w C++ jest klasa. Jest to rozszerzenie znanej z jêzyka C konstrukcji struct. Klasa zawiera dane i metody prywatne oraz dane i metody publiczne (hermetyzacja). Klasa mo¿e zawieraæ lub nawet wywodziæ siê z prostszych klas (dziedziczenie). Klasa rozró¿nia deklaracje (nag³ówki \*.h) i definicje (implementacje \*.cpp). _Klasa_ dla _obiektów_ jest tym, czym jest (abstrakcyjny) _typ danych_ dla _zmiennych_ w tradycyjnym programowaniu. C++ oferuje równie¿ kolekcje generyczne, takie jak wektor, które mog¹ przechowywaæ dane ró¿nych typów.

Program Bankirealizuje dwa g³ówne postulaty programowania obiektowego: abstrakcjê i hermetyzacjê. Program sk³ada siê z (aktywnych) obiektów typu Klient, które korzystaj¹ z us³ug (pasywnych) obiektów typu Bank. Klasa Bank modeluje podstawowe us³ugi bankowe. Do implementacji sieci banków i listy kont bankowych wykorzystane s¹ klasy generyczne vector i map.

1. Program Banki

Program Banki sk³ada siê z trzech czêœci: us³ug bankowych zrealizowanych przez hierarchiê klas Rachunek \&lt; Konto \&lt; Bank \&lt; Siec, z programu g³ównego, który korzysta z tych us³ug oraz z klasy poœredniczej Siec, która u³atwia programowi g³ównemu korzystanie z us³ug i ukrywa przed nim pewne szczegó³y dostêpu do kont.

  1. Definicje

W pliku nag³ówkowymDefinicje.h zdefiniowano nazwy dwóch istotnych dla projektu zmiennych typustring: numeru rozliczeniowego banku (w przypadku polskich banków 8 znaków) i numeru rachunku (16 znaków). Definicje te nie s¹ konieczne, mog¹ jednak u³atwiæ przysz³e rozszerzenia programu takie jak zast¹pienie zwyk³ego numeru rachunku miêdzynarodowym numerem rachunku bankowego.

Oprócz tego zdefiniowane s¹ tu dwie sta³e numeryczne. U¿ycie nazwy zamiast wartoœci liczbowej powinno poprawiæ czytelnoœæ programu.

Inkluzja Definicje.h uwalnia pozosta³e klasy projektu od inkluzji \&lt;string\&gt; i\&lt;iostream\&gt;.

```cpp

#include\&lt;string\&gt;

#include\&lt;iostream\&gt;

typedefstringNUMER\_ROZLICZENIOWY\_BANKU; // numer rozliczeniowy banku (8 znakow)

typedefstringNUMER\_RACHUNKU; // numer rachunku (16 znakow)

constint WPLATA\_MOZLIWA = 0;

constint LOGIN\_NIEMOZLIWY = -1;

```

  1. Klasa Rachunek

Klasa Rachunek jest prostym kontenerem, którego prywatne dane to numer rachunku i aktualny stan rachunku. Ka¿dy rachunek ma swój numer (parametr konstruktora). Publiczne metody umo¿liwiaj¹ wp³atê i wyp³atê. Wp³ata jest zawsze mo¿liwa. Wyp³ata, która prowadzi do ujemnego stanu konta, jest odrzucana. Metody publiczne Numer()i Stan() informuj¹ odpowiednio o numerze i o aktualnym stanie rachunku.

```cpp

#include&quot;Definicje.h&quot;

classRachunek

{

private:

NUMER\_RACHUNKU numer; // numer rachunku

double stan; // aktualny stan rachunku

public:

Rachunek(); // Standardowy konstruktor bez parametrow

Rachunek(NUMER\_RACHUNKUnumer); // Konstruktor

bool Wplata(doublekwota); // Wplac kwote na rachunek

bool Wyplata(doublekwota); // Pobierz kwote z rachunku

NUMER\_RACHUNKU Numer(); // Pokaz numer rachunku

double Stan(); // Pokaz stan rachunku

};

```

  1. Klasa Konto
Konto bankowe to rachunek klienta (jeden klient ma jeden rachunek). Klasa Konto zawiera klasê Rachunek, identyfikator i has³o klienta oraz identyfikator dostêpu do rachunku. Parametrami konstruktora s¹ identyfikator i has³o klienta oraz numer rachunku. Bezpieczny dostêp do rachunku gwarantuje metoda Login(), która sprawdza has³o klienta i zapamiêtuje identyfikator dostêpu. Klasa Kontopowtarza metody klasy wewnêtrznej Rachunek „zapakowane&quot; w kod sprawdzaj¹cy identyfikator dostêpu. Metody Numer(numer) i Klient(klient) s¹ funkcjami pomocnymi w znajdywaniu kont wed³ug ró¿nych kryteriów (patrz klasa Bank).

```cpp

#include&quot;Definicje.h&quot;

#include&quot;Rachunek.h&quot;

usingnamespace std;

classKonto

{

private:

Rachunek rachunek; // rachunek (wywoluje standardowy konstruktor)

string klient; // identyfikator klienta

string haslo; // haslo klienta

int id = LOGIN\_NIEMOZLIWY; // identyfikator dostepu do konta

public:

Konto(stringklient, stringhaslo, NUMER\_RACHUNKUnumer); // Konstruktor

int Login(stringklient, stringhaslo, intid); // Bezpieczny dostep do konta

bool Logout(intid); // Koniec dostepu do konta

bool Wplata(intid, doublekwota); // Wplac na konto

bool Wyplata(intid, doublekwota); // Wyplac z konta

double Stan(intid); // Zwroc stan konta

bool Numer(NUMER\_RACHUNKUnumer); // Porownaj numer rachunku

bool Klient(stringklient); // Porownaj identyfikator klienta

};

```

  1. Klasa Bank

Klasa Bank jest centraln¹ klas¹ projektu. Bank to kolekcja kont bankowych (dok³adnie: wektor wskaŸników na obiekt typu Konto). Wektor jest kolekcj¹ bez klucza, dlatego znalezienie konta o danym numerze wymaga liniowego przeszukania wektora (iteracji po indeksie w prywatnej metodzie Znajdz()).

Parametrami konstruktora s¹ numer rozliczeniowy banku i numer pocz¹tkowy rachunków w tym banku. Metoda Otworz() otwiera nowe konto dla klienta banku: generuje numer nowego konta, tworzy obiekt klasy Konto i zapisuje go do wektora kont. Parametrami tej metody s¹ identyfikator i has³o klienta.

Metoda Login() wymaga, ¿eby konto o podanym identyfikatorze klienta i podanym haœle ju¿ istnia³o i - jeœli tak jest - generuje identyfikator bezpiecznego dostêpu.

Klasa Bankpowtarza metody publiczne klasy wewnêtrznej Konto „zapakowane&quot; w kod znajduj¹cy konto w wektorze kont.

Metoda Przelej()wymaga bardziej szczegó³owego objaœnienia. Implementuje ona przelew kwoty z w³asnego konta na obce konto. Obce konto identyfikowane jest przez wskaŸnik na obcy bank i numer rachunku w tym banku. Przelew jest realizowany w dwóch krokach. Najpierw kwota jest wyp³acana z w³asnego konta (dostêp za pomoc¹ publicznej metody Wyplac()). Nastêpnie ta sama kwota jest wp³acana na obce konto za pomoc¹ prywatnej metody Wplac(). Bank Ÿród³owy staje siê tu klientem banku docelowego, nie posiadaj¹c ani identyfikatora klienta ani jego has³a. ¯eby rozwi¹zaæ problem dostêpu, dopuszcza siê wp³aty bez identyfikatora dostêpu. Metoda Wplac() jest wewn¹trz klasy Bank metod¹ prywatn¹, miêdzy obiektami typu Bank jest jednak widoczna (bank Ÿród³owy wo³a metodê Wplac() banku docelowego).

```cpp

#include\&lt;vector\&gt;

#include&quot;Definicje.h&quot;

#include&quot;Konto.h&quot;

classBank

{

private:

NUMER\_ROZLICZENIOWY\_BANKU numer; // numer banku

NUMER\_RACHUNKU numer\_poczatkowy\_rachunkow; // numer poczatkowy rachunkow w tym banku

int kolejny\_numer\_rachunku; // kolejny numer rachunku

int kolejny\_numer\_transakcji; // kolejny numer transakcji (id)

vector\&lt;Konto\*\&gt; konta; // kolekcja kont (wektor wskaznikow na konto)

bool Wplac(NUMER\_RACHUNKUnumer, doublekwota); // Wplac kwote na obcy rachunek

Konto\* Znajdz(NUMER\_RACHUNKUnumer); // Znajdz konto z numerem rachunku

public:

Bank(NUMER\_ROZLICZENIOWY\_BANKUnumer\_rozliczeniowy\_banku, NUMER\_RACHUNKUnumer\_pierwszego\_rachunku); // Konstruktor

NUMER\_RACHUNKU Otworz(stringklient, stringhaslo); // Otworz nowy rachunek

int Login(stringklient, stringhaslo, NUMER\_RACHUNKUnumer); // Login klienta

bool Logout(NUMER\_RACHUNKUnumer, intid);

bool Wplac(NUMER\_RACHUNKUnumer, intid, doublekwota); // Wplac kwote na rachunek klienta

bool Wyplac(NUMER\_RACHUNKUnumer, intid, doublekwota); // Pobierz kwote z rachunku klienta

bool Przelej(NUMER\_RACHUNKUnumer, intid, doublekwota, Bank\* bank, NUMER\_RACHUNKUobcy\_rachunek); // Przelej kwote z rachunku klienta na obcy rachunek

double Stan(NUMER\_RACHUNKUnumer, intid); // Zwroc stan rachunku

NUMER\_ROZLICZENIOWY\_BANKU Numer(); // Zwroc numer rozliczeniowy banku

};

```


  1. Klasa Siec

Sieæ to kolekcja banków (dok³adnie: wektor wskaŸników na obiekt Bank). Metoda Rejestruj() tworzy nowy obiekt Bank i dodaje go do kolekcji banków. Metoda Znajdz() szuka w wektorze banku o podanym numerze rozliczeniowym.

```cpp

#include\&lt;vector\&gt;

#include&quot;Bank.h&quot;

#include&quot;Definicje.h&quot;

classSiec

{

private:

vector\&lt;Bank\*\&gt; siec; // kolekcja bankow (wektor wskaznikow na Bank)

public:

Siec(); // Konstruktor

void Rejestruj(NUMER\_ROZLICZENIOWY\_BANKUnumer\_rozliczeniowy\_banku, NUMER\_RACHUNKUnumer\_poczatkowy\_rachunkow); // Zarejestruj nowy bank w sieci bankow

Bank\* Znajdz(NUMER\_ROZLICZENIOWY\_BANKUnumer\_rozliczeniowy\_banku); // Znajdz bank

};

```


  1. Klasa Klient

Klasa Klient korzysta z us³ug klas Siec oraz Bank (deleguje wykonanie us³ug bankowych do odpowiednich klas). Celem klasy jest udostepnienie mo¿liwie prostych w u¿yciu metod dla programu g³ównego. Klient jest definiowany przez identyfikator i has³o (parametry konstruktora). Klasa Klient ukrywa w czêœci prywatnej identyfikator dostêpu do konta.

```cpp
#include&quot;Definicje.h&quot;

#include&quot;Siec.h&quot;

#include&quot;Bank.h&quot;

classKlient

{

private:

Siec\* siec; // wskaznik na siec bankow

Bank\* bank; // wskaznik na bank klienta

string klient; // identyfikator klienta

string haslo; // haslo klienta

NUMER\_RACHUNKU numer; // numer rachunku klienta

int id; // identyfikator transaksji

public:

Klient (stringklient, stringhaslo); // Konstruktor

bool Otworz(Siec\* siec, NUMER\_ROZLICZENIOWY\_BANKUnumer); // Otworz nowy rachunek

bool Login(); // Rozpocznij transakcje

bool Logout(); // Rozpocznij transakcje

bool Wplac(doublekwota); // Wplac kwote na wlasny rachunek

bool Wyplac(doublekwota); // Pobierz kwote z wlasnego rachunku

bool Przelej(doublekwota, NUMER\_ROZLICZENIOWY\_BANKUbank, NUMER\_RACHUNKUrachunek); // Przelej kwote z wlasnego rachunku na obcy rachunek

double Stan(); // Zwroc aktualny stan rachunku

NUMER\_RACHUNKU Numer();

};
```

  1. Program g³ówny main

Program g³ówny sk³ada siê z obiektów typu Klient, które korzystaj¹ z us³ug obiektów typu Bank. W pierwszej czêœci programu obiekt klasy Siecpoœredniczy w tworzeniu obiektów typu Bank (metoda Rejestruj()). W drugiej czêœci tworzone s¹ obiekty typu Klient, które nastêpnie korzystaj¹ z us³ug bankowych.
 W programie g³ównym zrealizowano przyk³adowy prosty scenariusz:

- dwa banki: mBank i ING
- dwóch klientów: A i B

- A wp³aca kwotê na w³asne konto
- A przekazuje kwotê na konto B

- B wyp³aca kwotê ze swojego konta
- A i B informuj¹ o koñcowym stanie swoich kont.
