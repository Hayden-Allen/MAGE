#pragma once
#include "pch.h"
#include "mage/graphics/camera.h"

namespace mage::gl
{
	class orthographic_camera final : public mage::gfx::orthographic_camera
	{
	public:
		orthographic_camera(float left, float right, float bottom, float top, const glm::vec3& pos, float rotation) :
			mage::gfx::orthographic_camera(left, right, bottom, top, pos, rotation)
		{
			update();
		}
		MAGE_DCM(orthographic_camera);


		void set_pos(const glm::vec3& pos) override;
	protected:
		void update() override;
	};
}
