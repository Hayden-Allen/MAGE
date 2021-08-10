#pragma once
#include "pch.h"

namespace n
{
	template<std::ios_base::openmode FLAGS>
	class file
	{
	public:
		N_DCM(file);
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
		N_DCM(input_file);


		uint8_t get_byte()
		{
			return m_file.get();
		}
		uint16_t get_short()
		{
			return (N_CAST(uint16_t, get_byte()) << 8) | get_byte();
		}
		uint32_t get_int()
		{
			return (N_CAST(uint32_t, get_short()) << 16) | get_short();
		}
		uint64_t get_long()
		{
			return (N_CAST(uint64_t, get_int()) << 32) | get_int();
		}
	};



	class output_file final : public file<std::ios::binary | std::ios::out>
	{
	public:
		output_file(const std::string& fp) :
			file<std::ios::binary | std::ios::out>(fp)
		{}
		N_DCM(output_file);


		output_file& put_byte(uint8_t b)
		{
			return put(N_CAST(uint64_t, b), 1);
		}
		output_file& put_short(uint16_t s)
		{
			return put(N_CAST(uint64_t, s), 2);
		}
		output_file& put_int(uint32_t i)
		{
			return put(N_CAST(uint64_t, i), 3);
		}
		output_file& put_long(uint64_t l)
		{
			return put(l, 4);
		}
	private:
		output_file& put(uint64_t data, size_t bytes);
	};
}
