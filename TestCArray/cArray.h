//�������� ������� "������"  
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

		// ����������� �� ���������
	CArray();

	// ���������� �����������
	CArray(
		  const CArray & _array
	  );

	// ����������
	~CArray();

	// �������� ������� � ����� �������
	void push_back(
		  const TData & _value
	  );

	// �������� ������� � ������ �� ��������� �������
	void insert(
		  unsigned int  _index,
		  const TData & _value
	  );

	// ������� ������� ������� �� ��������� �������
	void erase(
		  unsigned int _index
	  );

	// �������� ������
	void clear();

	// �������� ������ �������
	unsigned int size() const;

  // ����������� ������
	void sort();

  // ������� ������ �� �����
	void out() const;

	// �������� ������� ������� �� ��������� �������
	TData & operator[](
		  unsigned int _index
		) const;

protected: // Attributes

	static unsigned int INITIAL_SIZE;
	TData* m_data;
	unsigned int m_size;
	unsigned int m_maxCapacity;

private:

  // ������� ����� ������-����, ����������� ������ � _array
	void loadArray(
		  const CArray &_array,
      int     _insertionPosition = -1
	  );

  // �������� �������� ������� � ������� _beginPosition �� _shiftInterval �������
	void rangeShift(
		  unsigned int _beginPosition,
		  int          _shiftInterval
	  );

};


// ====================================================================

// ��������� ������ �������
template<typename TData>
unsigned int CArray<TData>::INITIAL_SIZE = 30;

// ����������� �� ���������
template<typename TData>
CArray<TData>::CArray()
  :
    m_size       (0),
    m_maxCapacity(INITIAL_SIZE),
    m_data       (new TData[INITIAL_SIZE])
{}


// ���������� �����������
template<typename TData>
CArray<TData>::CArray(
	  const CArray &_array
  ):
    m_data(new TData[0])
{
	loadArray(_array);
}


// ����������
template<typename TData>
CArray<TData>::~CArray()
{
	delete[] m_data;
}


// �������� ������� � ����� �������
template<typename TData>
void CArray<TData>::push_back(
	  const TData &_value
  )
{
  // ��������� ������ ������� �� �������������:
	if (m_size >= m_maxCapacity)
	{
		loadArray(*this);
	}

  // �������� �������
	m_data[m_size] = _value;
	m_size++;
}


// �������� ������� � ������ �� ��������� �������
template<typename TData>
void CArray<TData>::insert(
	  unsigned int  _index,
	  const TData & _value
  )
{
  // ��������� ������ ������� �� ������������� � �������� ����� ������� _index
	if (m_size >= m_maxCapacity)
	{
		loadArray(*this, _index);
	}
  // ���� ����������� �������� ����� ������� _index
  else
  {
    rangeShift(_index, 1);
  }

	// ��������:
	m_data[_index] = _value;
}


// ������� ������� ������� �� ��������� �������
template<typename TData>
void CArray<TData>::erase(
	  unsigned int _index
  )
{
	// �������� �������� ����� ����� �������� �� 1 ������� �����:
	rangeShift(_index + 1, -1);
}


// �������� ������
template<typename TData>
void CArray<TData>::clear()
{
	m_size = 0;
}


// �������� ������ �������
template<typename TData>
unsigned int CArray<TData>::size() const
{
	return m_size;
}


// ����������� ������
template<typename TData>
void CArray<TData>::sort()
{
	std::sort(m_data, m_data + size());
}


// ������� ������ �� �����
template<typename TData>
void CArray<TData>::out() const
{
	cout << endl << "�������� �������:\n  [";
	for (unsigned int i = 0; i < size(); ++i)
    cout << m_data[i] << (i < (size() - 1) ? ", ": "");
	cout << "]" << endl << endl;
}


// �������� ������� ������� �� ��������� �������
template<typename TData>
TData &CArray<TData>::operator[](
    unsigned int _index
  ) const
{
	if (_index >= size())
		cout << "������ ������� �� ������� �������";
	else
		return m_data[_index];
}


// ������� ����� ������-����, ����������� ������ � _array
template<typename TData>
void CArray<TData>::loadArray(
	  const CArray<TData> &_array,
    int            _insertionPosition
  )
{
  // ���� ���� ������� ��������� ������ �� 1
	m_size = _array.size() + (_insertionPosition == -1 ? 0 : 1);

	m_maxCapacity = max(
      INITIAL_SIZE, 
      size() * 2
    );

  // ���� ����������� ������ � ���� - ��� �� ������, ����������� ������ � oldArray
  TData* oldArray;
  if (&_array != this)
    oldArray = _array.m_data;
  else
  {
    oldArray = new TData[_array.size()];
    copyArray(oldArray, _array.m_data, _array.size());
  }

  // ������� ����� ������ ������ ��������
  delete[] m_data;
  m_data = new TData[m_maxCapacity];

  if (_insertionPosition == -1)
    // ���� ��� ������� �������� � ����� ������ ��� ������
    copyArray(m_data, oldArray, size());
  else
  {
    // ���� ���� ������� �������� � ����� ������ ������ �� ������� � ����� �������
    copyArray(m_data, oldArray, _insertionPosition);
    copyArray(m_data + _insertionPosition + 1, oldArray + _insertionPosition, (_array.size() - _insertionPosition));
  }

  // ������� ��������� ������
  if (&_array == this)
  {
    delete[] oldArray;
  }
}


// �������� �������� ������� � ������� _beginPosition �� _shiftInterval �������
template<typename TData>
void CArray<TData>::rangeShift(
	  unsigned int _beginPosition,
	  int          _shiftInterval
  )
{
	int rangeSize = m_size - _beginPosition; //������ ���������
  if (rangeSize > 0) // ���� ��������� 0 ������ ���������� �� �����
  {
    TData* fromPtr = m_data + _beginPosition;
    TData* toPtr = fromPtr + _shiftInterval;
    copyArray(toPtr, fromPtr, rangeSize, (_shiftInterval > 0));
  }
  // �������� ������ �������
  m_size += _shiftInterval;
}


// ���������� _elementsCount ��������� � _arrayFrom � _arrayTo
// ��� _backOrder ������� ������ - � ����� � ������
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
    unsigned int index = (_backOrder ? _elementsCount - i - 1 : i);// ��� _backOrder ������� ������ - � �����
    _arrayTo[index] = _arrayFrom[index];
  }
}