#pragma once
#include "pch.h"
#include "log.h"
#include "application.h"

/**
 * Driver file. This is the entry point for any client application. Behaviour is controlled by creating an application implementation in the client and defining create_application.
 */

extern mage::application* create_application();

int main(int argc, char** argv)
{
	mage::log::init();

	mage::application* app = mage::create_application();
	app->run();
	delete app;

	return 0;
}
