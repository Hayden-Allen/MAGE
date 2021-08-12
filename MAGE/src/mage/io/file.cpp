#include "pch.h"
#include "file.h"

namespace mage
{
	output_file& output_file::write(uint64_t data, size_t bytes)
	{
		MAGE_ASSERT(bytes <= 8, "Writing more than 8 bytes at a time is unsupported");

		for (size_t i = bytes - 1; i >= 0; i--)
		{
			const uint64_t off = MAGE_CAST(uint64_t, i) * 8;
			uint64_t mask = MAGE_CAST(uint64_t, 0xff) << off;
			m_file << MAGE_CAST(uint8_t, (data & mask) >> off);
		}

		return *this;
	}
}
