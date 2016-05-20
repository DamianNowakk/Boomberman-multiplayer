#pragma once
#include "ElementSwiata.h"
#include "Stale.h"
#include "Bomba.h"

class Gracz
	:public ElementSwiata, sf::Transformable
{
public:
	//zmienne
	enum poruszanie { GORA, DOL, LEWO, PRAWO, STOJ, LEWYGORA, PRAWYGORA, LEWYDOL, PRAWYDOL, GORALEWY, GORAPRAWY, DOLLEWY, DOLPRAWY };
	poruszanie status;
	sf::Clock zegar;
	size_t klatka;
	float predkosc;
	int ilosc_bomb_postawionych;
	int numer_gracza;
	int max_bomb;
	int silabomb;
	bool czy_zyje;

	// konstruktor i destruktor
	Gracz(float x, float y, int numer_gracza);
	~Gracz();

	//getery i setery

	void ustawpozycjaGracza(float x, float y);
	int pozycjaX();
	int pozycjaY();

	bool getCzyzyje();
	void setCzyzyje(bool x);
	int getMaxBomb();
	void setMaxBomb(int x);
	int getSilaBomb();
	void setSilaBomb(int x);

	poruszanie getStatus();
	int getNumerGracza();
	void idz_gora();
	void idz_dol();
	void idz_lewo();
	void idz_prawo();
	void idz_lewygora();
	void idz_prawygora();
	void idz_lewydol();
	void idz_prawydol();
	void idz_dollewy();
	void idz_dolprawy();
	void idz_goralewy();
	void idz_goraprawy();
	void stoj();

	//metody
	void odswiezanie();
	void zwiekszenie_postawionych_bomb();
	void zmniejszenie_postawionych_bomb();
	void postawienie_bomby(ElementSwiata * mapa[MAPA][MAPA], vector<Bomba*> &boombs);
	sf::Vector2f przemieszczenie();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};