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
#define MAGE_WRAP(CLASS, PARENT, SIG, INIT, ...) \
	class CLASS final : public COGA_RAN::PARENT { \
	public: \
		CLASS SIG : COGA_RAN::PARENT INIT {} \
		MAGE_DCM(CLASS); \
		__VA_ARGS__ };
#define MAGE_WRAP_VIRTUAL(CLASS, PARENT, SIG, INIT, ...) \
	class CLASS final : public COGA_RAN::PARENT { \
	public: \
		CLASS SIG, COGA_RAN::PARENT INIT {} \
		MAGE_DCM(CLASS); \
		__VA_ARGS__ };
