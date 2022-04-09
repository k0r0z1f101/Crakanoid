#include "raylib.h"
#include "sound.h"

namespace sound
{
	const string SongPlayer::spPATH = "../resources/"; //path to the song folder

	SongPlayer::SongPlayer()
	{
	}

	void SongPlayer::randomSongPath()
	{
		vector<string> songPaths = {}; //paths to songs that haven't played yet
		int count;
		char** files = GetDirectoryFiles(spPATH.c_str(), &count);

		//loop through songs in the song folder and build a list of paths to songs that have not played yet
//		printf("Count: %i\n", count);
		for (int i = 0; i < count; i++) {
//		    printf("File: %s\n", files[i]);
			auto testPath = std::find(songPlayedOnce.begin(), songPlayedOnce.end(), files[i]);
			if(testPath != std::end(songPlayedOnce))
			{
			}
			else
			{
				songPaths.push_back(files[i]);
			}
		}
		ClearDirectoryFiles();

		//if there are still song that haven't played, choose one randomly
		if(songPaths.size() != 0)
		{
			int randNumber = rand() % songPaths.size(); //choose a random song from the list of song that have not played
			songPlayPath = songPaths[randNumber]; //store the chosen song path in a class private string
			songPlayedOnce.push_back(songPaths[randNumber]); //add the song to the list of song played
		}
	}

	void SongPlayer::playSong()
	{
		songPlayed = LoadMusicStream((spPATH + songPlayPath).c_str()); //load the song from the path to a private member
		PlayMusicStream(songPlayed); //start the loaded song
		songElapsedTime = 0.0f; //reset the time the current song has played for
	}

	void SongPlayer::updateStream()
	{
		float currentElapsed = GetMusicTimePlayed(songPlayed); //get the current time the song has played for

		//stop, unload the song and reset the time passed for the current song if the song has restarted playing (can't seem to find a way to not play it looped)
		if(currentElapsed < songElapsedTime)
		{
			StopMusicStream(songPlayed);
			UnloadMusicStream(songPlayed);
			songElapsedTime = 0.0f;
		}
		//continue playing if it's not restarted
		else
		{
			songElapsedTime = currentElapsed; //marker to compare on the next update
			UpdateMusicStream(songPlayed); // update audio buffer with new stream data
		}
	}

	bool SongPlayer::isSongPlaying()
	{
		return IsMusicStreamPlaying(songPlayed);
	}

	string SongPlayer::getSongPlaying()
	{
		return songPlayPath;
	}

	SongPlayer::~SongPlayer()
	{

	}
}
