#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip> 
#include <utility>

template <class ValType>
class TTable
{	
private:
	std::string TableName;
	size_t Row, Coll;
	ValType* Values;
	std::pair<std::string, ValType*>* TableColumn;

public:

	TTable(std::string tablename, size_t row, size_t coll);
	~TTable();

	
	void SetValue(size_t row, size_t coll, ValType val);
	void SetNameColl(const std::string& name, size_t row);
	void Print();
	size_t GetRow() { return Row; }
	size_t GetColl() { return Coll; }
	
};





template<class ValType>
TTable<ValType>::TTable(std::string tablename, size_t row, size_t coll)
{
	TableName = std::move(tablename);
	Row = row;
	Coll = coll;

	TableColumn = new std::pair<std::string, ValType*>[coll];

	for (size_t i = 0; i < coll; i++) {
		(TableColumn[i]).second = new ValType[row];
	}
	
}

template<class ValType>
TTable<ValType>::~TTable()
{
	delete[] Values;
    delete[] TableColumn;
}


template<class ValType>
void TTable<ValType>::SetValue(size_t row, size_t coll, ValType val)
{
	(TableColumn[coll].second)[row] = val;
}

template<class ValType>
void TTable<ValType>::SetNameColl(const std::string& name, size_t coll)
{
	(TableColumn[coll].first) = name;
}

template<class ValType>
void TTable<ValType>::Print()
{
	std::cout << "         "  << (std::string)(TableName) << std::endl;
	for (size_t j = 0; j < Coll; j++) std::cout << std::setw(15) << TableColumn[j].first ;
	std::cout << std::endl;
	for (size_t i = 0; i < Row ; i++) {
		for (size_t j = 0; j < Coll; j++) {
			std::cout << std::setw(10)  << (TableColumn[j].second)[i] ;
		}
		std::cout << std::endl;
	}
}


