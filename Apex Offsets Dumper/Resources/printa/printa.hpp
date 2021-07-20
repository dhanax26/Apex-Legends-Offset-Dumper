#pragma once
#include "macros.hpp"
#include "../Singleton/singleton.hpp"

typedef enum printa_e : uint32_t
{
	okay         = 0,
	input      = 1,
	loading    = 2,
	fail       = 3,
	found	   = 4,
	notfound   = 5,
};

class printa_c : public singleton<printa_c>
{
public:

	inline printa_c( )
	{
		const auto console_handle = GetConsoleWindow();
		const auto stream_handle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTitle(xorstr_("Apex Legends Dumper by dhanax26 - v1.0.2"));

		SetConsoleMode(stream_handle, 0x7);

		CloseHandle(console_handle);
	}
	inline ~printa_c( ) = default;


	template <printa_e type = printa_e::okay, typename ...args_t>
	constexpr __forceinline auto print( const std::string_view format, args_t... args ) -> void
	{
		PRINTA_PRE( );

		const auto [fmt_style, fmt_str] = this->get_format<type>( );
		fmt::print( fmt_style, fmt_str );

		PRINTA_POST( );

		fmt::print( format.data( ), args... );
	}

	template <printa_e type = printa_e::okay, typename ...args_t>
	constexpr __forceinline auto print( const std::wstring_view format, args_t... args ) -> void
	{
		PRINTA_PRE( );

		const auto [fmt_style, fmt_str] = this->get_format<type>( );
		fmt::print( fmt_style, fmt_str );

		PRINTA_POST( );

		fmt::print(fmt::emphasis::bold, format.data( ), args...);
	}

	template <uint32_t indentation>
	constexpr __forceinline auto project( const std::string_view project_name) -> void
	{
		std::string pre{ xorstr_("\r\n") }; for ( auto idx = 0u; idx < indentation; idx++ ) { pre += std::string{ xorstr_(" ") }; }

		fmt::print(pre);
		fmt::print( fg( fmt::color::hot_pink ) | fmt::emphasis::underline | fmt::emphasis::bold, project_name.data());
		fmt::print(xorstr_("\r\n") );

		updated<42>();
	}

	template <uint32_t indentation>
	constexpr __forceinline auto title(const std::string_view project_name) -> void
	{
		std::string pre{ xorstr_("\r\n") }; for (auto idx = 0u; idx < indentation; idx++) { pre += std::string{ xorstr_(" ") }; }

		fmt::print(pre);
		fmt::print(fg(fmt::color::white) | fmt::emphasis::underline | fmt::emphasis::bold, project_name.data());
		fmt::print(xorstr_("\r\n"));
	}

	template <uint32_t indentation>
	constexpr __forceinline auto updated() -> void
	{
		std::string pre{ xorstr_("\r\n") }; for (auto idx = 0u; idx < indentation; idx++) { pre += std::string{ xorstr_(" ") }; }

		const char* const LastUpdate = "Last Update " __DATE__ " at " __TIME__;
		std::string_view project_name = LastUpdate; //+ __DATE__ " @ " __TIME__;

		fmt::print(pre);
		fmt::print(fg(fmt::color::lime_green) | fmt::emphasis::underline | fmt::emphasis::bold, project_name.data());
		fmt::print(xorstr_("\r\n"));
	}

private:

	template <printa_e type>
	constexpr __forceinline auto get_format() -> std::pair<fmt::v7::text_style, std::string_view>
	{
		std::pair<fmt::v7::text_style, std::string_view> values = {};

		switch (type)
		{
			case okay:
			{
				values.first = fg(fmt::color::lawn_green);
				values.second = xorstr_("Good");
				break;
			}
			case input:
			{
				values.first = fg(fmt::color::yellow);
				values.second = xorstr_("-->");
				break;
			}
			case loading:
			{
				values.first = fg(fmt::color::sky_blue);
				values.second = xorstr_("Waiting");
				break;
			}
			case fail:
			{
				values.first = fg(fmt::color::red);
				values.second = xorstr_("Fail");
				break;
			}
			case found:
			{
				values.first = fg(fmt::color::lawn_green);
				values.second = xorstr_("Found");
				break;
			}
			case notfound:
			{
				values.first = fg(fmt::color::orange_red);
				values.second = xorstr_("Not Found");
				break;
			}
		}

		return values;
	}
};

inline auto printa = printa_c::instance( );