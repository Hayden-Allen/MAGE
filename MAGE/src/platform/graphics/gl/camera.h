#pragma once
#include "pch.h"
#include "mage/graphics/camera.h"

namespace mage::gl
{
	class orthographic_camera : public mage::gfx::orthographic_camera
	{
	public:
		orthographic_camera(event_handler_container& c, float width, float height, const glm::vec3& pos, s_type rotation, float zoom) :
			mage::gfx::orthographic_camera(c, width, height, pos, rotation, zoom)
		{
			update();
		}
		MAGE_DCM(orthographic_camera);
	public:
		void set_pos(const glm::vec3& pos) override;
	protected:
		void update() override;
	};
}
