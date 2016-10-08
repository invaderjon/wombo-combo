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
	system_clock::time_point now = system_clock::now();
	std::time_t time = system_clock::to_time_t(system_clock::now());
	std::cout << std::put_time(std::localtime(&time), "%c %Z") << std::endl;

	now = system_clock::now();
	time = system_clock::to_time_t(system_clock::now());
	std::cout << std::put_time(std::localtime(&time), "%c %Z") << std::endl;

	Plane p = Plane(Vec3(0, 0, 1), Vec3(1, 1, 1), Vec3(-1, 1, 1));
	Vec3 pt = Vec3(0, 0, 0);
	printf("Normal: <%f, %f, %f>\n", p.normal().x, p.normal().y, p.normal().z);
	printf("Distance: %f\n", p.dist(pt));
	pt += p.normal() * p.dist(pt);
	printf("Displacement: <%f, %f, %f>\n", pt.x, pt.y, pt.z);

	//std::cout << tester(100) << endl;
	return engine.start(argc, argv);
}