#pragma once
#include "pch.h"

#ifdef MAGE_PLATFORM_WINDOWS

extern mage::application* mage::create_application();


int main(int argc, char** argv)
{
	mage::application* app = mage::create_application();
	app->run();
	delete app;
	return 0;
}

#endif
