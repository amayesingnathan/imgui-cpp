export module imcpp.def;

import imcpp.std;

export namespace imcpp {

	template<typename TResult, typename... TArgs>
	using Func = std::function<TResult(TArgs...)>;

	template<typename... TArgs>
	using Action = Func<void, TArgs...>;

	template<typename... T>
	using Predicate = Func<bool, T...>;

	namespace fs = std::filesystem;

	template<typename T>
	struct Limits
	{
		static constexpr T Min = std::numeric_limits<T>::min();
		static constexpr T Max = std::numeric_limits<T>::max();
	};
}