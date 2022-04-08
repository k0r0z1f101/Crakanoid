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

namespace sound
{
	//Jukebox
	class SongPlayer
	{
		string songPlayPath; //path to the song being played
		vector<string> songPlayedOnce; //list of song already played since instanciation
		static const string spPATH; //path to the song folder
		Music songPlayed; //song being played; raylib CDT
		float songElapsedTime; //time passed in song since start of song in seconds

	public:
		SongPlayer();
		void randomSongPath(); //return a random song path that hasn't played yet from the song folder
		void playSong(); //play the song in songPlayPath
		void updateStream(); //update the audio stream
		bool isSongPlaying(); //return true if the song is currently playing
		string getSongPlaying(); //return the path to the song playing
		~SongPlayer();
	};
}