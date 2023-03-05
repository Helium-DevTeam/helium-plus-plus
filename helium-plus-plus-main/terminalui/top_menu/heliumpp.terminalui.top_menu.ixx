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
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include <vector>
#include <string>
#include <memory>

export module heliumpp.terminalui.top_menu;

import heliumpp.shared;
import heliumpp.terminalui.shared;

using namespace std;
using namespace ftxui;

export namespace helium {
	class helium_tui_top_menu_class final : public helium_object_class, public ComponentBase {
		int selected_;
		vector<string> tab_entries_;
		Components tab_children_;
		Component tab_container_;
		Component tab_menu_;
		Component main_container_;
	public:
		explicit helium_tui_top_menu_class(vector<string> tab_entries, Components tab_children) :
			selected_(0),
			tab_entries_(tab_entries),
			tab_children_(tab_children),
			tab_container_(Container::Tab(this->tab_children_, &this->selected_)),
			tab_menu_(Menu(&this->tab_entries_, &this->selected_, helium_horizontal_menu_option())),
			main_container_(Container::Vertical({
					tab_menu_,
					tab_container_
				}))
		{
			this->Add(this->tab_container_);
			this->Add(this->tab_menu_);
			this->Add(this->main_container_);
		}

		auto Render() -> Element final {
			return this->main_container_->Render();
		}
		auto OnEvent(Event event) -> bool final {
			return this->main_container_->OnEvent(event);
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	auto make_helium_tui_top_menu(vector<string> tab_entries, Components tab_children) -> shared_ptr<helium_tui_top_menu_class> {
		return make_shared<helium_tui_top_menu_class>(tab_entries, tab_children);
	}
}