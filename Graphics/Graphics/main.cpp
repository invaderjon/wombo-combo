#include "Engine.h"
#include <stdio.h>
#include <iomanip>
#include <chrono>
#include <random>
#include "IAllocator.h"
#include "StackAllocator.h"
#include "ChunkAllocator.h"
#include "DSStackAllocator.h"

using namespace graphics;
using namespace std::chrono;

//
// Title: Main
// Author: Jonathan DiGiacomo
// Version: 1.0.0
// 
// The application runner.
//

int main(int argc, char **argv)
{
	Engine engine;
	high_resolution_clock::time_point now = high_resolution_clock::now();
	std::time_t time = high_resolution_clock::to_time_t(high_resolution_clock::now());
	std::cout << std::put_time(std::localtime(&time), "%c %Z") << std::endl;

	now = high_resolution_clock::now();
	time = high_resolution_clock::to_time_t(high_resolution_clock::now());
	std::cout << std::put_time(std::localtime(&time), "%c %Z") << std::endl;

	//std::cout << tester(100) << endl;
	return engine.start(argc, argv);
}