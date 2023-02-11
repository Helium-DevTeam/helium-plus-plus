module;

#include <gsl/gsl>
#include <iostream>
#include <fmt/ostream.h>

export module heliumpp.main;

import heliumpp.shared;

using namespace gsl;
using namespace std;

export namespace helium
{

}

export int main()
{
	fmt::print("Hello World from Helium++ {}", helium::helium_version.to_string());
	return 0;
}