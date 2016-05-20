#pragma once
#include "ElementSwiata.h"
#include "Gracz.h"

class Bonus :public ElementSwiata
{
public:
	//zmienne
	enum rodzaj { BOMBA, SILA, GODMODE};
	rodzaj status;
	int x_mapa;
	int y_mapa;

	//konstruktor i destruktor
	Bonus(int x, int y, int losowa);
	~Bonus();

	//getery i setery
	int getXmapa();
	int getYmapa();

	//metody
	void bonusy(Gracz *osoba);
	void dodatkowa_bomba(Gracz *osoba);
	void wieksza_sila_razenia(Gracz* osoba);
	void niesmiertelnosc(Gracz *osoba);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};