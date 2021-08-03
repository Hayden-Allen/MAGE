#pragma once

namespace mage
{
	__declspec(dllimport) void print();
}


int main()
{
	mage::print();
	return 0;
}
