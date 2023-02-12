module;

#include <eventpp/eventdispatcher.h>

#include <string>
#include <any>
#include <unordered_map>
#include <format>
#include <unifex/sender_concepts.hpp>
#include <unifex/scheduler_concepts.hpp>
#include <unifex/stop_when.hpp>

export module heliumpp.events;

import heliumpp.shared;

using namespace std;
using namespace eventpp;

export namespace helium
{
	class helium_event_manager_class : public helium_object_class
	{
	private:
		using event_id_t = string;
		using event_listener_prototype_t = int (const event_id_t&, const unordered_map<string, any>&);
		using event_dispatcher_t = EventDispatcher<event_id_t, event_listener_prototype_t>;
		using event_handle_t = event_dispatcher_t::Handle;

		event_dispatcher_t dispatcher_ = {};
	public:
		auto dispatch_event(const event_id_t& event_id, const unordered_map<string, any>& param) const
		{
			using namespace unifex;/*
			sender auto dispatch_lambda = [event_id, param, this]
			{
				this->dispatcher_.dispatch(event_id, event_id, param);
			};
			stop_when(dispatch_lambda, schedule_after(500ms));*/
		}
		auto append_listener(const event_id_t& event_id, event_listener_prototype_t& listener) -> event_handle_t
		{
			return this->dispatcher_.appendListener(event_id, listener);
		}
		auto prepend_listener(const event_id_t& event_id, event_listener_prototype_t& listener) -> event_handle_t
		{
			return this->dispatcher_.prependListener(event_id, listener);
		}
		auto insert_listener(const event_id_t& event_id, event_listener_prototype_t& listener, const event_handle_t before) -> event_handle_t
		{
			return this->dispatcher_.insertListener(event_id, listener, before);
		}
		auto remove_listener(const event_id_t& event_id, const event_handle_t handle) -> bool
		{
			return this->dispatcher_.removeListener(event_id, handle);
		}
		auto has_any_listener(const event_id_t& event_id) const -> bool
		{
			return this->dispatcher_.hasAnyListener(event_id);
		}
		auto to_string() const -> string override
		{
			return format("obj:helium_event_manager_class<{}>", this->uuid_string());
		}
	};

	using helium_event_id_t = string;
	using helium_event_listener_prototype_t = int (const helium_event_id_t&, const unordered_map<string, any>&);

	helium_event_manager_class helium_event_manager;
}