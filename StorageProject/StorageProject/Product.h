#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
struct Date {
	int day;
	int month;
	int year;

	Date() :day(-1), month(-1), year(-1) {};
	Date(int day,
		int month,
		int year) :day(day), month(month), year(year) {};
};

struct Place {
	unsigned section;
	unsigned shelf;
	unsigned number;

	Place() :section(-1), shelf(-1), number(-1) {};
	Place(unsigned section,
		unsigned shelf,
		unsigned number) :section(section), shelf(shelf), number(number) {};
};


class Product {
	char* name;
	Date expirationDate;
	Date data;
	char* nameOfProducer;
	int amount;
	Place place;
	char* comment;


	void copy(const Product& other);
	void clear();

public:
	Product();
	Product(const char* name, Date expirationDate, Date data, const char* nameOfProducer, int amount, Place place, const char* comment);
	Product(const Product& other);
	Product& operator=(const Product& other);
	~Product();

	void addProduct(const Product* storageCollection, int len, const char* fileName);
	
	void out();
	Product& maxObj(Product* products, const char* fileName);


	void print() const;
	void addProductToCollection(const char* name, Date expirationDate, Date data, const char* nameOfProducer, int amount, Place place, const char* comment, Product* collection, const char* fileName);
	void infoAboutProduct(char* searchedName, int searchedQuantity, Product* collection, const char* fileName);
	void reference(Date startDate, Date endDate);
	void cleaning(Date data, char* fileName);

	int countSameNameProducts = 0;
};
