#include "Siec.h"

Siec::Siec()
{
}

void Siec::Rejestruj(NUMER_ROZLICZENIOWY_BANKU numer_rozliczeniowy_banku, NUMER_RACHUNKU numer_poczatkowy_rachunkow)
{
	this->siec.push_back(new Bank(numer_rozliczeniowy_banku, numer_poczatkowy_rachunkow));
}

Bank* Siec::Znajdz(NUMER_ROZLICZENIOWY_BANKU numer_rozliczeniowy_banku)
{
	return *find_if(this->siec.begin(), this->siec.end(), [numer_rozliczeniowy_banku](Bank* p)
	{
		return p->Numer() == numer_rozliczeniowy_banku;
	});
}
