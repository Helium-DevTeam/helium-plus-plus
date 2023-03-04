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

export module heliumpp.terminalui.main;

import heliumpp.shared;
import heliumpp.terminalui.shared;
import heliumpp.terminalui.logger_panel;

using namespace std;
using namespace ftxui;

export namespace helium {
	class helium_tui_main_panel_class final : public helium_object_class, public ComponentBase {
	public:
		helium_tui_main_panel_class() = default;

		auto Render() -> Element final {
			return vbox({
					text("Hello Helium++ Terminal UI!"),
				});
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	auto start_helium_tui() {
		auto screen = ScreenInteractive::Fullscreen();
		auto main_container = Container::Vertical({
				Window("logs", helium_tui_log_panel),
			});
		auto main_renderer = Renderer(main_container, [&]() {
			return vbox({
				main_container->Render()
				});
			});
		return screen.Loop(main_renderer);
	}
}