#pragma once
#include "pch.h"

namespace mage
{
	template<std::ios_base::openmode FLAGS>
	class file
	{
	public:
		MAGE_DCM(file);
		virtual ~file()
		{
			m_file.close();
		}

	protected:
		std::fstream m_file;


		file(const std::string& fp) :
			m_file(fp, FLAGS)
		{
			MAGE_ASSERT(m_file.is_open(), "Failed to open file {}", fp);
		}
	};



	class input_file final : public file<std::ios::binary | std::ios::in>
	{
	public:
		input_file(const std::string& fp) :
			file<std::ios::binary | std::ios::in>(fp)
		{}
		MAGE_DCM(input_file);


		uint8_t ubyte()
		{
			return m_file.get();
		}
		uint16_t ushort()
		{
			return (MAGE_CAST(uint16_t, ubyte()) << 8) | ubyte();
		}
		uint32_t uint()
		{
			return (MAGE_CAST(uint32_t, ushort()) << 16) | ushort();
		}
		uint64_t ulong()
		{
			return (MAGE_CAST(uint64_t, uint()) << 32) | uint();
		}
	};



	class output_file final : public file<std::ios::binary | std::ios::out>
	{
	public:
		output_file(const std::string& fp) :
			file<std::ios::binary | std::ios::out>(fp)
		{}
		MAGE_DCM(output_file);


		output_file& ubyte(uint8_t b)
		{
			return write(MAGE_CAST(uint64_t, b), 1);
		}
		output_file& ushort(uint16_t s)
		{
			return write(MAGE_CAST(uint64_t, s), 2);
		}
		output_file& uint(uint32_t i)
		{
			return write(MAGE_CAST(uint64_t, i), 3);
		}
		output_file& ulong(uint64_t l)
		{
			return write(l, 4);
		}
		output_file& write(uint64_t data, size_t bytes);
	};
}
