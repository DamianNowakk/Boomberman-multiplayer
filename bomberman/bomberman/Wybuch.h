#pragma once
#include "ElementSwiata.h"
#include "Stale.h"

class Wybuch
	:public ElementSwiata
{
public:
	//zmienne
	enum kierunek { PIONOWO, POZIOMO,SRODEK, GORA, DOL, LEWO, PRAWO };
	kierunek status;
	sf::Clock czas_trwania;
	sf::Clock animacji;
	int x_mapa;
	int y_mapa;
	size_t klatkax;
	size_t klatkay;
	// konstruktor i destruktor
	Wybuch(int x, int y, kierunek jaka_strona);
	~Wybuch();

	//getery i setery
	int getXmapa();
	int getYmapa();
	//metody
	bool odswiezanie_wybuch();
	void animacja();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};