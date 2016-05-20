#pragma once
#include "Wybuch.h"

// konstruktor i destruktor
Wybuch::Wybuch(int x, int y, kierunek jaka_strona) : ElementSwiata((float)x, (float)y)
{
	nazwa = "wybuch";
	texture.loadFromFile("obrazki/wybuch.png");
	sprite.setTexture(texture);
	zniszczalnosc = false;
	przenikalnosc = true;
	this->x_mapa = x / OBIEKTY;
	this->y_mapa = y / OBIEKTY;
	klatkax = 0;
	klatkay = 0;
	if (jaka_strona == PIONOWO)
	{
		sprite.setTextureRect(sf::IntRect(64, 5, OBIEKTY, OBIEKTY));
		sprite.setOrigin(0, OBIEKTY);
		sprite.setRotation(90);
	}
	else if (jaka_strona == POZIOMO)
	{
		sprite.setTextureRect(sf::IntRect(64, 5, OBIEKTY, OBIEKTY));

	}
	else if (jaka_strona == GORA)
	{
		sprite.setTextureRect(sf::IntRect(0, 5, OBIEKTY, OBIEKTY));
		sprite.setOrigin(0, OBIEKTY);
		sprite.setRotation(90);
	}
	else if (jaka_strona == DOL)
	{
		sprite.setTextureRect(sf::IntRect(220, 5, OBIEKTY, OBIEKTY));
		sprite.setOrigin(0, OBIEKTY);
		sprite.setRotation(90);
	}
	else if (jaka_strona == LEWO)
	{
		sprite.setTextureRect(sf::IntRect(0, 5, OBIEKTY, OBIEKTY));
	}
	else if (jaka_strona == PRAWO)
	{
		sprite.setTextureRect(sf::IntRect(220, 5, OBIEKTY, OBIEKTY));
	}
	else if (jaka_strona == SRODEK)
	{
		texture.loadFromFile("obrazki/srodek.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, OBIEKTY, OBIEKTY));
	}
	this->status = jaka_strona;
	
}

Wybuch::~Wybuch()
{

}

//getery i setery
int Wybuch::getXmapa()
{
	return this->x_mapa;
}

int Wybuch::getYmapa()
{
	return this->y_mapa;
}
//metody
bool Wybuch::odswiezanie_wybuch()
{
	animacja();
	if (czas_trwania.getElapsedTime() > sf::seconds(0.6f))
	{
		return true;
	}
	return false;
}

void Wybuch::animacja()
{
	if (status == SRODEK)
	{
		if (animacji.getElapsedTime() > sf::seconds(0.04f))
		{
			if (klatkax < 3)
			{
				klatkax++;
			}
			else
			{
				klatkax = 0;
				klatkay++;
			}
			sprite.setTextureRect(sf::IntRect(OBIEKTY * klatkax + OBIEKTY * klatkay, OBIEKTY, OBIEKTY, OBIEKTY));
			animacji.restart();
		}
	}
	else
	{
		if (animacji.getElapsedTime() > sf::seconds(0.3))
		{
			if (klatkax < 1)
			{
				sprite.setColor(sf::Color(255, 255, 255));
				klatkax++;
			}
			else
			{
				sprite.setColor(sf::Color(255, 0, 0));
			}	
		}
	}
}

void Wybuch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
