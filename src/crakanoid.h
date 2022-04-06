#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <experimental/filesystem>
#include <chrono>
#include <array>
#include <random>
#include <iomanip>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;
using std::experimental::filesystem::directory_iterator;

#define MAX_SAMPLES               512
#define MAX_SAMPLES_PER_UPDATE   4096

const string PATH = "../resources/";
const auto DIR = directory_iterator(PATH);

namespace crakanoid
{
	string randomSong(vector<string>& songPlayedOnce);	//choose a random song that hasn't played yet in the song repertory
}
