#pragma once
#include <string_view>

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Objects/ID.hpp>
#include <gloomy/Utilities/NonCopyable.hpp>
#include <gloomy/Objects/Committable.hpp>

#include <cassert>

namespace gloomy {
	template<typename T>
	struct ObjectTrait {
		static inline auto generate() -> ID<T>;
		static inline auto release(const ID<T>& id) -> void;
	};

	struct AnyObject : public util::NonCopyable {
		virtual const RawID& get_raw_id() const = 0;
		virtual RawID& get_raw_id() = 0;

		virtual void generate() = 0;
		virtual void release() = 0;
	};

	template<typename T>
	struct Object : AnyObject {
		using Trait = ObjectTrait<T>;

		Object() = default;
		Object(ID<T>&& id) : id(std::move(id)) {};
		virtual ~Object();

		virtual const RawID& get_raw_id() const final;
		virtual RawID& get_raw_id() final;
		virtual inline const ID<T>& get_id() const final;
		virtual inline ID<T>& get_id() final;

		virtual inline void generate() final;
		virtual inline void release() final;

		using object_type = T;

	protected:
		ID<T> id = null_id<T>();
	};

	template<typename T>
	inline Object<T>::~Object() {}

	template<typename T>
	inline const RawID& Object<T>::get_raw_id() const {
		return this->id.get();
	}

	template<typename T>
	inline RawID& Object<T>::get_raw_id() {
		return this->id.get();
	}

	template<typename T>
	inline const ID<T>& Object<T>::get_id() const {
		return this->id;
	}

	template<typename T>
	inline ID<T>& Object<T>::get_id() {
		return this->id;
	}

	template<typename T>
	inline void Object<T>::generate() {
		this->release();

		this->get_id() = Object<T>::Trait::generate();
	}

	template<typename T>
	inline void Object<T>::release() {
		if (this->get_id().is_valid()) {
			Object<T>::Trait::release(this->get_id());
			this->id = gloomy::null_id<T>();
		}
	}

	template<typename T>
	inline ID<T> generate() {
		return Object<T>::Trait::generate();
	}

	template<typename T>
	inline void release(const ID<T>& id) {
		return Object<T>::Trait::release(id);
	}

	template<typename T>
	struct Owned final : T {
		virtual ~Owned() { static_cast<T*>(this)->release(); }
		Owned() = default;
		Owned(T&& t) : T(std::move(t)) {}
	};

	template<typename T, typename... Args>
	Owned<T> make(Args&&... args) {
		return Owned<T>(std::move(args)...);
	};

	template<typename T, typename I>
	Owned<T> make(std::initializer_list<I> args) {
		return Owned<T>(args);
	};


	template<typename T, typename... Args>
	Owned<T> make_generated(Args&&... args) {
		auto value = T(std::forward<Args>(args)...);
		value.generate();
		return Owned<T>(std::move(value));
	};

	template<typename T, typename I>
	Owned<T> make_generated(std::initializer_list<I> args) {
		auto value = T(args);
		value.generate();
		return Owned<T>(std::move(value));
	};

	template<typename T, typename... Args>
	Owned<T> make_ready(Args&&... args) {
		auto value = T(std::forward<Args>(args)...);
		value.generate();

		if constexpr (std::is_base_of_v<Committable<T>, T>) {
			if constexpr (std::is_base_of_v<Bindable<T>, T>) {
				if constexpr (Committable<T>::Trait::bind_before_commit) {
					value.bind();
					value.commit();
					value.unbind();
				}
				else value.commit();
			}
			else value.commit();
		}

		return Owned<T>(std::move(value));
	};

	template<typename T, typename I>
	Owned<T> make_ready(std::initializer_list<I> args) {
		auto value = T(args);

		value.generate();
		if constexpr (std::is_base_of_v<Committable<T>, T>) {
			if constexpr (std::is_base_of_v<Bindable<T>, T>) {
				if constexpr (Committable<T>::Trait::bind_before_commit) {
					value.bind();
					value.commit();
					value.unbind();
				}
				else value.commit();
			}
			else value.commit();
		}

		return Owned<T>(std::move(value));
	};
};
