module;

#include <gsl/gsl>
#include <iostream>
#include <fmt/ostream.h>

export module heliumpp.main;

import heliumpp.shared;
import heliumpp.event;

using namespace gsl;
using namespace std;

export namespace helium
{
	auto helium_main(int argc, char* argv[]) -> int
	{
		return 0;
	}
}

export auto main(int argc, char* argv[]) -> int
{
	return helium::helium_main(argc, argv);
}