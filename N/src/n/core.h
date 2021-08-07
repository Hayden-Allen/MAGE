#pragma once
// for convenience to delete copy/move constructors
#define N_DCM(name) \
	name(const name& other) = delete; \
	name(name&& other) = delete;
#define N_DC(name) \
	name(const name& other) = delete;
#define N_DM(name) \
	name(name&& other) = delete;
// additional utils
#define N_BIT(x) (1 << x)
#define N_CAST(T, x) static_cast<T>(x)
#define N_PUN(T, x) *(T*)&x
#define N_WRAP(CLASS, PARENT, SIG, INIT, ...) \
	class CLASS final : public MAGE_RAN::PARENT { \
	public: \
		CLASS SIG : MAGE_RAN::PARENT INIT {} \
		N_DCM(CLASS); \
		__VA_ARGS__ };
