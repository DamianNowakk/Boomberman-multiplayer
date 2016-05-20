#pragma once
#define NOMINMAX
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
#include "Swiat.h"
#include "Silnik.h"
#include "Stale.h"

using namespace std;

Swiat::Swiat()
{
	status = MENU;
	ilosc_graczy = 4;
	oknoAplikacji.create(sf::VideoMode(OKNO, OKNO, 32), "boomberman");
	oknoAplikacji.setVerticalSyncEnabled(true);
	gra();
}

Swiat::~Swiat()
{
	
}

void Swiat::gra()
{
	WSAData wsa_data;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	string sent_message = "";
	client_type client = { INVALID_SOCKET, -1, "" };
	int iResult = 0;
	string message;

	cout << "Starting Client...\n";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != 0) {
		cout << "WSAStartup() failed with error: " << iResult << endl;
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	cout << "Connecting...\n";

	// Resolve the server address and port
	iResult = getaddrinfo(static_cast<LPCTSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "getaddrinfo() failed with error: " << iResult << endl;
		WSACleanup();
		system("pause");
		return;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		client.socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (client.socket == INVALID_SOCKET) {
			cout << "socket() failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			system("pause");
			return;
		}

		// Connect to server.
		iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(client.socket);
			client.socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (client.socket == INVALID_SOCKET) {
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
		system("pause");
		return;
	}

	cout << "Successfully Connected" << endl;
	recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
	message = client.received_message;

	if (message != "Server is full")
	{
		client.id = atoi(client.received_message);
	}
	else
		cout << client.received_message << endl;



	while (status != KONIEC)
	{
		switch (status)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GRA:
			rozgrywka(client);
			break;
		
		}
	}

	cout << "Shutting down socket..." << endl;
	iResult = shutdown(client.socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown() failed with error: " << WSAGetLastError() << endl;
		closesocket(client.socket);
		WSACleanup();
		system("pause");
		return;
	}

	closesocket(client.socket);
	WSACleanup();
	system("pause");
	return;
}

void Swiat::menu()
{
	
	czcionka.loadFromFile("obrazki/arial.ttf");
	Text tytul("Boomberman", czcionka, 40);
	tytul.setStyle(Text::Bold);

	tytul.setPosition(OKNO / 2 - tytul.getGlobalBounds().width / 2, 20);

	const int ile = 2;

	Text tekst[ile];

	string str[] = { "Graj", "Wyjscie" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(czcionka);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(OKNO / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (status == MENU)
	{
		Vector2f mouse(Mouse::getPosition(oknoAplikacji));
		Event event;

		while (oknoAplikacji.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				status = KONIEC;
			else if (tekst[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				status = GRA;
			}
			else if (tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				status = KONIEC;
			}
		}
		for (int i = 0; i<ile; i++)
		if (tekst[i].getGlobalBounds().contains(mouse))
			tekst[i].setColor(Color::Cyan);
		else tekst[i].setColor(Color::White);

		oknoAplikacji.clear();

		oknoAplikacji.draw(tytul);
		for (int i = 0; i<ile; i++)
			oknoAplikacji.draw(tekst[i]);

		oknoAplikacji.display();
	}
}

void Swiat::rozgrywka(client_type client)
{

	Silnik silnik(oknoAplikacji, ilosc_graczy, client , client.id);

	silnik.odpalSilnik();

	status = MENU;
}




