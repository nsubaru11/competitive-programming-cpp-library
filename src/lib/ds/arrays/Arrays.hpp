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
	int size, shiftCount;
	T* arr;

	[[nodiscard]] int toIndex(const int index) const { return ((index - shiftCount) % size + size) % size; }

public:
	explicit Arrays(int size = 1024, int shiftCount = 0, T arr[] = nullptr) {
		this->arr = arr == nullptr ? new T[size] : arr;
		this->size = size;
		this->shiftCount = shiftCount;
	}

	~Arrays() { delete[] arr; }

	T& operator[](int index) {
		if (index < 0 || index >= this->size) {
			throw out_of_range("ArrayIndexOutOfBoundsException: Index" + to_string(index) +
							   "out of bounds for length " + to_string(this->size));
		}
		return this->arr[toIndex(index)];
	}

	void rShift(int cnt = 1) {
		this->shiftCount += cnt;
		this->shiftCount %= this->size;
	}

	void lShift(int cnt = 1) {
		this->shiftCount -= cnt;
		this->shiftCount %= this->size;
	}

	void fill(T value) {
		for (int i = 0; i < this->size; i++) {
			this->arr[toIndex(i)] = value;
		}
	}

	template <typename Func>
		requires invocable<Func, int> && convertible_to<invoke_result_t<Func, int>, T>
	void setAll(Func function) {
		for (int i = 0; i < this->size; i++) {
			this->arr[toIndex(i)] = function(i);
		}
	}
};
