#pragma once
#include "pch.h"
#include "log.h"

#ifdef MAGE_PLATFORM_WINDOWS

extern mage::application* mage::create_application();


int main(int argc, char** argv)
{
	mage::log::init();
	MAGE_CORE_INFO("TEST {}", 5.5f);
	MAGE_WARN("Uh oh");

	mage::application* app = mage::create_application();
	app->run();
	delete app;
	return 0;
}

#endif
