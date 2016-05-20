#pragma once
#include "Mapa.h"
#include <fstream>
using namespace std;
// konstruktor i destruktor
Mapa::Mapa()
{
	wczytanie_mapy_z_pliku(1);
	czybonus = false;
	nr = -1;
}

Mapa::Mapa(bool czybonus, int nr)
{
	wczytanie_mapy_z_pliku(1);
	this->czybonus = czybonus;
	this->nr = nr;
}

Mapa::~Mapa()
{

}

//getery i setery

bool Mapa::getCzyBonus()
{
	return this->czybonus;
}

void Mapa::setCzyBonus(bool x)
{
	this->czybonus = x;
}

int Mapa::getNr()
{
	return this->nr;
}

void Mapa::setNr(int x)
{
	this->nr = x;
}


//metody
void Mapa::wczytanie_mapy_z_pliku(int jaka_mapa)
{
	fstream mapaPlik;
	mapaPlik.open("obrazki/mapa1.txt", ios::in);
	int cos;
	for (int i = 0; i < MAPA; i++)//y
	{
		for (int j = 0; j < MAPA; j++)//x
		{
			mapaPlik >> mapa[i][j];
			mapaPlik >> cos;
			mapaPlik >> cos;
		}
	}
	mapaPlik.close();
}

char Mapa::co_jest_na_mapie(int x, int y)
{
	return mapa[y][x];
}