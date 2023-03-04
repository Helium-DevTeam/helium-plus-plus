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

#include <spdlog/common.h>

#include <fmt/format.h>

#include <format>
#include <memory>
#include <chrono>

export module heliumpp.terminalui.logger_panel;

import heliumpp.shared;
import heliumpp.terminalui.shared;

using namespace std;
using namespace std::chrono;
using namespace ftxui;

export namespace helium {
	enum class helium_tui_log_level_enum
	{
		trace = SPDLOG_LEVEL_TRACE,
		debug = SPDLOG_LEVEL_DEBUG,
		info = SPDLOG_LEVEL_INFO,
		warn = SPDLOG_LEVEL_WARN,
		err = SPDLOG_LEVEL_ERROR,
		critical = SPDLOG_LEVEL_CRITICAL,
	};

	class helium_tui_log_panel_class final : public helium_object_class, public ComponentBase {
	private:
		Elements logs_;
		Component log_container_;
		Component scroller_container_;
	public:
		helium_tui_log_panel_class() :
			logs_({ 
				vbox({}) 
			}),
			log_container_(Container::Vertical({
				Renderer([&]() { return vbox({this->logs_}); })
			})),
			scroller_container_(Scroller(this->log_container_)) {}

		auto Render() -> Element final {
			return this->scroller_container_->Render();
		}

		auto add_log_info(helium_tui_log_level_enum log_lvl, string log_str) {
			string lvl_str = "info"s;
			ftxui::Color lvl_color = ftxui::Color::Green;
			if (log_lvl == helium_tui_log_level_enum::trace) {
				lvl_str = "trace"s;
				lvl_color = ftxui::Color::GrayLight;
			}
			if (log_lvl == helium_tui_log_level_enum::debug) {
				lvl_str = "debug"s;
				lvl_color = ftxui::Color::BlueLight;
			}
			if (log_lvl == helium_tui_log_level_enum::info) {
				lvl_str = "info"s;
				lvl_color = ftxui::Color::Green;
			}
			if (log_lvl == helium_tui_log_level_enum::warn) {
				lvl_str = "warn"s;
				lvl_color = ftxui::Color::YellowLight;
			}
			if (log_lvl == helium_tui_log_level_enum::err) {
				lvl_str = "error"s;
				lvl_color = ftxui::Color::RedLight;
			}
			if (log_lvl == helium_tui_log_level_enum::critical) {
				lvl_str = "critical"s;
				lvl_color = ftxui::Color::Red;
			}
			auto now = chrono::system_clock::now();
			this->logs_.push_back(
				hbox({
					ftxui::text(format("[{:%F} {:%T}] [", now, now)),
					ftxui::text(lvl_str) | color(lvl_color),
					ftxui::paragraph(format("] {}", log_str)) | xflex,
				}) | xflex
			);
			while (this->logs_.size() > 65535) {
				this->logs_.erase(this->logs_.begin());
			}
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};

	shared_ptr<helium_tui_log_panel_class> helium_tui_log_panel = Make<helium_tui_log_panel_class>();
}