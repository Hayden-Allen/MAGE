#pragma once
#include "pch.h"

namespace mage
{
	MAGE_WRAP
	(
		camera,
		orthographic_camera,
		(coga::event_handler_container& c, float width, float height, const glm::vec3& pos, float rotation, float zoom),
		(c, width, height, pos, rotation, zoom)
	);
}
