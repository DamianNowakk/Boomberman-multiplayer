#pragma once
#include "Swiat.h"
#include "Bomba.h"
#include "Gracz.h"
#include "Sciana.h"
#include "Bonus.h"
#include "Mapa.h"
#include "Wybuch.h"
#include "Stale.h"
#include <vector>

class Silnik
{
public:
	//zmienne
	client_type client;
	string sent_message;

	int start = 0;

	sf::Clock zegar;
	int mojgracz;
	int ilosc_graczy;
	sf::RenderWindow * oknoAplikacji;
	ElementSwiata * mapa[MAPA][MAPA];
	Gracz * gracze[4];
	vector<Bomba*> boombs;
	vector<Wybuch*> wybuchy;

	sf::Texture tloTexture;
	sf::Sprite tloSprite;
	sf::Sprite sprite;

	sf::RenderTexture ramka;
	const sf::Texture& texture = ramka.getTexture();
	
	// konstruktor i destruktor
	Silnik(sf::RenderWindow &window, int ilu_graczy, client_type client, int ktorym_graczem_jestes);
	~Silnik();

	//getery i setery
	sf::RenderWindow * getOknoAplikacji();

	int getIloscGraczy();
	void zmniejszIloscGraczy();


	//metody
	void odpalSilnik();
	void tworzenie_ramki();
	void zaladowanie_mapy();
	void sprawdzanie_kolizji_z_mapa(int gracz);
	void sprawdzanie_kolizji_z_graczami(int gracz);
	void sprawdzanie_kolizji_z_wybuchami();
	void obsluga_bomb();
	void wybuch_bomb(int x, int y, int silarazenia);
	void obsluga_wybuchow();
	
};