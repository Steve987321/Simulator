//#pragma warning(disable:4996) CRT_SECURE_NOWARNIGNSfa;lkjl;kf...
#define DEBUG

#include "toad.h"
#include <Windows.h>

int main()
{
	if (!toad::init()) return 1;
	toad::run();
	toad::clean_up();
	return 0;
}