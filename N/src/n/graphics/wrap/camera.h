#pragma once
#include "pch.h"

namespace n
{
	N_WRAP
	(
		camera,
		orthographic_camera,
		(mage::event_handler_container& c, float width, float height, const glm::vec3& pos, float rotation, float zoom),
		(c, width, height, pos, rotation, zoom)
	);
}
