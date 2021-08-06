#pragma once
#include "pch.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "util/color.h"
#include "window.h"

namespace mage::gfx
{
	class renderer
	{
	public:
		MAGE_DCM(renderer);
		virtual ~renderer() {}

		static renderer* create();
		virtual void set_clear_color(const color<float>& color) const = 0;
		virtual void clear() const = 0;
		virtual void draw(const index_buffer* const indices, const vertex_array* const vertices) const = 0;
		virtual void render(const window* const window) const = 0;
	protected:
		renderer() {}
	};
}
