//#pragma warning(disable:4996) CRT_SECURE_NOWARNIGNSfa;lkjl;kf...
#define DEBUG

#include "toad.h"
#ifdef _WIN32
#include <Windows.h>
#endif

int main()
{
	sf::RenderWindow window;

	if (!toad::init(window))
		return 1;
	
	toad::run(window);
	toad::clean_up(window);
	return 0;
}