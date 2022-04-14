#include "raylib.h"
#include "crakanoid.h"
#include "sound.h"

using namespace crakanoid;

namespace tools
{
	float getMagnitude(Vector2 vec)
	{
		return sqrtf(pow(vec.x,2) + pow(vec.y,2));
	}

	Vector2 normalizeVector(Vector2 vec)
	{
		float mag = getMagnitude(vec);
		vec.x = vec.x / mag;
		vec.y = vec.y / mag;
		return vec;
	}
}
