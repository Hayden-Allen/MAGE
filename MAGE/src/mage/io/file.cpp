#include "pch.h"
#include "file.h"

namespace mage
{
	output_file& output_file::put(uint64_t data, size_t bytes)
	{
		MAGE_ASSERT(bytes <= 8, "Writing more than 8 bytes at a time is unsupported");

		for (int i = bytes - 1; i >= 0; i--)
		{
			/*const uint64_t off = MAGE_CAST(uint64_t, i) * 8;
			const uint64_t mask = MAGE_CAST(uint64_t, 0xff) << off;
			m_file << MAGE_CAST(uint8_t, (data & mask) >> off);*/
			uint64_t mask = MAGE_CAST(uint64_t, 0xff) << (MAGE_CAST(uint64_t, i) * 8);
			m_file << MAGE_CAST(uint8_t, (data & mask) >> i * 8);
		}

		return *this;
	}
}
