#pragma once

#pragma once
#include "../preprocessor/Common.h"
#include "Signal.hpp"
#include <string>
#include "SystemEvents.hpp"

namespace Coffee {
	class Event_ {
	private:

		class Registry_ {
		public:
			template <typename FunctionSignature>
			static auto& fetch(const SystemEvents identifier)
			{
				static std::map <SystemEvents, Signal <FunctionSignature>> registry;
				auto i(registry.begin());
				i = registry.find(identifier);
				if (i != registry.end())
				{
					return i->second;
				}
				registry[identifier] = Signal <FunctionSignature>();
				return registry[identifier];
			}
		};

	public:

		template <typename FunctionSignature>
		int subscribe(const SystemEvents eventName, const std::function<FunctionSignature>& function) {
			auto& signal(Registry_::template fetch <FunctionSignature>(eventName));
			return signal.connect(function);
		}

		template <typename FunctionSignature>
		void unsubscribe(const SystemEvents eventName, const int& handle) {
			auto& signal(Registry_::template fetch <FunctionSignature>(eventName));
			signal.disconnect(handle);
		}

		template <typename FunctionSignature, typename... Args>
		void dispatch(const SystemEvents eventName, Args... args) const
		{
			auto& signal(Registry_::template fetch <FunctionSignature>(eventName));
			signal.dispatch(args...);
		}

	private:
		COFFEE_MAKE_SINGLETON(Event_);
	};
}

#define Event Event_::getInstance()
