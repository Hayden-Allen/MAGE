#pragma once
#include "pch.h"
#include "window.h"

namespace mage
{
	class MAGE_API application
	{
	public:
		MAGE_DCM(application);


		virtual void run() const = 0;
	protected:
		std::unique_ptr<window> m_window;
		bool m_running;


		application(const window_data& data) :
			m_running(true)
		{
			m_window = std::unique_ptr<window>(window::create(data));
		}
	};


	application* create_application();
}
