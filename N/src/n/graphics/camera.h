#pragma once
#include "pch.h"

namespace n
{
	N_WRAP
	(
		camera,
		orthographic_camera,
		(float left, float right, float bottom, float top, const glm::vec3& pos, float rotation),
		(left, right, bottom, top, pos, rotation)
	);
}
