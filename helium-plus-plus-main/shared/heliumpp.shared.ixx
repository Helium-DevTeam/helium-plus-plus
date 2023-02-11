module;

#include <neargye/semver.hpp>

#include <concepts>
#include <type_traits>

export module heliumpp.shared;

using namespace semver;
using namespace std;

export namespace helium
{
	constexpr version helium_version{0, 0, 1, prerelease::alpha};
}

export namespace helium
{
	template<typename T>
	concept helium_std_string = requires
	{
		requires is_same_v<decay_t<T>, string>
			|| is_same_v<decay_t<T>, wstring>
			|| is_same_v<decay_t<T>, u8string>
			|| is_same_v<decay_t<T>, u16string>
			|| is_same_v<decay_t<T>, u32string>
			|| is_same_v<decay_t<T>, pmr::string>
			|| is_same_v<decay_t<T>, pmr::wstring>
			|| is_same_v<decay_t<T>, pmr::u8string>
			|| is_same_v<decay_t<T>, pmr::u16string>
			|| is_same_v<decay_t<T>, pmr::u32string>
			|| is_same_v<decay_t<T>, string_view>
			|| is_same_v<decay_t<T>, wstring_view>
			|| is_same_v<decay_t<T>, u8string_view>
			|| is_same_v<decay_t<T>, u16string_view>
			|| is_same_v<decay_t<T>, u32string_view>;
	};
}