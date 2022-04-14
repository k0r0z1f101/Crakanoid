#pragma once
#include "crakanoid.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <chrono>
#include <array>
#include <random>
#include <iomanip>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;

using namespace crakanoid;

namespace tools
{
	float getMagnitude(Vector2 vec); //return length of vector
	Vector2 normalizeVector(Vector2 vec); //normalize vector
}
