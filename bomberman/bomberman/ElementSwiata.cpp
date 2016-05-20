#pragma once
#include "ElementSwiata.h"
#include <vector>

// konstruktor i destruktor
ElementSwiata::ElementSwiata(float x, float y)
{
	sprite.setPosition(sf::Vector2f(x, y));
	przenikalnosc = false;
}

ElementSwiata::~ElementSwiata()
{

}

//getery i setery
bool ElementSwiata::getPrzenikalnosc()
{
	return przenikalnosc;
}

void ElementSwiata::setPrzenikalnosc(bool x)
{
	przenikalnosc = x;
}

bool ElementSwiata::getZniszczalnosc()
{
	return zniszczalnosc;
}

void ElementSwiata::setZniszczalnosc(bool x)
{
	zniszczalnosc = x;
}

sf::Vector2f ElementSwiata::getPozycja()
{
	return sprite.getPosition();
}

sf::FloatRect ElementSwiata::getBoundingBox()
{
	return sprite.getGlobalBounds();
}

string ElementSwiata::getNazwa()
{
	return nazwa;
}

//metody