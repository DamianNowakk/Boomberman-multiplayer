#pragma once
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
#include "Stale.h"
#include <SFML/Graphics.hpp>
#include <time.h>   
#include "Swiat.h"

using namespace std;

int main()
{
	srand(time(NULL));
	Swiat* swiat = new Swiat();
	return 0;
}