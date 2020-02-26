#pragma once
#include <gloomy/Objects/ID.hpp>
#include <gloomy/Objects/Bindable.hpp>

namespace gloomy {
	template<typename T>
	struct CommittableTrait {
		static inline auto commit(const T&) -> void;

		static constexpr bool bind_before_commit = true;
	};

	struct AnyCommittable {
		virtual void commit() const = 0;
	};

	template<typename T>
	struct Committable {
		virtual void commit() const final;

		using Trait = CommittableTrait<T>;
	};

	template<typename T>
	inline void Committable<T>::commit() const {
		Committable<T>::Trait::commit(*static_cast<const T*>(this));
	}

	template<typename T, typename... Ts>
	inline void commit(const T& committable, const Ts&... committables) {
		committable.commit();

		if constexpr (sizeof...(Ts) != 0) { commit<Ts...>(committables...); };
	}

	template<typename Fn, typename... Ts>
	inline void staged(Fn callable, const Ts&... stageable) {
		gloomy::bind(stageable...);

		callable();

		gloomy::commit(stageable...);
		gloomy::unbind(stageable...);
	}
}