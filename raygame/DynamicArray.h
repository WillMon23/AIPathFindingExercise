#pragma once
#include <exception>

template<typename T>
class DynamicArray {
public:
	DynamicArray();
	DynamicArray(const DynamicArray<T>& other);
	~DynamicArray();
	void addItem(T item);
	void addItem(T item[], int size);
	void insert(T item, int index);
	bool remove(T item);
	bool remove(int index);
	void sortItems();
	T getItem(int index) const;
	int getLength() const;

	void clear();

	/// <summary>
	/// Checks if the item is in the array
	/// </summary>
	/// <param name="item">A reference to the item to use to check</param>
	/// <returns>False if the item is not in the array</returns>
	bool contains(T item);

	T& operator [](int index);
	const DynamicArray<T>& operator = (const DynamicArray<T>& other);
private:
	T* m_items = nullptr;
	int m_count = 0;
};

template<typename T>
inline DynamicArray<T>::DynamicArray() {
	m_count = 0;
	m_items = nullptr;
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
	*this = other;
}

template<typename T>
inline DynamicArray<T>::~DynamicArray() {
	if (m_count <= 0) return;
	delete[] m_items;
	m_count = 0;
	m_items = nullptr;
}

template<typename T>
inline void DynamicArray<T>::addItem(T item) {
	T* tempArray = new T[getLength() + 1];
	for (int i = 0; i < getLength(); i++) {
		tempArray[i] = m_items[i];
	}

	delete[] m_items;
	tempArray[getLength()] = item;
	m_items = tempArray;
	m_count++;
}

template<typename T>
inline void DynamicArray<T>::addItem(T item[], int size) {
	T* tempArray = new T[getLength() + size];

	int j = 0;
	for (int i = 0; i < getLength(); i++) {
		tempArray[j] = m_items[i];
		j++;
	}
	for (int i = 0; i < size; i++) {
		tempArray[j] = item[i];
		j++;
	}

	m_count += size;
	delete[] m_items;
	m_items = tempArray;
}

template<typename T>
inline void DynamicArray<T>::insert(T item, int index)
{
	T* tempArray = new T[getLength() + 1];
	int j = 0;
	for (int i = 0; i < getLength() + 1; i++) {
		if (i != index) {
			tempArray[i] = m_items[j];
			j++;
		}
	}

	delete[] m_items;
	tempArray[index] = item;
	m_items = tempArray;
	m_count++;
}

template<typename T>
inline bool DynamicArray<T>::remove(T item) {
	bool itemRemoved = false;

	if (getLength() <= 0)
		return itemRemoved;

	T* tempArray = new T[getLength() - 1];

	int j = 0;
	for (int i = 0; i < getLength(); i++) {
		if (item != m_items[i] || itemRemoved) {
			tempArray[j] = m_items[i];
			j++;
		}
		else {
			itemRemoved = true;
		}
	}

	if (itemRemoved) {
		delete[] m_items;
		m_items = tempArray;
		m_count--;
	}

	return itemRemoved;
}

template<typename T>
inline bool DynamicArray<T>::remove(int index)
{
	bool itemRemoved = false;

	if (getLength() <= 0 || index < 0 || index >= getLength() || !m_items)
		return itemRemoved;

	T* tempArray = new T[getLength() - 1];

	int j = 0;
	for (int i = 0; i < getLength(); i++) {
		if (index != i || itemRemoved) {
			tempArray[j] = m_items[i];
			j++;
		}
		else {
			itemRemoved = true;
		}
	}

	if (itemRemoved) {
		delete[] m_items;
		m_items = tempArray;
		m_count--;
	}

	return itemRemoved;
}

template<typename T>
inline void DynamicArray<T>::sortItems() {
	T key = T();
	int j = 0;

	for (int i = 1; i < getLength(); i++) {
		key = m_items[i];
		j = i - 1;
		while (j >= 0 && m_items[j] > key) {
			m_items[j + 1] = m_items[j];
			j--;
		}

		m_items[j + 1] = key;
	}
}

template<typename T>
inline T DynamicArray<T>::getItem(int index) const {
	if (index > 0 || index < getLength()) {
		return m_items[index];
	}
	return T();
}

template<typename T>
inline int DynamicArray<T>::getLength() const {
	return m_count;
}

template<typename T>
inline void DynamicArray<T>::clear()
{
	for (int i = 0; i < getLength(); i++)
	{
		remove(i);
	}

	m_count = 0;
	m_items = nullptr;
}

template<typename T>
inline bool DynamicArray<T>::contains(T value)
{
	//Iterate through item array
	for (int i = 0; i < m_count; i++)
	{
		//return the current item if it matches the argument
		if (m_items[i] == value)
			return true;
	}

	return false;
}

template<typename T>
inline T& DynamicArray<T>::operator[](int index)
{
	if (index > 0 || index < getLength()) {
		return m_items[index];
	}

	throw std::exception("Index was outside the bounds of the array.");
}

template<typename T>
inline const DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	if (getLength() > 0)
		clear();

	for (int i = 0; i < other.m_count; i++)
		addItem(other.getItem(i));

	return *this;
}
