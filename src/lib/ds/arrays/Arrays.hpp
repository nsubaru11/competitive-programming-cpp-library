#pragma once

#include <concepts>
#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>

using namespace std;

template <typename T>
	requires totally_ordered<T>
class Arrays {
	int size, shift_count;
	T* arr;

	[[nodiscard]] int to_index(const int index) const { return ((index - shift_count) % size + size) % size; }

public:
	explicit Arrays(int size = 1024, int shift_count = 0, T arr[] = nullptr) {
		this->arr = arr == nullptr ? new T[size] : arr;
		this->size = size;
		this->shift_count = shift_count;
	}

	~Arrays() { delete[] arr; }

	T& operator[](int index) {
		if (index < 0 || index >= this->size) {
			throw out_of_range("ArrayIndexOutOfBoundsException: Index" + to_string(index) +
					"out of bounds for length " + to_string(this->size));
		}
		return this->arr[to_index(index)];
	}

	void rotate_right(int cnt = 1) {
		this->shift_count += cnt;
		this->shift_count %= this->size;
	}

	void rotate_left(int cnt = 1) {
		this->shift_count -= cnt;
		this->shift_count %= this->size;
	}

	void fill(T value) {
		for (int i = 0; i < this->size; i++) {
			this->arr[to_index(i)] = value;
		}
	}

	template <typename Func>
		requires invocable<Func, int> && convertible_to<invoke_result_t<Func, int>, T>
	void set_all(Func function) {
		for (int i = 0; i < this->size; i++) {
			this->arr[to_index(i)] = function(i);
		}
	}
};
