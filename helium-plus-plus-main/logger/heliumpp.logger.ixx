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

#define SPDLOG_HEADER_ONLY
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/async.h>

#include <string>
#include <memory>
#include <iostream>
#include <format>

export module heliumpp.logger;

import heliumpp.shared;
import heliumpp.terminalui.main;

using namespace std;
using namespace spdlog;

namespace helium
{
	auto get_file_sink()
	{
		static auto async_file
			= spdlog::create_async<sinks::daily_file_sink_mt>("heliumpp_logger", "logs/heliumpp-log.log", 23, 59);
		return async_file;
	}
}

export namespace helium
{
	enum class helium_log_level_enum
	{
		trace = SPDLOG_LEVEL_TRACE,
		debug = SPDLOG_LEVEL_DEBUG,
		info = SPDLOG_LEVEL_INFO,
		warn = SPDLOG_LEVEL_WARN,
		err = SPDLOG_LEVEL_ERROR,
		critical = SPDLOG_LEVEL_CRITICAL,
	};

	class helium_logger_class final : public helium_object_class
	{
	private:
		shared_ptr<logger> logger_ptr_;
		string logger_name_;
		string logger_thread_;

		template <typename ... Ts>
		auto __inner_log(spdlog::level::level_enum log_lvl, string_view fmt_str, Ts&& ... fmt_args) 
			const -> void
		{
			string out_str = format(
				"[{}/{}] {}",
				this->logger_name_,
				this->logger_thread_,
				vformat(
					fmt_str,
					make_format_args(forward<Ts>(fmt_args)...)
				)
			);
			this->logger_ptr_->log(log_lvl, out_str);
			helium_tui_main_panel->get_logger_panel()->add_log_info(static_cast<helium_tui_log_level_enum>(log_lvl), out_str);
		}
	public:
		explicit helium_logger_class(string_view logger_name, string_view logger_thread)
			: logger_ptr_(get_file_sink()), logger_name_(logger_name), logger_thread_(logger_thread)
		{
		}

		template <typename ... Ts>
		auto log(const helium_log_level_enum log_lvl, string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(static_cast<spdlog::level::level_enum>(to_underlying(log_lvl)), fmt_str, forward<Ts>(fmt_args)...);
		}
		template <typename ... Ts>
		auto trace(string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(spdlog::level::level_enum::trace, fmt_str, forward<Ts>(fmt_args)...);
		}
		template <typename ... Ts>
		auto debug(string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(spdlog::level::level_enum::debug, fmt_str, forward<Ts>(fmt_args)...);
		}
		template <typename ... Ts>
		auto info(string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(spdlog::level::level_enum::info, fmt_str, forward<Ts>(fmt_args)...);
		}
		template <typename ... Ts>
		auto warning(string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(spdlog::level::level_enum::warn, fmt_str, forward<Ts>(fmt_args)...);
		}
		template <typename ... Ts>
		auto error(string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(spdlog::level::level_enum::err, fmt_str, forward<Ts>(fmt_args)...);
		}
		template <typename ... Ts>
		auto critical(string_view fmt_str, Ts&& ... fmt_args)
			const -> void
		{
			this->__inner_log(spdlog::level::level_enum::critical, fmt_str, forward<Ts>(fmt_args)...);
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};
}
