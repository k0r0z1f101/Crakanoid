#include "raylib.h"
#include "sound.h"

namespace sound
{
	const string SongPlayer::spPATH = "/home/wa/git/Crakanoid/resources/"; //path to the song folder

	SongPlayer::SongPlayer()
	{
		songElapsedTime = {};
		musicVolume = 0.1f;
	}

	void SongPlayer::randomSongPath()
	{
		vector<string> songPaths = {}; //paths to songs that haven't played yet
		int count;
		char** files = GetDirectoryFiles(spPATH.c_str(), &count);

		//loop through songs in the song folder and build a list of paths to songs that have not played yet
		for (int i = 0; i < count; i++) {

			//check if file is a valid format, if not continue to next loop iteration
			char *output = NULL;
			output = strstr (files[i],".mp3");
			if(!output) continue;

			//add to list if song has not played yet
			auto testPath = std::find(songPlayedOnce.begin(), songPlayedOnce.end(), files[i]);
			if(testPath == std::end(songPlayedOnce))
			{
				songPaths.push_back(files[i]);
			}
		}
		ClearDirectoryFiles();

		//if there are still song that haven't played, choose one randomly
		if(songPaths.size() != 0)
		{
			int randNumber = GetRandomValue(0, int(songPaths.size()-1)); //choose a random song from the list of song that have not played
			songPlayPath = songPaths[randNumber]; //store the chosen song path in a class private string
			songPlayedOnce.push_back(songPaths[randNumber]); //add the song to the list of song played
		}
		else
		{
			songPlayedOnce = {}; //reset the list of song already played so we can play them again
		}
	}

	void SongPlayer::playSong()
	{
		songPlayed = LoadMusicStream((spPATH + songPlayPath).c_str()); //load the song from the path to a private member
		SetMusicVolume(songPlayed, musicVolume);
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

	void SongPlayer::changeVolume()
	{
		if(IsKeyPressed(KEY_W))
			musicVolume += 0.05f;
		else if (IsKeyDown(KEY_W))
			musicVolume += 0.005f;

		if(IsKeyPressed(KEY_S))
			musicVolume -= 0.05f;
		else if (IsKeyDown(KEY_S))
			musicVolume -= 0.005f;

		musicVolume = musicVolume < 0.0f ? 0.0f : (musicVolume > 1.0f ? 1.0f : musicVolume);

		SetMusicVolume(songPlayed, musicVolume);
	}

	SongPlayer::~SongPlayer()
	{

	}

	//Sample Player definitions

	const string SamplePlayer::sapPATH = "/home/wa/git/Crakanoid/resources/sound/"; //path to the sample folder

	SamplePlayer::SamplePlayer()
	{

	}
	void SamplePlayer::playSample(string path)
	{
		samplePlayed = LoadSound((sapPATH + path).c_str());
		PlaySoundMulti(samplePlayed);
	}
	void changeVolume()
	{

	}
	SamplePlayer::~SamplePlayer()
	{
	    StopSoundMulti();       // We must stop the buffer pool before unloading
		UnloadSound(samplePlayed);     // Unload sound data
	}
}
