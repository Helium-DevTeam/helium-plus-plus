module;

#include <eventpp/eventdispatcher.h>

#include <string>
#include <type_traits>
#include <concepts>
#include <any>
#include <unordered_map>

export module heliumpp.event;

import heliumpp.shared;

using namespace std;
using namespace eventpp;

export namespace helium
{
	template<typename T>
	concept helium_hashable = integral<T> || helium_std_string<T>;

	template <typename T>
	concept helium_event_listener_prototype = is_function_v<T>;

	template <helium_hashable EventIdT, helium_event_listener_prototype EventListenerPrototypeT>
	class helium_event_manager_class
	{
	private:
		EventDispatcher<EventIdT, EventListenerPrototypeT> dispatcher_;

	public:
	};

	using helium_event_id_t = string;
	using helium_event_listener_prototype_t = int (const helium_event_id_t&, const unordered_map<string, any>&);

	helium_event_manager_class<helium_event_id_t, helium_event_listener_prototype_t> helium_event_manager;
}