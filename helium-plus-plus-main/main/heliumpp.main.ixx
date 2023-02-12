module;

#include <gsl/gsl>
#include <unordered_map>
#include <any>
#include <iostream>
#include <fmt/ostream.h>

export module heliumpp.main;

import heliumpp.shared;
import heliumpp.events;

using namespace gsl;
using namespace std;

export namespace helium
{
	auto listener(const string&, const unordered_map<string, any>&) {cout << "hey bro"; return 0;};
	auto helium_main(int argc, char* argv[]) -> int
	{
		
		helium_event_manager.append_listener("heybro"s, listener);
		helium_event_manager.dispatch_event("heybro"s, unordered_map<string, any>{});
		//cout << helium_event_manager.to_string() << endl;
		return 0;
	}
}

export auto main(int argc, char* argv[]) -> int
{
	return helium::helium_main(argc, argv);
}