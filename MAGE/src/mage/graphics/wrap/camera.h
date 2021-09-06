#pragma once
#include "pch.h"

namespace mage
{
	class camera final : public COGA_RAN::orthographic_camera
	{
	public:
		camera(coga::event_handler_container& c, float width, float height, const glm::vec3& pos, float rotation, float zoom) :
			COGA_RAN::orthographic_camera(c, width, height, pos, rotation, zoom)
		{}
		COGA_DCM(camera);
	};
}
