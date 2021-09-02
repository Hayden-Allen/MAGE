#pragma once
#define MAGE_WRAP(CLASS, PARENT, SIG, INIT, ...) \
	class CLASS final : public COGA_RAN::PARENT { \
	public: \
		CLASS SIG : COGA_RAN::PARENT INIT {} \
		COGA_DCM(CLASS); \
		__VA_ARGS__ };
#define MAGE_WRAP_VIRTUAL(CLASS, PARENT, SIG, INIT, ...) \
	class CLASS final : public COGA_RAN::PARENT { \
	public: \
		CLASS SIG, COGA_RAN::PARENT INIT {} \
		COGA_DCM(CLASS); \
		__VA_ARGS__ };
