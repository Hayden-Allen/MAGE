#pragma once
#include "pch.h"
#include "log.h"
#include "application.h"

#ifdef MAGE_PLATFORM_WINDOWS

extern mage::application* create_application();

int main(int argc, char** argv)
{
	mage::log::init();

	mage::application* app = mage::create_application();
	app->run();
	delete app;

	return 0;
}

#endif
