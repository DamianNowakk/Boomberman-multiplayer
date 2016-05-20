#pragma once
#include "Bonus.h"
#include "Gracz.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

// konstruktor i destruktor
Bonus::Bonus(int x, int y, int losowa) : ElementSwiata((float)x, (float)y)
{
	srand(time(NULL));
	nazwa = "bonus";
	przenikalnosc = true;
	this->x_mapa = x / OBIEKTY;
	this->y_mapa = y / OBIEKTY;
	zniszczalnosc = false;
	switch (losowa)
	{
	case 0:
		texture.loadFromFile("obrazki/bonus1.png");
		status = BOMBA;
		break;

	case 1:
		texture.loadFromFile("obrazki/bonus2.png");
		status = SILA;
		break;

	case 2:
		texture.loadFromFile("obrazki/bonus3.png");
		status = GODMODE;
		break;

	default:
		texture.loadFromFile("obrazki/bonus1.png");
		status = SILA;
		break;
	}
	sprite.setTexture(texture);
}

Bonus::~Bonus()
{

}

//getery i setery
int Bonus::getXmapa()
{
	return this->x_mapa;
}

int Bonus::getYmapa()
{
	return this->y_mapa;
}

//metody

void Bonus::bonusy(Gracz * osoba)
{
	switch (status)
	{
	case BOMBA:
		dodatkowa_bomba(osoba);
		break;

	case SILA:
		wieksza_sila_razenia(osoba);
		break;

	case GODMODE:
		niesmiertelnosc(osoba);
		break;

	default:
		break;
	}
}
void Bonus::dodatkowa_bomba(Gracz * osoba)
{
	osoba->setMaxBomb(osoba->getMaxBomb() + 1);
}
void Bonus::wieksza_sila_razenia(Gracz * osoba)
{
	osoba->setSilaBomb(osoba->getSilaBomb() + 1);
}

void Bonus::niesmiertelnosc(Gracz * osoba)
{

}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}