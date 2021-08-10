#include "pch.h"
#include "file.h"

namespace n
{
	output_file& output_file::put(uint64_t data, size_t bytes)
	{
		MAGE_ASSERT(bytes <= 4, "Writing more than 4 bytes at a time is unsupported");

		for (size_t i = bytes - 1; i >= 0; i--)
		{
			const uint64_t off = N_CAST(uint64_t, i) * 8;
			uint64_t mask = N_CAST(uint64_t, 0xff) << off;
			m_file << N_CAST(uint8_t, (data & mask) >> off);
		}

		return *this;
	}
}
