#pragma once
#include <memory>
#include <cstddef>
#include <cstring>
#include <gloomy/Utilities/Span.hpp>

namespace gloomy::util {
	template<typename T, typename D = std::default_delete<T[]>>
	struct DynamicArray {
		using deleter_type = D;
		using value_type = T;
		using pointer = value_type*;
		using data_pointer = std::unique_ptr<value_type[], deleter_type>;

	private:
		data_pointer _data;
		size_t _size;
		deleter_type _deleter;

	public:
		~DynamicArray() { this->_data = data_pointer(nullptr, this->_deleter); };
		DynamicArray(deleter_type deleter = deleter_type()) : _data(data_pointer(nullptr, deleter)), _size(0), _deleter(deleter) {};
		DynamicArray(size_t size, deleter_type deleter = deleter_type()) : _data(data_pointer(new value_type[size], deleter)), _size(size), _deleter(deleter) {};
		DynamicArray(data_pointer p, size_t size) : _data(std::move(p)), _size(size), _deleter(p.get_deleter()) {};
		DynamicArray(pointer p = nullptr, size_t size = 0, deleter_type deleter = deleter_type()) : _data(data_pointer(p, deleter)), _size(size), _deleter(deleter) {};
		DynamicArray(DynamicArray&& other) noexcept : _data(std::move(other._data)), _size(other._size), _deleter(other._deleter) {};
		DynamicArray& operator=(DynamicArray&& other) {
			this->_data = std::move(other._data);
			this->_size = other._size;
			this->_deleter = other._deleter;
			return *this;
		};

		inline size_t size() const;
		inline value_type* data();
		inline const value_type* data() const;

		inline value_type& operator[](size_t index);
		inline const value_type& operator[](size_t index) const;

		inline DynamicArray<T, D> clone() const;
		inline Span<T> span();
		inline const Span<T> span() const;
	};

	template<typename D = std::default_delete<std::byte[]>>
	using Bytes = DynamicArray<std::byte, D>;

	template<typename T, typename D>
	inline size_t DynamicArray<T, D>::size() const {
		return this->_size;
	};

	template<typename T, typename D>
	inline typename DynamicArray<T, D>::value_type* DynamicArray<T, D>::data() {
		return this->_data.get();
	};

	template<typename T, typename D>
	inline const typename DynamicArray<T, D>::value_type* DynamicArray<T, D>::data() const {
		return this->_data.get();
	};

	template<typename T, typename D>
	inline T& DynamicArray<T, D>::operator[](size_t index) {
		return this->data()[index];
	};

	template<typename T, typename D>
	inline const T& DynamicArray<T, D>::operator[](size_t index) const {
		return this->data()[index];
	};

	template<typename T, typename D>
	inline DynamicArray<T, D> DynamicArray<T, D>::clone() const {
		auto other = DynamicArray<T, D>(this->_size, this->_deleter);
		memcpy(other.data(), this->data(), this->_size * sizeof(T));

		return other;
	};

	template<typename T, typename D>
	inline Span<T> DynamicArray<T, D>::span(){
		return Span<T>(this->data(), this->_size);
	};

	template<typename T, typename D>
	inline const Span<T> DynamicArray<T, D>::span() const {
		return Span<T>(this->data(), this->_size);
	};
}