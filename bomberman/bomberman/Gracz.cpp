#pragma once
#include "Gracz.h"

// konstruktor i destruktor
Gracz::Gracz(float x, float y, int numer_gracza) : ElementSwiata(x, y)
{
	czy_zyje = true;
	nazwa = "gracz";
	texture.loadFromFile("obrazki/gracz.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(OBIEKTY + numer_gracza * OBIEKTY * 3, 0, 64, 64));
	this->numer_gracza = numer_gracza;
	predkosc = 4;
	klatka = 0;
	ilosc_bomb_postawionych = 0;
	zniszczalnosc = true;
	max_bomb = 1;
	silabomb = 1;
	status = STOJ;
}

Gracz::~Gracz()
{

}

//getery i setery

void Gracz::ustawpozycjaGracza(float x, float y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}
int Gracz::pozycjaX()
{
	return sprite.getPosition().x;
}
int Gracz::pozycjaY()
{
	return sprite.getPosition().y;
}


bool Gracz::getCzyzyje()
{
	return czy_zyje;
}
void Gracz::setCzyzyje(bool x)
{
	czy_zyje = x;
}

int Gracz::getMaxBomb()
{
	return max_bomb;
}
void Gracz::setMaxBomb(int x)
{
	max_bomb = x;
}
int Gracz::getSilaBomb()
{
	return silabomb;
}
void Gracz::setSilaBomb(int x)
{
	silabomb = x;
}

Gracz::poruszanie Gracz::getStatus()
{
	return status;
}
int Gracz::getNumerGracza()
{
	return this->numer_gracza;
}
void Gracz::idz_gora()
{
	status = GORA;
}
void Gracz::idz_dol()
{
	status = DOL;
}
void Gracz::idz_lewo()
{
	status = LEWO;
}
void Gracz::idz_prawo()
{
	status = PRAWO;
}
void Gracz::idz_lewygora()
{
	status = LEWYGORA;
}
void Gracz::idz_lewydol()
{
	status = LEWYDOL;
}
void Gracz::idz_prawygora()
{
	status = PRAWYGORA;
}
void Gracz::idz_prawydol()
{
	status = PRAWYDOL;
}
void Gracz::idz_dollewy()
{
	status = DOLLEWY;
}
void Gracz::idz_dolprawy()
{
	status = DOLPRAWY;
}
void Gracz::idz_goralewy()
{
	status = GORALEWY;
}
void Gracz::idz_goraprawy()
{
	status = GORAPRAWY;
}
void Gracz::stoj()
{
	status = STOJ;
}

//metody
void Gracz::odswiezanie()
{
	if (status == STOJ)
	{
		sprite.setTextureRect(sf::IntRect(OBIEKTY + numer_gracza * OBIEKTY * 3, 0, 64, 64));
		return;
	}
	else if (status == GORA)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, OBIEKTY*3, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		if ((int)(sprite.getPosition().x) % OBIEKTY == 0)
			sprite.move(0, -predkosc);
	}
	else if (status == DOL)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, 0, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		if ((int)(sprite.getPosition().x) % OBIEKTY == 0)
			sprite.move(0, predkosc);
	}
	else if (status == LEWO)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, OBIEKTY, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		if ((int)(sprite.getPosition().y) % OBIEKTY == 0)
			sprite.move(-predkosc, 0);
	}
	else if (status == PRAWO)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, OBIEKTY*2, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		if ((int)(sprite.getPosition().y) % OBIEKTY == 0)
			sprite.move(predkosc, 0);
	}
	else if (status == LEWYDOL || status == LEWYGORA)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, OBIEKTY, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		float pozycja_x = sprite.getPosition().x;
		if ((int)(pozycja_x - predkosc) % OBIEKTY < WSPOMAGANIE_1_4)
		{
			sprite.move(-predkosc, 0);
		}
		else
		{
			sprite.move(-(int)(pozycja_x) % OBIEKTY, 0);
			if (status == LEWYDOL)
				this->idz_dol();
			else
				this->idz_gora();
		}
	}
	else if (status == PRAWYDOL || status == PRAWYGORA)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, OBIEKTY * 2, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		float pozycja_x = sprite.getPosition().x;
		if ((int)(pozycja_x + predkosc) % OBIEKTY > WSPOMAGANIE_3_4)
		{
			sprite.move(predkosc, 0);
		}
		else
		{
			sprite.move(OBIEKTY - (int)(pozycja_x) % OBIEKTY, 0);
			if (status == PRAWYDOL)
				this->idz_dol();
			else
				this->idz_gora();
		}
	}
	else if (status == GORALEWY || status == GORAPRAWY)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, OBIEKTY * 3, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		float pozycja_y = sprite.getPosition().y;
		if ((int)(pozycja_y - predkosc) % OBIEKTY < WSPOMAGANIE_1_4)
		{
			sprite.move(0, -predkosc);
		}
		else
		{
			sprite.move(0, -(int)(pozycja_y) % OBIEKTY);
			if (status == GORALEWY)
				this->idz_lewo();
			else
				this->idz_prawo();
		}
	}
	else if (status == DOLLEWY || status == DOLPRAWY)
	{
		if (zegar.getElapsedTime() > sf::seconds(0.13f))
		{
			if (klatka < 2)
				klatka = 2;
			else
				klatka = 0;
			sprite.setTextureRect(sf::IntRect(OBIEKTY* klatka + numer_gracza * OBIEKTY * 3, 0, 64, 64));
			//x, y, szerokosc, wysokosc
			zegar.restart();
		}
		float pozycja_y = sprite.getPosition().y;
		if ((int)(pozycja_y + predkosc) % OBIEKTY > WSPOMAGANIE_3_4)
		{
			sprite.move(0, predkosc);
		}
		else
		{
			sprite.move(0, OBIEKTY - (int)(pozycja_y) % OBIEKTY);
			if (status == DOLLEWY)
				this->idz_lewo();
			else
				this->idz_prawo();
		}
	}
}

void Gracz::zwiekszenie_postawionych_bomb()
{
	ilosc_bomb_postawionych += 1;
}

void Gracz::zmniejszenie_postawionych_bomb()
{
	ilosc_bomb_postawionych -= 1;
}

void Gracz::postawienie_bomby(ElementSwiata * mapa[MAPA][MAPA], vector<Bomba*> &boombs)
{
	int x = (this->sprite.getPosition().x + OBIEKTY / 2) / OBIEKTY;
	int y = (this->sprite.getPosition().y + OBIEKTY / 2) / OBIEKTY;
	if (mapa[y][x] == NULL && ilosc_bomb_postawionych < max_bomb)
	{
		this->zwiekszenie_postawionych_bomb();
		Bomba *bomba = new Bomba(OBIEKTY *x, OBIEKTY *y, this->getNumerGracza(), this->getSilaBomb());
		mapa[y][x] = bomba;
		boombs.push_back(bomba);
	}
}

sf::Vector2f Gracz::przemieszczenie()
{
	if (status == GORA)
	{
		if ((int)(sprite.getPosition().x) % OBIEKTY == 0)
			return sf::Vector2f(0, -predkosc);
		else
			return sf::Vector2f(0, 0);
	}
	else if (status == DOL)
	{
		if ((int)(sprite.getPosition().x) % OBIEKTY == 0)
			return sf::Vector2f(0, predkosc);
		else
			return sf::Vector2f(0, 0);
	}
	else if (status == LEWO)
	{
		if ((int)(sprite.getPosition().y) % OBIEKTY == 0)
			return sf::Vector2f(-predkosc, 0);
		else
			return sf::Vector2f(0, 0);
	}
	else if (status == PRAWO)
	{
		if ((int)(sprite.getPosition().y) % OBIEKTY == 0)
			return sf::Vector2f(predkosc, 0);
		else
			return sf::Vector2f(0, 0);
	}
}

void Gracz::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

