#pragma once
#include "Sciana.h"
#include <cstdlib>
#include <ctime>

// konstruktor i destruktor
Sciana::Sciana(float x, float y, char typ) : ElementSwiata(x, y)
{
	
	nazwa = "sciana";
	if (typ == 'z')
	{
		texture.loadFromFile("obrazki/scianaz.png");
		zniszczalnosc = true;
		if (rand() % 3 == 0)
		{
			bonus = true;
		}
		else
		{
			bonus = false;
		}
		nrbonusu = rand() % 3;
	}
	else if (typ == 'n')
	{
		texture.loadFromFile("obrazki/sciananz.png");
		zniszczalnosc = false;
		bonus = false;
		nrbonusu = -1;
	}
	this->typ = typ;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, OBIEKTY, OBIEKTY));
}

Sciana::Sciana(float x, float y, char typ, bool bunusik, int nrbonusiku) : ElementSwiata(x, y)
{

	nazwa = "sciana";
	if (typ == 'z')
	{
		texture.loadFromFile("obrazki/scianaz.png");
		zniszczalnosc = true;
		bonus = bunusik;
		nrbonusu = nrbonusiku;
	}
	else if (typ == 'n')
	{
		texture.loadFromFile("obrazki/sciananz.png");
		zniszczalnosc = false;
		bonus = false;
		nrbonusu = -1;
	}
	this->typ = typ;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, OBIEKTY, OBIEKTY));
}

Sciana::~Sciana()
{

}

//getery i setery
char Sciana::getTyp()
{
	return typ;
}

bool Sciana::getBonus()
{
	return bonus;
}

void Sciana::setBonus(bool x)
{
	bonus = x;
}

int Sciana::getNrBonusu()
{
	return nrbonusu;
}

void Sciana::setNrBonusu(int x)
{
	nrbonusu = x;
}

//metody

void Sciana::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
