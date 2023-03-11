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

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include <vector>
#include <string>

export module heliumpp.terminalui.component.settings_panel;

import heliumpp.shared;
import heliumpp.terminalui.shared;

using namespace std;
using namespace ftxui;

export namespace helium {
	class helium_tui_settings_entry_bool final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_entry_bool() = default;

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_entry_integer final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_entry_integer() = default;

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_entry_float final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_entry_float() = default;

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_entry_string final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_entry_string() = default;

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_preferences_subpanel final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_preferences_subpanel() = default;

		auto Render() -> Element final
		{
			return vbox({
				text("Preferences") | bold | color(Color::BlueLight)
			}) | flex;
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_server_subpanel final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_server_subpanel() = default;

		auto Render() -> Element final
		{
			return vbox({
				text("Server") | bold | color(Color::BlueLight)
			}) | flex;
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_extension_subpanel final : public helium_object_class, public ComponentBase
	{
	public:
		helium_tui_settings_extension_subpanel() = default;

		auto Render() -> Element final
		{
			return vbox({
				text("Extension") | bold | color(Color::BlueLight)
			}) | flex;
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	class helium_tui_settings_panel_class final : public helium_object_class, public ComponentBase {
	private:
		Box box_;
		int selected_;
		vector<string> entries_;
		Components tabs_;
		Component side_menu_;
		Component menu_tabs_;
		Component settings_panel_container_;
	public:
		helium_tui_settings_panel_class() :
			selected_(0),
			entries_(
				{
					"Preferences",
					"Server",
					"Extension",
				}),
			tabs_(
				{
					Make<helium_tui_settings_preferences_subpanel>(),
					Make<helium_tui_settings_server_subpanel>(),
					Make<helium_tui_settings_extension_subpanel>(),
				}
			),
			side_menu_(Menu(&this->entries_, &this->selected_)),
			menu_tabs_(Container::Tab(this->tabs_, &this->selected_)),
			settings_panel_container_(Container::Horizontal(
				{
					side_menu_,
					menu_tabs_,
				}
			))
		{
			this->Add(this->settings_panel_container_);
		}

		auto Render() -> Element final {
			return hbox({ 
					this->side_menu_->Render(),
					separator(),
					this->menu_tabs_->Render(),
				})| flex | reflect(this->box_);
		}
		auto OnEvent(Event event) -> bool final {
			if (event.is_mouse() && not this->box_.Contain(event.mouse().x, event.mouse().y)) {
				return false;
			}
			return this->settings_panel_container_->OnEvent(event);
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};
}