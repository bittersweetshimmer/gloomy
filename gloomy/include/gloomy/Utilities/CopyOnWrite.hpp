#pragma once
#include <functional>
#include <variant>
#include <gloomy/Utilities/NonCopyable.hpp>

namespace gloomy::util {
	template<typename T>
	struct Cow : public NonCopyable{
	public:
		Cow(T&& value) : value(std::move(value)) {}
		Cow(const T& value) : value(std::ref(value)) {}
		Cow(Cow&& other) noexcept : value(std::move(other.value)) {};
		Cow& operator=(Cow&& other) {
			this->value = std::move(other.value);
		};

		inline T& get_mutable() {
			static_assert(std::is_copy_constructible_v<T>, "get_mutable() called on a potentially borrowed non-copyable value.");

			if (!this->is_owned()) {
				this->value = T(*std::get_if<borrow>(&this->value));
			}

			return *std::get_if<owned>(&this->value);
		}

		inline T& get_unsafe() {
			return const_cast<T&>(this->get());
		}

		inline const T& get() const {
			if (const borrow* borrow_ptr = std::get_if<borrow>(&this->value)) {
				return borrow_ptr->get();
			}
			else {
				const owned* owned_ptr = std::get_if<owned>(&this->value);

				return *owned_ptr;
			}
		}

		inline void set(T&& value) { this->value = std::move(value); }
		inline void set(const T& value) { this->value = std::ref(value); }
		inline bool is_owned() const { return nullptr != std::get_if<owned>(&this->value); }
	private:
		using owned = T;
		using borrow = std::reference_wrapper<const T>;
		
		std::variant<borrow, owned> value;
	};
}