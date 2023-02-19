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

//#include <boost/process.hpp>

#include <string>
#include <memory>
#include <format>

export module heliumpp.server.process_starter;

import heliumpp.shared;

//namespace bp = boost::process;
using namespace std;

export namespace helium
{
	class helium_process_starter_class final : public helium_object_class
	{
	private:
		string startup_command_line_ = {};
		//shared_ptr<bp::child> child_process_;
		//bp::opstream in_stream_;
		//bp::ipstream out_stream_;
	public:
		explicit helium_process_starter_class(string_view command_line)
			:
			startup_command_line_(command_line)
		{
			//this->child_process_ = make_shared<bp::child>(static_cast<string>(command_line), bp::std_out > this->out_stream_, bp::std_in < this->in_stream_);
		}
		auto to_string() const -> string override
		{
			return get_object_type_string(this);
		}
	};
}