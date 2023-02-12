module;

#include <neargye/semver.hpp>

#include <concepts>
#include <string>
#include <format>
#include <type_traits>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

export module heliumpp.shared;

using namespace semver;
using namespace std;

export namespace helium
{
	constexpr version helium_version{0, 0, 1, prerelease::alpha};
}

export namespace helium
{
	using namespace boost::uuids;

	class helium_object_class
	{
	private:
		uuid object_uuid_ = random_generator()();
	public:
		virtual ~helium_object_class() = default;

		virtual auto to_string() const -> string
		{
			return format("obj:helium_object_class<{}>", this->uuid_string());
		}
		auto uuid_string() const -> string
		{
			return boost::uuids::to_string(this->object_uuid_);
		}
		auto uuid() const -> uuid
		{
			return this->object_uuid_;
		}
	};
}

export namespace helium	//concepts utils, only in C++20 and after
{
	template <typename T>
	concept helium_object =
			   same_as<remove_cvref_t<T>, helium_object_class>
			or derived_from<remove_cvref_t<T>, helium_object_class>;

	template <typename T>
	concept helium_std_string = 
		       same_as<remove_cvref_t<T>, string>
			or same_as<remove_cvref_t<T>, wstring>
			or same_as<remove_cvref_t<T>, u8string>
			or same_as<remove_cvref_t<T>, u16string>
			or same_as<remove_cvref_t<T>, u32string>
			or same_as<remove_cvref_t<T>, pmr::string>
			or same_as<remove_cvref_t<T>, pmr::wstring>
			or same_as<remove_cvref_t<T>, pmr::u8string>
			or same_as<remove_cvref_t<T>, pmr::u16string>
			or same_as<remove_cvref_t<T>, pmr::u32string>
			or same_as<remove_cvref_t<T>, string_view>
			or same_as<remove_cvref_t<T>, wstring_view>
			or same_as<remove_cvref_t<T>, u8string_view>
			or same_as<remove_cvref_t<T>, u16string_view>
			or same_as<remove_cvref_t<T>, u32string_view>;

	template <typename T>
	concept helium_char =
			   same_as<remove_cvref_t<T>, char>
			or same_as<remove_cvref_t<T>, wchar_t>
			or same_as<remove_cvref_t<T>, char8_t>
			or same_as<remove_cvref_t<T>, char16_t>
			or same_as<remove_cvref_t<T>, char32_t>
			or same_as<remove_cvref_t<T>, signed char>
			or same_as<remove_cvref_t<T>, unsigned char>;

	template <typename T>
	concept helium_integral = integral<T>;

	template <typename T>
	concept helium_floating_point = is_floating_point_v<T>;

	template <typename T>
	concept helium_nullptr = same_as<remove_cvref_t<T>, nullptr_t>;

	template <typename T>
	concept helium_not_nullptr = not helium_nullptr<T>;

	template <typename T>
	concept helium_pointer = is_pointer_v<remove_cvref_t<T>>;

	template <typename T>
	concept helium_hashable = 
		       helium_integral<T>
			or helium_std_string<T>
			or helium_floating_point<T>
			or helium_nullptr<T>
			or helium_pointer<T>
			or helium_char<T>;
}