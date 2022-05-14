#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include <cstring>
#include<fstream>
#include "Product.h"

class Storage  {
	Product* products;
	int countProducts;

	void copy(const Storage& other);
	void free();

public:

	Storage();
	Storage(Product* products, int countProducts);
	Storage(const Storage& other);
	Storage& operator=(const Storage& other);
	~Storage();

	void printStorage();
	void addProductToStorage(const char* name, Date expirationDate, Date data, const char* nameOfProducer, int amount, Place place, const char* comment, const char* fileName);
	void takeProductFromStorage(char* name, int quantity, const char* fileName);
	void cleaningStorage(Date date, char* fileName);
	void referenceStorage(Date startDate, Date endDate);
};
