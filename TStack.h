#pragma once
#include <cassert>
#include <iostream>

template <class ValType>
class TStack
{
private:
	ValType* Data;
	size_t Num;
	size_t TopIndex;

public:
	explicit TStack(size_t num = 10) {
		assert(num != 0);
		Data = new ValType[num];
		Num = num;
		TopIndex = -1;
	}
	TStack(const TStack& st) {
		Num = st.Num;
		TopIndex = st.TopIndex;
		Data = new ValType[Num];
		for (size_t i = 0; i < TopIndex + 1; i++) {
			Data[i] = st.Data[i];
		}
	}
	TStack& operator=(const TStack& st) {
		if (this == &st)
			return *this;
		Num = st.Num;
		TopIndex = st.TopIndex;
		delete[] Data;
		Data = new ValType[Num];
		for (size_t i = 0; i < TopIndex + 1; i++) {
			Data[i] = st.Data[i];
		}
	}

	size_t GetNum() {
		return Num;
	}

	bool IsEmpty() { return TopIndex == -1; }
	bool IsFull() { return TopIndex + 1 == Num; }

	void Push(ValType elem) {
		if (IsFull()) {
			ValType* tmp = Data;
			Data = new ValType[Num + 10];
			for (size_t i = 0; i < Num; i++)
				Data[i] = tmp[i];
			Num += 10;
			delete[] tmp;
		}
		TopIndex++;
		Data[TopIndex] = elem;
	}

	ValType Pop() {
		assert(!IsEmpty());
		ValType popElem = Data[TopIndex];
		TopIndex--;
		return popElem;
	}

	ValType Top() {
		assert(!IsEmpty());
		return Data[TopIndex];
	}

	void Print() {
		std::cout << "Stack: ";
		if (IsEmpty()) {
			std::cout << "is empty!" << std::endl;
			return;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < TopIndex + 1; i++) {
			std::cout << Data[i] << std::endl;
		}
	}

	~TStack() {
		delete[] Data;
	}

};

