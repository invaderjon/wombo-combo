#include "Manager.h"

using namespace graphics;

//
// Title: Main
// Author: Jonathan DiGiacomo
// Version: 1.0.0
// 
// The application runner.
//

int main(int argc, char **argv)
{
	Manager manager;
	manager.init(argc, argv);
	return manager.start("Wombo Combo");
}