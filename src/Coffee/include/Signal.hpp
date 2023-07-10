#pragma 
#include <map>
#include <memory>
#include <functional>

namespace Coffee {

	template <typename FunctionSignature, typename DelegateType = std::function <FunctionSignature>>
	class Signal;

	template <typename DelegateType, typename ReturnType, typename... Args>
	class Signal<ReturnType(Args...), DelegateType> {
	public:

		int connect(const std::function<ReturnType(Args...)>& subscribedFunction) {
			auto handle = getHandle();
			_listOfSignals.insert({ handle, subscribedFunction });
			return handle;
		}

		void disconnect(const int& signalId) {
			_listOfSignals.erase(signalId);
		}

		void dispatch(Args... args) {
			for (auto& signal : _listOfSignals) {
				signal.second(args...);
			}
		}

	private:
		int getHandle() const {
			static int _handleIndex;
			return ++_handleIndex;
		}
		std::map<int, std::function<ReturnType(Args...)>> _listOfSignals;
	};
}
