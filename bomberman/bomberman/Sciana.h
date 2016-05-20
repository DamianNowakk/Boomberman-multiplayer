#pragma once
#include "ElementSwiata.h"
#include "Stale.h"

class Sciana
	:public ElementSwiata
{
public:
	//zmienne
	char typ;
	bool bonus;
	int nrbonusu;
	// konstruktor i destruktor
	Sciana(float x, float y, char typ);
	Sciana(float x, float y, char typ, bool bunusik, int nrbonusiku);
	~Sciana();

	//getery i setery
	char getTyp();
	bool getBonus();
	void setBonus(bool x);
	int getNrBonusu();
	void setNrBonusu(int x);
	//metody

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};