/*
* Helium++ is a customizable extension system for Minecraft server.
* You can get the latest source code and releases of Helium++ at :
* https://github.com/Helium-DevTeam/helium-plus-plus
* ----------------------------------------------------------------------------------------
* Helium++ Copyright (C) 2021-2023 Helium-DevTeam
*
* This file is a part of Helium++
*
* Helium++ is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium++ is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium++.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include <neargye/semver.hpp>

#include <memory>
#include <concepts>
#include <random>
#include <string>
#include <format>
#include <expected>
#include <map>
#include <type_traits>
#include <stduuid/uuid.h>

export module heliumpp.shared;

using namespace semver;
using namespace std;

export namespace helium
{
	constexpr version helium_version{0, 0, 2, prerelease::alpha};
}

export namespace helium
{
	using namespace uuids;

	/**
	 * \brief The common base class for all helium classes.
	 */
	class helium_object_class
	{
	private:
		uuid object_uuid_;
	public:
		helium_object_class()
		{
			std::random_device rd;
			auto seed_data = std::array<int, std::mt19937::state_size> {};
			ranges::generate(seed_data, std::ref(rd));
			std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
			std::mt19937 generator(seq);
			uuid_random_generator gen{generator};
			this->object_uuid_ = gen();
		}

		virtual ~helium_object_class() = default;

		virtual auto to_string() const -> string
		{
			return format("obj:helium_object_class<{}>", this->uuid_string());
		}
		auto uuid_string() const -> string
		{
			return uuids::to_string(this->object_uuid_);
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
	concept helium_floating_point = floating_point<T>;

	template <typename T>
	concept helium_nullptr = same_as<remove_cvref_t<T>, nullptr_t>;

	template <typename T>
	concept helium_not_nullptr = not helium_nullptr<T>;

	template <typename T>
	concept helium_pointer = is_pointer_v<remove_cvref_t<T>>;

	template <typename T>
	concept helium_uuid = same_as<remove_cvref_t<T>, uuids::uuid>;

	template <typename T>
	concept helium_hashable = requires(T a){
		requires helium_integral<T>
			or helium_std_string<T>
			or helium_floating_point<T>
			or helium_nullptr<T>
			or helium_pointer<T>
			or helium_char<T>
			or helium_uuid<T>;

		typename std::hash<T>;

		{ std::hash<T>{}(a) } -> convertible_to<size_t>;
	};
}

export namespace helium
{
	/**
	 * \brief helium_abstract_manager_class is a interface class for manager classes.
	 * \tparam ItemT Smart pointers to items
	 * \tparam NotOwningItemT Non-owning Smart pointers to items
	 * \tparam ItemUidT UID for items, uuids::uuid by default
	 * \tparam ItemNameT Name for items, std::string by default
	 */
	template<typename ItemT, typename NotOwningItemT, helium_hashable ItemUidT = uuids::uuid, helium_hashable ItemNameT = std::string>
		requires convertible_to<remove_cvref_t<ItemT>, remove_cvref_t<NotOwningItemT>>
	class helium_abstract_manager_class : public helium_object_class
	{
		using item_t = remove_cvref_t<ItemT>;
		using non_owning_item_t = remove_cvref_t<NotOwningItemT>;
		using item_uid_t = remove_cvref_t<ItemUidT>;
		using item_name_t = remove_cvref_t<ItemNameT>;
		using uid_map_t = std::unordered_map<item_name_t, item_uid_t>;
		using item_map_t = std::unordered_map<item_uid_t, item_t>;
		using item_expected_t = std::expected<non_owning_item_t, std::string>;
		using owning_item_expected_t = std::expected<item_t, std::string>;
		using uid_expected_t = std::expected<item_uid_t, std::string>;

	private:
		uid_map_t uid_map_ = {};
		item_map_t item_map_ = {};

	public:
		helium_abstract_manager_class() = default;	//default constructor
		helium_abstract_manager_class(helium_abstract_manager_class&& rhs) = default;	//move constructor
		helium_abstract_manager_class(const helium_abstract_manager_class& rhs) = delete;	//NO COPY

		auto operator=(const helium_abstract_manager_class& rhs) -> helium_abstract_manager_class& = delete;	//NO COPY
		auto operator=(helium_abstract_manager_class&& rhs) -> helium_abstract_manager_class& = default;	//move assignment

		auto get_item(item_name_t const& item_name) const -> item_expected_t
		{
			if(this->uid_map_.contains(item_name))
			{
				return this->item_map_.at(this->uid_map_.at(item_name));
			}
			return unexpected("item_name lookup failed");
		}
		auto get_item(item_uid_t const& item_uid) const -> item_expected_t
		{
			if(this->item_map_.contains(item_uid))
			{
				return this->item_map_.at(item_uid);
			}
			return unexpected("item_uid lookup failed");
		}
		auto get_item_owning(item_name_t const& item_name) const -> owning_item_expected_t
		{
			if(this->uid_map_.contains(item_name))
			{
				return this->item_map_.at(this->uid_map_.at(item_name));
			}
			return unexpected("item_name lookup failed");
		}
		auto get_item_owning(item_uid_t const& item_uid) const -> owning_item_expected_t
		{
			if(this->item_map_.contains(item_uid))
			{
				return this->item_map_.at(item_uid);
			}
			return unexpected("item_uid lookup failed");
		}
		auto get_uid(item_name_t const& item_name) const -> uid_expected_t
		{
			if(this->uid_map_.contains(item_name))
			{
				return this->uid_map_.at(item_name);
			}
			return unexpected("item_name lookup failed");
		}
		auto set_item(item_name_t const& item_name, item_t const& item)
		{
			if(this->uid_map_.contains(item_name))
			{
				this->item_map_.at(this->uid_map_.at(item_name)) = item;
			}
		}
		auto set_item(item_uid_t const& item_uid, item_t const& item)
		{
			if(this->uid_map_.contains(item_uid))
			{
				this->item_map_.at(item_uid) = item;
			}
		}
	};
}