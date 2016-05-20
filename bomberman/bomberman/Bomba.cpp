#pragma once
#include "Bomba.h"
#include "Gracz.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

// konstruktor i destruktor
Bomba::Bomba(int x, int y, int gracz, int sila) : ElementSwiata((float)x, (float)y)
{
	nazwa = "bomba";
	texture.loadFromFile("obrazki/bomba.png");
	sprite.setTexture(texture);
	nalezy_do_gracza = gracz;
	przenikalnosc = true;
	sila_razenia = sila;
	this->x_mapa = x/OBIEKTY;
	this->y_mapa = y/OBIEKTY;
	zniszczalnosc = false;
	czy_wybuchnac = false;
}

Bomba::~Bomba()
{
	
}

//getery i setery
int Bomba::getXmapa()
{
	return this->x_mapa;
}

int Bomba::getYmapa()
{
	return this->y_mapa;
}

int Bomba::getSilaRazenia()
{
	return this->sila_razenia;
}

void Bomba::setSilaRazenia(int x)
{
	sila_razenia = x;
}

int Bomba::doKogoNalezyBomba()
{
	return this->nalezy_do_gracza;
}

bool Bomba::getCzywybuchnac()
{
	return czy_wybuchnac;
}

void Bomba::setCzywybuchnac(bool x)
{
	czy_wybuchnac = x;
}

//metody

bool Bomba::odswiezanie_bomba()
{
	tykanie();
	if ((czas_wybuchu.getElapsedTime() > sf::seconds(5.0f)) || czy_wybuchnac)
	{
		return true;
	}
	return false;
}

void Bomba::tykanie()
{
	
	if (czas_animacja.getElapsedTime() < sf::seconds(1.0f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(1.5f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(2.0f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(2.34f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(2.66f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(3.0f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(3.25f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(3.5f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(3.75f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.0f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.125f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.25f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.375f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.5f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.625f))
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	else if (czas_animacja.getElapsedTime() < sf::seconds(4.75f))
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
	else
	{
		sprite.setColor(sf::Color(255, 0, 0));
	}
}

void usun_z_mapy(ElementSwiata * mapa[MAPA][MAPA], int x, int y)
{
	mapa[y][x] = NULL;
}

void Bomba::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}