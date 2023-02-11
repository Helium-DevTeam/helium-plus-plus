module;

#include <neargye/semver.hpp>

export module heliumpp.shared;

using namespace semver;

export namespace helium
{
	constexpr version helium_version{0, 0, 1, prerelease::alpha};
}