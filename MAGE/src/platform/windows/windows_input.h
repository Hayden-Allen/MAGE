#pragma once
#include "pch.h"
#include "mage/input/input.h"

namespace mage
{
	/**
	 * Windows implementation of the input polling interface
	 */
	class windows_input final : public input
	{
	public:
		windows_input() {}
		MAGE_DCM(windows_input);
	protected:
		bool key_pressed(int key) const override;
		bool mouse_pressed(int button) const override;
		float mouse_x() const override;
		float mouse_y() const override;
	};
}
