#pragma once
#include <gloomy/Objects/ID.hpp>
#include <vector>
#include <functional>

namespace gloomy {
	template<typename T>
	struct BindableTrait {
		static inline auto bind(const T&) -> void;
		static inline auto unbind(const T&) -> void;
	};

	struct AnyBindable {
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};

	struct BindGroup {
		template<typename... Bs>
		BindGroup(const Bs&... bindables) : binds{std::ref(static_cast<const AnyBindable&>(bindables))...} {}
		std::vector<std::reference_wrapper<const gloomy::AnyBindable>> binds;
	};

	template<> struct BindableTrait<BindGroup> {
		static inline auto bind(const BindGroup& group) -> void {
			for (const auto& ref : group.binds) {
				ref.get().bind();
			}
		};
		static inline auto unbind(const BindGroup& group) -> void {
			for (const auto& ref : group.binds) {
				ref.get().unbind();
			}
		};
	};

	template<typename T>
	struct Bindable : public AnyBindable{
		virtual void bind() const final;
		virtual void unbind() const final;

		using Trait = BindableTrait<T>;
	};

	template<typename T>
	inline void Bindable<T>::bind() const {
		Bindable<T>::Trait::bind(*static_cast<const T*>(this));
	}

	template<typename T>
	inline void Bindable<T>::unbind() const {
		Bindable<T>::Trait::unbind(*static_cast<const T*>(this));
	}

	template<typename T, typename... Ts>
	inline void bind(const T& bindable, const Ts&... bindables) {
		if constexpr (std::is_base_of_v<AnyBindable, T>) { bindable.bind(); }
		else { BindableTrait<T>::bind(bindable); }

		if constexpr (sizeof...(Ts) != 0) { bind<Ts...>(bindables...); };
	}

	template<typename T, typename... Ts>
	inline void unbind(const T& bindable, const Ts&... bindables) {
		if constexpr (std::is_base_of_v<AnyBindable, T>) { bindable.unbind(); }
		else { BindableTrait<T>::unbind(bindable); }

		if constexpr (sizeof...(Ts) != 0) { unbind<Ts...>(bindables...); };
	}

	template<typename Fn, typename... Ts>
	inline void use(Fn callable, const Ts&... bindables) {
		gloomy::bind(bindables...);

		callable();

		gloomy::unbind(bindables...);
	}
}