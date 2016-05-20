#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Stale.h"

using namespace std;

class ElementSwiata
	: public sf::Drawable
{
public:
	//zmienne
	sf::Sprite sprite;
	sf::Texture texture;
	bool przenikalnosc;
	bool zniszczalnosc;
	string nazwa;
	// konstruktor i destruktor
	ElementSwiata(float x, float y);
	~ElementSwiata();

	//getery i setery
	bool getPrzenikalnosc();
	void setPrzenikalnosc(bool x);
	bool getZniszczalnosc();
	void setZniszczalnosc(bool x);
	sf::Vector2f getPozycja();
	sf::FloatRect getBoundingBox();
	string getNazwa();

	//metody
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};