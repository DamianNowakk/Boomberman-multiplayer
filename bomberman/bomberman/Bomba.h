#pragma once
#include "ElementSwiata.h"


class Bomba :public ElementSwiata
{
public:
	//zmienne
	int x_mapa;
	int y_mapa;
	int sila_razenia;
	int nalezy_do_gracza;
	bool czy_wybuchnac;
	sf::Clock czas_wybuchu;
	sf::Clock czas_animacja;

	//konstruktor i destruktor
	Bomba(int x, int y, int gracz, int sila);
	~Bomba();

	//getery i setery
	int getXmapa();
	int getYmapa();
	int getSilaRazenia();
	void setSilaRazenia(int x);
	int doKogoNalezyBomba();
	bool getCzywybuchnac();
	void setCzywybuchnac(bool x);

	//metody
	bool odswiezanie_bomba();
	void tykanie();
	void usun_z_mapy(ElementSwiata * mapa[MAPA][MAPA], int x, int y);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};