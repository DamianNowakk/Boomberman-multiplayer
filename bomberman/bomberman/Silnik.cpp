#pragma once
#include "Silnik.h"
#include "Swiat.h"
#include <time.h> 
#include <thread>
#include <fstream>

// konstruktor i destruktor
Silnik::Silnik(sf::RenderWindow &okienko, int ilu_graczy, client_type client, int ktorym_graczem_jestes)
{
	this->client = client;
	sent_message = "";
	mojgracz = ktorym_graczem_jestes;
	ilosc_graczy = ilu_graczy;
	oknoAplikacji = &okienko;
	ramka.create(OKNO, OKNO);
	for (int i = 0; i < ilu_graczy; i++)
	{
		if (i == 0)
			gracze[i] = new Gracz(GRACZ1, i);
		else if (i == 1)
			gracze[i] = new Gracz(GRACZ2, i);
		else if (i == 2)
			gracze[i] = new Gracz(GRACZ3, i);
		else if (i == 3)
			gracze[i] = new Gracz(GRACZ4, i);
		else
			gracze[i] = NULL;
	}
	tloTexture.loadFromFile("obrazki/tlo.png");
	tloSprite.setTexture(tloTexture);
	tloSprite.setTextureRect(sf::IntRect(0, 0, OKNO, OKNO));
	//surowaMapa = new Mapa();
}

Silnik::~Silnik()
{

}

//getery i setery
sf::RenderWindow * Silnik::getOknoAplikacji()
{
	return oknoAplikacji;
}

int Silnik::getIloscGraczy()
{
	return ilosc_graczy;
}

void Silnik::zmniejszIloscGraczy()
{
	this->ilosc_graczy -= 1;
}

//metody
int process_client(client_type &new_client, Silnik * silnik)
{
	while (1)
	{
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);

		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);

			if (iResult != SOCKET_ERROR){
				cout << new_client.received_message << endl;
				if (new_client.received_message[0] == 's' && new_client.received_message[1] == 't' && new_client.received_message[2] == 'a' &&new_client.received_message[3] == 'r' &&new_client.received_message[4] == 't')
				{
					silnik->start = 1;
				}
				else
				{
					int ktory_gracz = (int)new_client.received_message[0] - 48;
					switch (new_client.received_message[1])
					{
					case 'w':
						silnik->gracze[ktory_gracz]->idz_gora();
						break;
					case 's':
						silnik->gracze[ktory_gracz]->idz_dol();
						break;
					case 'a':
						silnik->gracze[ktory_gracz]->idz_lewo();
						break;
					case 'd':
						silnik->gracze[ktory_gracz]->idz_prawo();
						break;
					case 'x':
						silnik->gracze[ktory_gracz]->stoj();
						break;
					case 'b':
						silnik->gracze[ktory_gracz]->postawienie_bomby(silnik->mapa, silnik->boombs);
						break;
					case 'p':
						string sx, sy;
						sx = "";
						sy = "";
						int x, y;
						int i = 3;
						while (new_client.received_message[i] != ' ')
						{
							sx += new_client.received_message[i];
							i++;
						}
						i++;
						while (new_client.received_message[i] != ' ')
						{
							sy += new_client.received_message[i];
							i++;
						}
						x = std::stoi(sx);
						y = std::stoi(sy);
						silnik->gracze[ktory_gracz]->ustawpozycjaGracza(x, y);
						break;
					}
				}
			}
			else
			{
				cout << "recv() failed: " << WSAGetLastError() << endl;
				break;
			}
		}
	}

	if (WSAGetLastError() == WSAECONNRESET)
		cout << "The server has disconnected" << endl;

	return 0;
}


void Silnik::odpalSilnik()
{
	bool menu = false;
	int iResult;
	sf::Clock zegar;
	zaladowanie_mapy();
	int now = GetTickCount();
	int lastFrame = GetTickCount();
	int delta;
	thread my_thread(process_client, this->client, this);

	sent_message = "ready";
	iResult = send(this->client.socket, sent_message.c_str(), strlen(sent_message.c_str()), 0);

	while (this->start != 1);
	sent_message = "";
	while (oknoAplikacji->isOpen())
	{
		now = GetTickCount();
		delta = now - lastFrame;
		lastFrame = now;
		if (delta < 10)
		{
			Sleep(10 - delta);
		}

		sf::Event zdarzenie;
		sf::Event * starezdarzenie = new Event();;
		while (oknoAplikacji->pollEvent(zdarzenie))
		{
			if (zegar.getElapsedTime() > sf::seconds(0.3f) && sent_message == "")
			{
				int x = gracze[mojgracz]->pozycjaX();
				int y = gracze[mojgracz]->pozycjaY();
				sent_message = "p " + std::to_string(x)+ ' ' + std::to_string(y) + ' ';
				iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
				zegar.restart();
				sent_message = "";
			}
			switch (zdarzenie.type)
			{
			case sf::Event::Closed:
				oknoAplikacji->close();
				break;

			case sf::Event::KeyPressed:
				*starezdarzenie = zdarzenie;
				if (zdarzenie.key.code == Keyboard::W && sent_message == "")
				{
					sent_message = "w";
					iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
					if (gracze[mojgracz]->getCzyzyje())
						gracze[mojgracz]->idz_gora();
					sent_message = "";
				}
				else if (zdarzenie.key.code == Keyboard::S && sent_message == "")
				{
					sent_message = "s";
					iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
					if (gracze[mojgracz]->getCzyzyje())
						gracze[mojgracz]->idz_dol();
					sent_message = "";
				}
				else if (zdarzenie.key.code == Keyboard::A && sent_message == "")
				{
					sent_message = "a";
					iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
					if (gracze[mojgracz]->getCzyzyje())
						gracze[mojgracz]->idz_lewo();
					sent_message = "";
				}
				else if (zdarzenie.key.code == Keyboard::D && sent_message == "")
				{
					sent_message = "d";
					iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
					if (gracze[mojgracz]->getCzyzyje())
						gracze[mojgracz]->idz_prawo();
					sent_message = "";
				}
				else if (zdarzenie.key.code == Keyboard::Space && sent_message == "")
				{
					sent_message = "b";
					iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
					if (gracze[mojgracz]->getCzyzyje())
						gracze[mojgracz]->postawienie_bomby(mapa, boombs);
					sent_message = "";
				}
				break;

			case sf::Event::KeyReleased:
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sent_message == "")
				{
					sent_message = "x";
					iResult = send(this->client.socket, sent_message.c_str(), DEFAULT_BUFLEN, 0);
					if (gracze[mojgracz]->getCzyzyje())
						gracze[mojgracz]->stoj();
					sent_message = "";
				}
				break;

			default:
				break;
			}
			
		}

		for (int i = 0; i < 4; i++)
		{
			if (gracze[i]->getCzyzyje())
			{
				sprawdzanie_kolizji_z_mapa(i);
				sprawdzanie_kolizji_z_graczami(i);
				gracze[i]->odswiezanie();
			}
		}
		obsluga_bomb();
		obsluga_wybuchow();
		sprawdzanie_kolizji_z_wybuchami();
		tworzenie_ramki();
		oknoAplikacji->clear();
		sprite.setTexture(texture);
		oknoAplikacji->draw(sprite);
		oknoAplikacji->display();
	}

}

void Silnik::tworzenie_ramki()
{
	ramka.clear();
	ramka.draw(tloSprite);
	

	for (int i = 0; i < MAPA; i++)//y
	{
		for (int j = 0; j < MAPA; j++)//x
		{
			if (mapa[i][j] != NULL)
			{
				ramka.draw(*mapa[i][j]);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (gracze[i] != NULL)
			if (gracze[i]->getCzyzyje())
				ramka.draw(*gracze[i]);
	}
	for (int i = 0; i < wybuchy.size(); i++)
	{
		ramka.draw(*wybuchy[i]);
	}
	ramka.display();
}

void Silnik::zaladowanie_mapy()
{
	char znak;
	int czybonus, nrbonusu;
	fstream mapaPlik;
	mapaPlik.open("obrazki/mapa1.txt", ios::in);
	for (int i = 0; i < MAPA; i++)//y
	{
		for (int j = 0; j < MAPA; j++)//x
		{
			mapaPlik >> znak;
			mapaPlik >> czybonus;
			mapaPlik >> nrbonusu;
			switch (znak)
			{
			case 'z':
				if (czybonus == 1)
					this->mapa[i][j] = new Sciana(OBIEKTY * j, OBIEKTY * i, znak, true, nrbonusu);
				else
					this->mapa[i][j] = new Sciana(OBIEKTY * j, OBIEKTY * i, znak, false, -1);
				break;

			case 'n':
				this->mapa[i][j] = new Sciana(OBIEKTY * j, OBIEKTY * i, znak);
				break;

			default:
				this->mapa[i][j] = NULL;
				break;
			}
		}
	}
	mapaPlik.close();
}

void Silnik::sprawdzanie_kolizji_z_mapa(int gracz)
{
	if (gracze[gracz]->getStatus() != Gracz::GORA)
		if (gracze[gracz]->getStatus() != Gracz::DOL)
			if (gracze[gracz]->getStatus() != Gracz::LEWO)
				if (gracze[gracz]->getStatus() != Gracz::PRAWO)
					return;

	Gracz::poruszanie gdzie_chce_isc = gracze[gracz]->getStatus();
	FloatRect box1(gracze[gracz]->getBoundingBox());
	box1.height -= 2;
	box1.width -= 2;
	box1.left += 1;
	box1.top += 1;

	box1.left += (gracze[gracz]->przemieszczenie()).x;
	box1.top += (gracze[gracz]->przemieszczenie()).y;
	if (gracze[gracz]->przemieszczenie().x == 0 && gracze[gracz]->przemieszczenie().y == 0)
		gracze[gracz]->stoj();
	bool p1 = true;
	bool p2 = true;
	bool p3 = true;
	bool p4 = true;


	//1 gora , lewo
	int x1 = box1.left / OBIEKTY;
	int y1 = box1.top / OBIEKTY;
	if (mapa[y1][x1] != NULL && !mapa[y1][x1]->getPrzenikalnosc())
	{
		if (box1.intersects(mapa[y1][x1]->getBoundingBox()))
		{
			gracze[gracz]->stoj();
			p1 = false;
		}
	}
	else if (mapa[y1][x1] != NULL && (mapa[y1][x1]->getNazwa() == "bonus"))
	{
		if (box1.intersects(mapa[y1][x1]->getBoundingBox()))
		{
			Bonus *tmp = (Bonus*)mapa[y1][x1];
			tmp->bonusy(gracze[gracz]);
			delete mapa[y1][x1];
			mapa[y1][x1] = NULL;
		}
	}

	//2 gora, prawo
	int x2 = (box1.left + OBIEKTY) / OBIEKTY;
	int y2 = box1.top / OBIEKTY;
	if (mapa[y2][x2] != NULL && !mapa[y2][x2]->getPrzenikalnosc())
	{
		if (box1.intersects(mapa[y2][x2]->getBoundingBox()))
		{
			gracze[gracz]->stoj();
			p2 = false;
		}
	}
	else if (mapa[y2][x2] != NULL && (mapa[y2][x2]->getNazwa() == "bonus"))
	{
		if (box1.intersects(mapa[y2][x2]->getBoundingBox()))
		{
			Bonus *tmp = (Bonus*)mapa[y2][x2];
			tmp->bonusy(gracze[gracz]);
			delete mapa[y2][x2];
			mapa[y2][x2] = NULL;
		}
	}
	//3 dol ,lewo
	int x3 = (box1.left) / OBIEKTY;
	int y3 = (box1.top + OBIEKTY) / OBIEKTY;
	if (mapa[y3][x3] != NULL && !mapa[y3][x3]->getPrzenikalnosc())
	{
		if (box1.intersects(mapa[y3][x3]->getBoundingBox()))
		{
			gracze[gracz]->stoj();
			p3 = false;
		}
	}
	else if (mapa[y3][x3] != NULL && (mapa[y3][x3]->getNazwa() == "bonus"))
	{
		if (box1.intersects(mapa[y3][x3]->getBoundingBox()))
		{
			Bonus *tmp = (Bonus*)mapa[y3][x3];
			tmp->bonusy(gracze[gracz]);
			delete mapa[y3][x3];
			mapa[y3][x3] = NULL;
		}
	}
	//4 dol , prawo
	int x4 = (box1.left + OBIEKTY) / OBIEKTY;
	int y4 = (box1.top + OBIEKTY) / OBIEKTY;
	if (mapa[y4][x4] != NULL && !mapa[y4][x4]->getPrzenikalnosc())
	{
		if (box1.intersects(mapa[y4][x4]->getBoundingBox()))
		{
			gracze[gracz]->stoj();
			p4 = false;
		}
	}
	else if (mapa[y4][x4] != NULL && (mapa[y4][x4]->getNazwa() == "bonus"))
	{
		if (box1.intersects(mapa[y4][x4]->getBoundingBox()))
		{
			Bonus *tmp = (Bonus*)mapa[y4][x4];
			tmp->bonusy(gracze[gracz]);
			delete mapa[y4][x4];
			mapa[y4][x4] = NULL;
		}
	}


	if (gracze[gracz]->getStatus() == Gracz::STOJ)
	{
		if (gdzie_chce_isc == Gracz::DOL)
		{
			int tmp;
			if (p3)
			{
				tmp = box1.left - x3 * OBIEKTY;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_lewydol();
				}
			}
			if (p4)
			{
				tmp = x4 * OBIEKTY - box1.left;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_prawydol();
				}
			}
		}
		if (gdzie_chce_isc == Gracz::GORA)
		{
			int tmp;
			if (p1)
			{
				tmp = box1.left - x1 * OBIEKTY;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_lewygora();
				}
			}
			if (p2)
			{
				tmp = x2 * OBIEKTY - box1.left;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_prawygora();
				}
			}
		}
		if (gdzie_chce_isc == Gracz::LEWO)
		{
			int tmp;
			if (p1)
			{
				tmp = box1.top - y1 * OBIEKTY;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_goralewy();
				}
			}
			if (p3)
			{
				tmp = y3 * OBIEKTY - box1.top;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_dollewy();
				}
			}
		}
		if (gdzie_chce_isc == Gracz::PRAWO)
		{
			int tmp;
			if (p2)
			{
				tmp = box1.top - y2 * OBIEKTY;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_goraprawy();
				}
			}
			if (p4)
			{
				tmp = y4 * OBIEKTY - box1.top;
				if (0 <= tmp && tmp <= WSPOMAGANIE_1_4)
				{
					gracze[gracz]->idz_dolprawy();
				}
			}
		}
	}
}

void Silnik::sprawdzanie_kolizji_z_graczami(int gracz)
{
	if (gracze[gracz]->getStatus() != Gracz::GORA)
		if (gracze[gracz]->getStatus() != Gracz::DOL)
			if (gracze[gracz]->getStatus() != Gracz::LEWO)
				if (gracze[gracz]->getStatus() != Gracz::PRAWO)
					return;
	FloatRect box1(gracze[gracz]->getBoundingBox());
	box1.height -= 2;
	box1.width -= 2;
	box1.left += 1;
	box1.top += 1;
	box1.left += (gracze[gracz]->przemieszczenie()).x;
	box1.top += (gracze[gracz]->przemieszczenie()).y;
	if (gracze[gracz]->przemieszczenie().x == 0 && gracze[gracz]->przemieszczenie().y == 0)
		gracze[gracz]->stoj();
	for (int x = 0; x < 4; x++)
	{
		if (x != gracz)
		{
			if (gracze[x]->getCzyzyje())
			{
					//1 gora , lewo
					int x1 = box1.left / OBIEKTY;
					int y1 = box1.top / OBIEKTY;
					if (box1.intersects(gracze[x]->getBoundingBox()))
					{
						gracze[gracz]->stoj();
						break;
					}

					//2 gora, prawo
					int x2 = (box1.left + OBIEKTY) / OBIEKTY;
					int y2 = box1.top / OBIEKTY;
					if (box1.intersects(gracze[x]->getBoundingBox()))
					{
						gracze[gracz]->stoj();
						break;
					}

					//3 dol ,lewo
					int x3 = (box1.left) / OBIEKTY;
					int y3 = (box1.top + OBIEKTY) / OBIEKTY;
					if (box1.intersects(gracze[x]->getBoundingBox()))
					{
						gracze[gracz]->stoj();
						break;
					}

					//4 dol , prawo
					int x4 = (box1.left + OBIEKTY) / OBIEKTY;
					int y4 = (box1.top + OBIEKTY) / OBIEKTY;
					if (box1.intersects(gracze[x]->getBoundingBox()))
					{
						gracze[gracz]->stoj();
						break;
					}
			}
		}
	}
}

void Silnik::sprawdzanie_kolizji_z_wybuchami()
{
	for (int x = 0; x < 4; x++)
	{
		if (gracze[x]->getCzyzyje())
		{
			FloatRect box1(gracze[x]->getBoundingBox());
			box1.height -= 2;
			box1.width -= 2;
			box1.left += 1;
			box1.top += 1;

			for (int i = 0; i < wybuchy.size(); i++)
			{
				//1 gora , lewo
				int x1 = box1.left / OBIEKTY;
				int y1 = box1.top / OBIEKTY;
				if (box1.intersects(wybuchy[i]->getBoundingBox()))
				{
					gracze[x]->setCzyzyje(false);
					this->zmniejszIloscGraczy();
					break;
				}

				//2 gora, prawo
				int x2 = (box1.left + OBIEKTY) / OBIEKTY;
				int y2 = box1.top / OBIEKTY;
				if (box1.intersects(wybuchy[i]->getBoundingBox()))
				{
					gracze[x]->setCzyzyje(false);
					this->zmniejszIloscGraczy();
					break;
				}

				//3 dol ,lewo
				int x3 = (box1.left) / OBIEKTY;
				int y3 = (box1.top + OBIEKTY) / OBIEKTY;
				if (box1.intersects(wybuchy[i]->getBoundingBox()))
				{
					gracze[x]->setCzyzyje(false);
					this->zmniejszIloscGraczy();
					break;
				}

				//4 dol , prawo
				int x4 = (box1.left + OBIEKTY) / OBIEKTY;
				int y4 = (box1.top + OBIEKTY) / OBIEKTY;
				if (box1.intersects(wybuchy[i]->getBoundingBox()))
				{
					gracze[x]->setCzyzyje(false);
					this->zmniejszIloscGraczy();
					break;
				}
			}
		}
	}
}

void Silnik::obsluga_bomb()
{
	for (int i = 0; i < boombs.size(); i++)
	{
		if (boombs[i]->getPrzenikalnosc()) // bohater moze wyjsc z pola razenia
		{
			sf::FloatRect box1(gracze[boombs[i]->doKogoNalezyBomba()]->getBoundingBox());
			sf::FloatRect box2(boombs[i]->getBoundingBox());
			if (!box1.intersects(box2))
			{
				boombs[i]->setPrzenikalnosc(false);
			}
		}

		if (boombs[i]->odswiezanie_bomba())
		{
			gracze[boombs[i]->doKogoNalezyBomba()]->zmniejszenie_postawionych_bomb();
			int x = boombs[i]->getXmapa();
			int y = boombs[i]->getYmapa();
			int silarazenia = boombs[i]->getSilaRazenia();
			boombs[i]->~Bomba();
			this->boombs.erase(this->boombs.begin() + i);
			delete mapa[y][x];
			this->mapa[y][x] = NULL;
			wybuch_bomb(x, y, silarazenia);
			
		}
	}
}

void Silnik::wybuch_bomb(int x, int y, int silarazenia)
{
	Wybuch *wybuch;
	wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y), Wybuch::PIONOWO);
	wybuchy.push_back(wybuch);
	wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y), Wybuch::POZIOMO);
	wybuchy.push_back(wybuch);
	wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y), Wybuch::SRODEK);
	wybuchy.push_back(wybuch);
	string tmp = "bomba";
	bool czystworzycbonus = false;
	int nrbonusu = 0;
	for (int i = 0; i < 4; i++) // 0 gora 1 dol 2 lewo 4 prawo
	{
		for (int promien = 1; promien < silarazenia + 1; promien++)
		{
			if (i == 0)
			{
				if (this->mapa[y - promien][x] == NULL || this->mapa[y - promien][x]->getPrzenikalnosc())
				{
					
					if (promien == silarazenia || (this->mapa[y - (promien + 1)][x] != NULL && !this->mapa[y - (promien + 1)][x]->getZniszczalnosc() && !this->mapa[y - (promien + 1)][x]->getPrzenikalnosc()))
						wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y - promien), Wybuch::GORA);
					else
						wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y - promien), Wybuch::PIONOWO);
					wybuchy.push_back(wybuch);
					continue;
				}
				else if (this->mapa[y - promien][x]->getZniszczalnosc())
				{
					if (mapa[y - promien][x]->getNazwa() == "sciana")
					{
						Sciana * tym;
						tym = (Sciana*)mapa[y - promien][x];
						czystworzycbonus = tym->getBonus();
						nrbonusu = tym->getNrBonusu();
					}
					
					this->mapa[y - promien][x]->~ElementSwiata();
					delete mapa[y - promien][x];

					wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y - promien), Wybuch::GORA);
					mapa[y - promien][x] = NULL;
					if (czystworzycbonus)
					{
						mapa[y - promien][x] = new Bonus(OBIEKTY *x, OBIEKTY*(y - promien), nrbonusu);
					}
					wybuchy.push_back(wybuch);
					break;
				}
				else
				{
					if (this->mapa[y - promien][x]->getNazwa() == tmp)
					{
						Bomba *tym = (Bomba*)mapa[y - promien][x];
						tym->setCzywybuchnac(true);
					}
					break;
				}
			}
			else if (i == 1)
			{
				if (this->mapa[y + promien][x] == NULL || this->mapa[y + promien][x]->getPrzenikalnosc())
				{
					if (promien == silarazenia || (this->mapa[y + (promien + 1)][x] != NULL && !this->mapa[y + (promien + 1)][x]->getZniszczalnosc() && !this->mapa[y + (promien + 1)][x]->getPrzenikalnosc()))
						wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y + promien), Wybuch::DOL);
					else
						wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y + promien), Wybuch::PIONOWO);
					wybuchy.push_back(wybuch);
					continue;
				}
				else if (this->mapa[y + promien][x]->getZniszczalnosc())
				{
					if (mapa[y + promien][x]->getNazwa() == "sciana")
					{
						Sciana * tym;
						tym = (Sciana*)mapa[y + promien][x];
						czystworzycbonus = tym->getBonus();
						nrbonusu = tym->getNrBonusu();
					}
					this->mapa[y + promien][x]->~ElementSwiata();
					delete mapa[y + promien][x];
					
					wybuch = new Wybuch(OBIEKTY *x, OBIEKTY *(y + promien), Wybuch::DOL);
					mapa[y + promien][x] = NULL;
					if (czystworzycbonus)
					{
						mapa[y + promien][x] = new Bonus(OBIEKTY *x, OBIEKTY*(y + promien), nrbonusu);
					}
					wybuchy.push_back(wybuch);
					break;
				}
				else
				{
					if (this->mapa[y + promien][x]->getNazwa() == tmp)
					{
						Bomba *tym = (Bomba*)mapa[y + promien][x];
						tym->setCzywybuchnac(true);
					}
					break;
				}
			}
			else if (i == 2)
			{
				if (this->mapa[y][x - promien] == NULL || this->mapa[y][x - promien]->getPrzenikalnosc())
				{
					if (promien == silarazenia || (this->mapa[y][x - (promien + 1)] != NULL && !this->mapa[y][x - (promien + 1)]->getZniszczalnosc() && !this->mapa[y][x - (promien + 1)]->getPrzenikalnosc()))
						wybuch = new Wybuch(OBIEKTY *(x-promien), OBIEKTY *y, Wybuch::LEWO);
					else
						wybuch = new Wybuch(OBIEKTY *(x - promien), OBIEKTY *y, Wybuch::POZIOMO);
					wybuchy.push_back(wybuch);
					continue;
				}
				else if (this->mapa[y][x - promien]->getZniszczalnosc())
				{
					if (mapa[y][x - promien]->getNazwa() == "sciana")
					{
						Sciana * tym;
						tym = (Sciana*)mapa[y][x - promien];
						czystworzycbonus = tym->getBonus();
						nrbonusu = tym->getNrBonusu();
					}
					this->mapa[y][x - promien]->~ElementSwiata();
					delete mapa[y][x - promien];
					
					wybuch = new Wybuch(OBIEKTY *(x - promien), OBIEKTY *y, Wybuch::LEWO);
					mapa[y][x - promien] = NULL;
					if (czystworzycbonus)
					{
						mapa[y][x - promien] = new Bonus(OBIEKTY *(x - promien), OBIEKTY*y, nrbonusu);
					}
					wybuchy.push_back(wybuch);
					break;
				}
				else
				{
					if (this->mapa[y][x - promien]->getNazwa() == tmp)
					{
						Bomba *tym = (Bomba*)mapa[y][x - promien];
						tym->setCzywybuchnac(true);
					}
					break;
				}
			}
			else if (i == 3)
			{
				if (this->mapa[y][x + promien] == NULL || this->mapa[y][x + promien]->getPrzenikalnosc())
				{
					if (promien == silarazenia || (this->mapa[y][x + (promien + 1)] != NULL && !this->mapa[y][x + (promien + 1)]->getZniszczalnosc() && !this->mapa[y][x + (promien + 1)]->getPrzenikalnosc()))
						wybuch = new Wybuch(OBIEKTY *(x + promien), OBIEKTY *y, Wybuch::PRAWO);
					else
						wybuch = new Wybuch(OBIEKTY *(x + promien), OBIEKTY *y, Wybuch::POZIOMO);
					wybuchy.push_back(wybuch);
					continue;
				}
				else if (this->mapa[y][x + promien]->getZniszczalnosc())
				{
					if (mapa[y][x + promien]->getNazwa() == "sciana")
					{
						Sciana * tym;
						tym = (Sciana*)mapa[y][x + promien];
						czystworzycbonus = tym->getBonus();
						nrbonusu = tym->getNrBonusu();
					}
					this->mapa[y][x + promien]->~ElementSwiata();
					delete mapa[y][x + promien];
					
					wybuch = new Wybuch(OBIEKTY *(x + promien), OBIEKTY *y, Wybuch::PRAWO);
					mapa[y][x + promien] = NULL;
					if (czystworzycbonus)
					{
						mapa[y][x + promien] = new Bonus(OBIEKTY *(x + promien), OBIEKTY*y, nrbonusu);
					}
					wybuchy.push_back(wybuch);
					break;
				}
				else
				{
					if (this->mapa[y][x + promien]->getNazwa() == tmp)
					{
						Bomba *tym = (Bomba*)mapa[y][x + promien];
						tym->setCzywybuchnac(true);
					}
					break;
				}
			}
		}
	}
}

void Silnik::obsluga_wybuchow()
{
	for (int i = 0; i < wybuchy.size(); i++)
	{
		if (wybuchy[i]->odswiezanie_wybuch())
		{
			int x = wybuchy[i]->getXmapa();
			int y = wybuchy[i]->getYmapa();
			wybuchy[i]->~Wybuch();
			delete wybuchy[i];
			this->wybuchy.erase(this->wybuchy.begin() + i);
	
		}
	}
}