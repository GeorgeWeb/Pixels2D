#include "Pixels2DErrors.h"

#include <iostream>
#include <cstdlib>

using namespace Pixels2D;

void Errors::fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(69);
}