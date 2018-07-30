//Тестовое задание "Вектор"  
//20.07.2018
//sdgsegre
//drhdrh
//dsfbrsb

#pragma once

#include "stdafx.h"


using namespace std;

template <typename TData>
class CArray
{
public: // Interface

		// Конструктор по умолчанию
	CArray();

	// Копирующий конструктор
	CArray(
		  const CArray & _array
	  );

	// Деструктор
	~CArray();

	// Добавить элемент в конец массива
	void push_back(
		  const TData & _value
	  );

	// Добавить элемент в массив по заданному индексу
	void insert(
		  unsigned int  _index,
		  const TData & _value
	  );

	// Удалить элемент массива по заданному индексу
	void erase(
		  unsigned int _index
	  );

	// Очистить массив
	void clear();

	// Получить размер массива
	unsigned int size() const;

  // Сортировать массив
	void sort();

  // Вывести массив на экран
	void out() const;

	// Получить элемент массива по заданному индексу
	TData & operator[](
		  unsigned int _index
		) const;

protected: // Attributes

	static unsigned int INITIAL_SIZE;
	TData* m_data;
	unsigned int m_size;
	unsigned int m_maxCapacity;

private:

  // Создать новый массив-член, скопировать данные с _array
	void loadArray(
		  const CArray &_array,
      int     _insertionPosition = -1
	  );

  // Сдвинуть элементы начиная с позиции _beginPosition на _shiftInterval позиций
	void rangeShift(
		  unsigned int _beginPosition,
		  int          _shiftInterval
	  );

};


// ====================================================================

// Начальный размер массива
template<typename TData>
unsigned int CArray<TData>::INITIAL_SIZE = 30;

// Конструктор по умолчанию
template<typename TData>
CArray<TData>::CArray()
  :
    m_size       (0),
    m_maxCapacity(INITIAL_SIZE),
    m_data       (new TData[INITIAL_SIZE])
{}


// Копирующий конструктор
template<typename TData>
CArray<TData>::CArray(
	  const CArray &_array
  ):
    m_data(new TData[0])
{
	loadArray(_array);
}


// Деструктор
template<typename TData>
CArray<TData>::~CArray()
{
	delete[] m_data;
}


// Добавить элемент в конец массива
template<typename TData>
void CArray<TData>::push_back(
	  const TData &_value
  )
{
  // Увеличить размер массива по необходимости:
	if (m_size >= m_maxCapacity)
	{
		loadArray(*this);
	}

  // Вставить элемент
	m_data[m_size] = _value;
	m_size++;
}


// Добавить элемент в массив по заданному индексу
template<typename TData>
void CArray<TData>::insert(
	  unsigned int  _index,
	  const TData & _value
  )
{
  // Увеличить размер массива по необходимости и сдвинуть после позиции _index
	if (m_size >= m_maxCapacity)
	{
		loadArray(*this, _index);
	}
  // Если помещаеться сдвинуть после позиции _index
  else
  {
    rangeShift(_index, 1);
  }

	// Вставить:
	m_data[_index] = _value;
}


// Удалить элемент массива по заданному индексу
template<typename TData>
void CArray<TData>::erase(
	  unsigned int _index
  )
{
	// Сдвигаем элементы после места стирания на 1 позицию влево:
	rangeShift(_index + 1, -1);
}


// Очистить массив
template<typename TData>
void CArray<TData>::clear()
{
	m_size = 0;
}


// Получить размер массива
template<typename TData>
unsigned int CArray<TData>::size() const
{
	return m_size;
}


// Сортировать массив
template<typename TData>
void CArray<TData>::sort()
{
	std::sort(m_data, m_data + size());
}


// Вывести массив на экран
template<typename TData>
void CArray<TData>::out() const
{
	cout << endl << "Элементы массива:\n  [";
	for (unsigned int i = 0; i < size(); ++i)
    cout << m_data[i] << (i < (size() - 1) ? ", ": "");
	cout << "]" << endl << endl;
}


// Получить элемент массива по заданному индексу
template<typename TData>
TData &CArray<TData>::operator[](
    unsigned int _index
  ) const
{
	if (_index >= size())
		cout << "Индекс выходит за границы массива";
	else
		return m_data[_index];
}


// Создать новый массив-член, скопировать данные с _array
template<typename TData>
void CArray<TData>::loadArray(
	  const CArray<TData> &_array,
    int            _insertionPosition
  )
{
  // Если есть вставка увеличить размер на 1
	m_size = _array.size() + (_insertionPosition == -1 ? 0 : 1);

	m_maxCapacity = max(
      INITIAL_SIZE, 
      size() * 2
    );

  // Если загружаемый массив и этот - тот же объект, скопировать данные в oldArray
  TData* oldArray;
  if (&_array != this)
    oldArray = _array.m_data;
  else
  {
    oldArray = new TData[_array.size()];
    copyArray(oldArray, _array.m_data, _array.size());
  }

  // Создать новый массив больше размером
  delete[] m_data;
  m_data = new TData[m_maxCapacity];

  if (_insertionPosition == -1)
    // Если нет вставки копируем в новый массив все данные
    copyArray(m_data, oldArray, size());
  else
  {
    // Если есть вставка копируем в новый массив данные до вставки и после вставки
    copyArray(m_data, oldArray, _insertionPosition);
    copyArray(m_data + _insertionPosition + 1, oldArray + _insertionPosition, (_array.size() - _insertionPosition));
  }

  // Удаляем временный массив
  if (&_array == this)
  {
    delete[] oldArray;
  }
}


// Сдвинуть элементы начиная с позиции _beginPosition на _shiftInterval позиций
template<typename TData>
void CArray<TData>::rangeShift(
	  unsigned int _beginPosition,
	  int          _shiftInterval
  )
{
	int rangeSize = m_size - _beginPosition; //размер интервала
  if (rangeSize > 0) // если элементов 0 ничего перемещать не нужно
  {
    TData* fromPtr = m_data + _beginPosition;
    TData* toPtr = fromPtr + _shiftInterval;
    copyArray(toPtr, fromPtr, rangeSize, (_shiftInterval > 0));
  }
  // Изменяем размер массива
  m_size += _shiftInterval;
}


// Копировать _elementsCount элементов с _arrayFrom в _arrayTo
// При _backOrder порядок обхода - с конца в начало
template<typename TData>
void copyArray(
    TData*       _arrayTo,
    TData*       _arrayFrom,
    unsigned int _elementsCount,
    bool         _backOrder = false
  )
{
  for (unsigned int i = 0; i < _elementsCount; i++)
  {
    unsigned int index = (_backOrder ? _elementsCount - i - 1 : i);// при _backOrder порядок обхода - с конца
    _arrayTo[index] = _arrayFrom[index];
  }
}