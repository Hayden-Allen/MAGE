#pragma once
#include "pch.h"
#include "mage/log.h"

namespace mage
{
	/**
	 * Interface for polling various input devices
	 */
	class input
	{
	public:
		MAGE_DCM(input);
	public:
		bool is_key_pressed(int key) const { return key_pressed(key); }
		bool is_mouse_pressed(int button) const { return mouse_pressed(button); }
		float get_mouse_x() const { return mouse_x(); }
		float get_mouse_y() const { return mouse_y(); }
		static input* const get() { return s_instance; }
	protected:
		input()
		{
			MAGE_CORE_ASSERT(s_instance != nullptr, "Cannot create multiple inputs");
			s_instance = this;
		}
	protected:
		virtual bool key_pressed(int key) const = 0;
		virtual bool mouse_pressed(int button) const = 0;
		virtual float mouse_x() const = 0;
		virtual float mouse_y() const = 0;
	private:
		static input* s_instance;
	};
}
