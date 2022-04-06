#include "raylib.h"
#include "crakanoid.h"

namespace crakanoid
{
	//choose a random song that hasn't played yet in the song repertory
	string randomSong(vector<string>& songPlayedOnce)
	{
		vector<string> songPaths = {};
		for(const auto & file : DIR)
		{
			cout << file.path() << endl;
			auto teststr = std::find(songPlayedOnce.begin(), songPlayedOnce.end(), file.path());
			if(teststr != std::end(songPlayedOnce))
			{
				cout << "In there!" << endl;
			}
			else
			{
				songPaths.push_back(file.path());
			}
		}

		cout << songPaths.size() << endl;
		cout << songPlayedOnce.size() << endl;

		int randNumber = rand() % songPaths.size();
		cout << "rand: " << randNumber << endl;
		cout << "song path: " << songPaths[1] << endl;

		string songPlayPath = songPaths[randNumber];
		songPlayedOnce.push_back(songPaths[randNumber]);
		cout << songPlayedOnce.size() << endl;

		cout << "song played: " << songPlayPath << endl;

		return songPlayPath;
	}
}
