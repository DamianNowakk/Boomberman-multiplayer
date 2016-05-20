#pragma once
#include "Stale.h"
#include <SFML/Graphics.hpp>


class Mapa
{
public:
	//zmienne
	char mapa[MAPA][MAPA];
	bool czybonus;
	int nr;
	// konstruktor i destruktor
	Mapa();
	Mapa(bool czybonus, int nr);
	~Mapa();
	//getery i setery
	bool getCzyBonus();
	void setCzyBonus(bool x);

	int getNr();
	void setNr(int x);

	//metody
	void wczytanie_mapy_z_pliku(int jaka_mapa);
	char co_jest_na_mapie(int x, int y);
};