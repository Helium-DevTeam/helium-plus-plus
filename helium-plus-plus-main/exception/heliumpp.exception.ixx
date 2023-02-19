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

#include <ctime>
#include <stacktrace>
#include <exception>
#include <iostream>

export module heliumpp.exception;

import heliumpp.logger;
import heliumpp.shared;

using namespace std;

export namespace helium
{
	[[noreturn]] auto helium_exception_handler() -> void
	{
		helium_logger_class log("heliumpp", "CRASH");
		const auto st = stacktrace::current();
		log.critical("STACKTRACE : ");
		for(auto& entry : st)
		{
			log.critical("{} in {} at line {}", entry.description(), entry.source_file(), entry.source_line());
		}
		exit(-1);
	}
	class helium_exception_handler_helper_class : public helium_object_class
	{
	public:
		helium_exception_handler_helper_class()
		{
			set_terminate(helium_exception_handler);
		}

		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	} helium_exception_handler_helper;
}
