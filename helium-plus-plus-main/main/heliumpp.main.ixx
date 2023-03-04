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

#include <gsl/gsl>
#include <unordered_map>
#include <any>
#include <thread>
#include <iostream>

export module heliumpp.main;

import heliumpp.config;
import heliumpp.shared;
import heliumpp.server;
import heliumpp.events;
import heliumpp.logger;
import heliumpp.terminalui;

using namespace gsl;
using namespace std;

namespace helium
{
	helium_logger_class log("heliumpp", "main");
}

export namespace helium
{
	auto helium_main(int argc, char* argv[]) -> int
	{
		thread tui_thread = thread([]() {return start_helium_tui(); });
		int i = 100;
		while (i > 0) {
			log.debug("test{}", i);
			--i;
		}
		tui_thread.join();
		return 0;
	}
}

export auto main(int argc, char* argv[]) -> int
{
	return helium::helium_main(argc, argv);
}