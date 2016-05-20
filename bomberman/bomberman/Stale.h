#define MAPA 13
#define OBIEKTY 64
#define WSPOMAGANIE_1_4 29
#define WSPOMAGANIE_3_4 31
#define OKNO MAPA*64
#define GRACZ1 OBIEKTY,OBIEKTY // lewy gorny
#define GRACZ2 OKNO-2*OBIEKTY,OBIEKTY // prawy gorny
#define GRACZ3 OBIEKTY,OKNO-2*OBIEKTY // lewy dolny
#define GRACZ4 OKNO-2*OBIEKTY,OKNO-2*OBIEKTY //prawy dolny

#define DEFAULT_BUFLEN 512            
#define IP_ADDRESS "localhost"
#define DEFAULT_PORT "55004"
#pragma comment (lib, "Ws2_32.lib")

