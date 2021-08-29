#pragma once
// for convenience to delete copy/move constructors
#define MAGE_DCM(name) \
	name(const name& other) = delete; \
	name(name&& other) = delete;
#define MAGE_DC(name) \
	name(const name& other) = delete;
#define MAGE_DM(name) \
	name(name&& other) = delete;
// additional utils
#define MAGE_BIT(x) (1 << x)
#define MAGE_CAST(T, x) static_cast<T>(x)
#define MAGE_PUN(T, x) *(T*)&x
#define MAGE_MTU ::mage::gfx::context::get_max_texture_units()
#define MAGE_APP ::mage::application::get()
#define MAGE_WIN ::mage::application::get().get_window()
#define MAGE_IN ::mage::input::get()
