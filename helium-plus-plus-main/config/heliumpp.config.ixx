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

#include <toml++/toml.h>

#include <any>
#include <memory>
#include <ranges>
#include <string>

export module heliumpp.config;

import heliumpp.shared;

using namespace std;

export namespace helium
{
	class helium_config_entry final : public helium_object_class
	{
	private:
		weak_ptr<toml::table> config_table_;
		string config_entry_;
		any value_;
	public:
		helium_config_entry(weak_ptr<toml::table> config_table, const string_view config_entry) :
			config_table_(config_table),
			config_entry_(config_entry)
		{}

		auto read_value() -> void
		{
			if(auto ptr = this->config_table_.lock())
			{
				this->value_ = ptr->at_path(this->config_entry_);
			}
		}

		auto set_value(auto& value) -> void
		{
			if(auto ptr = this->config_table_.lock())
			{
				ptr->at_path(this->config_entry_) = value;
			}
		}

		auto get_value() const -> any
		{
			return this->value_;
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_config_manager_class final : public helium_abstract_manager_class<shared_ptr<helium_config_entry>, weak_ptr<helium_config_entry>>
	{
	private:
		string config_file_name_;
		shared_ptr<toml::table> config_table_;
	public:
		explicit helium_config_manager_class(const string_view config_file_name) :
			config_file_name_(config_file_name)
		{
			this->config_table_ = make_shared<toml::table>(move(toml::parse_file(this->config_file_name_)));
		}

		auto read_all() -> void
		{
			for(const auto& value : this->item_map_ | views::values)
			{
				value->read_value();
			}
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	helium_config_manager_class helium_config_manager("heliumpp_config.toml");
}