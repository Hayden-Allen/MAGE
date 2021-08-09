#pragma once
#include "pch.h"
#include "shader_type.h"
#include "mage/graphics/renderer.h"

namespace mage::gl
{
	class renderer final : public mage::gfx::renderer
	{
	public:
		renderer() {}
		MAGE_DCM(renderer);


		void set_clear_color(const color<float>& color) const override;
		void clear() const override;
		void draw(const mage::gfx::index_buffer* const indices, const mage::gfx::vertex_array* const vertices) const override;
		void draw(const mage::gfx::shader_program* const shader, const mage::gfx::index_buffer* const indices, const mage::gfx::vertex_array* const vertices) const override;
		void render(const window* const window) const override;
	};
}
