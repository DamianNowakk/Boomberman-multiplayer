#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include "ElementSwiata.h"
#include "Stale.h"

using namespace std;
using namespace sf;

struct client_type
{
	SOCKET socket;
	int id;
	char received_message[DEFAULT_BUFLEN];
};


class Swiat
{
public:
	//zmienne
	sf::RenderWindow oknoAplikacji;


	int ilosc_graczy;
	//menu
	Font czcionka;
	enum GameState { MENU, GRA, KONIEC };
	GameState status;

	//metody
	Swiat();
	~Swiat();
	void rozgrywka(client_type client);
	void menu();
	void gra();
};