#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include "Product.h"

const int MAX_VALID_YEAR = 2022;
const int MIN_VALID_YEAR = 2000;

void Product::print() const {
	std::cout << name << " " << expirationDate.day << " " << expirationDate.month << " " << expirationDate.year
		<< " " << data.day << " " << data.month << " " << data.year << " " << nameOfProducer << " " << amount << " " <<
		place.number << " " << place.section << " " << place.shelf << " " << comment<<" "<<countSameNameProducts;
}


void Product::addProduct(const Product* storageCollection, int len, const char* fileName) {
	std::ofstream outFile(fileName);

	if (!outFile.is_open())
		return;

	for (int i = 0; i < len; i++) {
		outFile << storageCollection[i].name << " " << storageCollection[i].expirationDate.day << " " << storageCollection[i].expirationDate.month << " " << storageCollection[i].expirationDate.year
			<< " " << storageCollection[i].data.day << " " << storageCollection[i].data.month << " " << storageCollection[i].data.year << " " << storageCollection[i].nameOfProducer << " " << storageCollection[i].amount << " " <<
			storageCollection[i].place.number << " " << storageCollection[i].place.section << " " << storageCollection[i].place.shelf << " " << storageCollection[i].comment;

	}

	outFile.close();
}

Product::Product() :name(nullptr), expirationDate(-1, -1, -1), data(-1, -1, -1),
nameOfProducer(nullptr), amount(-1), place(-1, -1, -1), comment(nullptr) {};

Product::Product(const char* name,
	Date expirationDate,
	Date data,
	const char* nameOfProducer,
	int amount,
	Place place,
	const char* comment)
	:name(new char[strlen(name) + 1]),
	expirationDate(expirationDate),
	data(data),
	nameOfProducer(new char[strlen(nameOfProducer) + 1]),
	amount(amount),
	place(place),
	comment(new char[strlen(comment) + 1])
{
	strcpy_s(this->name, strlen(name) + 1, name);
	strcpy_s(this->nameOfProducer, strlen(nameOfProducer) + 1, nameOfProducer);
	strcpy_s(this->comment, strlen(comment) + 1, comment);
}

Product::~Product() {
	clear();
}

Product::Product(const Product& other) {
	copy(other);
}

Product& Product::operator=(const Product& other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

void Product::clear() {
	delete[] name;
	name = nullptr;

	delete[] nameOfProducer;
	nameOfProducer = nullptr;

	delete[] comment;
	comment = nullptr;
}

void Product::copy(const Product& other) {
	expirationDate = other.expirationDate;
	data = other.data;
	amount = other.amount;
	place = other.place;
	strcpy(name, other.name);
	strcpy(nameOfProducer, other.nameOfProducer);
	strcpy(comment, other.comment);
}

int countLines(const char* fileName)
{
	std::ifstream f(fileName);
	if (!f.is_open())
		return -1;

	int linesCount = 0;

	while (!f.eof())
	{
		char buff[1024];
		f.getline(buff, 1024);
		linesCount++;
	}
	f.close();

	return linesCount;

}

bool checkDate(Date date) {
	bool isLeap = (((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0));

	if (date.year > MAX_VALID_YEAR || date.year < MIN_VALID_YEAR)
		return false;
	if (date.month < 1 || date.month > 12)
		return false;
	if (date.day < 1 || date.day > 31)
		return false;

	if (date.month == 2) {
		if (isLeap)
			return (date.day <= 29);
		else
			return (date.day <= 28);
	}
	if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
		return (date.day <= 30);
	}

	return true;
}

bool isSymbol(char a) {
	return a >= 'a' && a <= 'Z';
}

bool validName(const char* name) {
	int length = strlen(name);

	for (int i = 0; i < length; i++) {
		if (!isSymbol(name[i]))
			return false;
	}
	return true;
}

void Product::addProductToCollection(const char* name, Date expirationDate, Date data, const char* nameOfProducer, int amount, Place place, const char* comment, Product* collection, const char* fileName) {
	int productsCount = countLines(fileName);

	productsCount++;
	
	for (int i = 0; i < productsCount + 1; i++) {
		if (checkDate(expirationDate) && (checkDate(data)) && validName(name) && validName(nameOfProducer)) {
			if (strcmp(name, collection[i].name) == 0 && (expirationDate.day == collection[i].expirationDate.day || expirationDate.month == collection[i].expirationDate.month || expirationDate.year == collection[i].expirationDate.year)) {

				for (int j = productsCount; j > i; j--) {
					collection[j] = collection[j - 1];
				}
				collection[productsCount] = Product(name, expirationDate, data, nameOfProducer, amount, place, comment);
			}
			else {
					collection[productsCount] = Product(name, expirationDate, data, nameOfProducer, amount, place, comment);
			}
			}
		else
			std::cout << "Invalid input" << std::endl;

	if (strcmp(name, collection[i].name) != 0)
		countSameNameProducts++;
}
	
}

Product& Product:: maxObj(Product* products, const char* fileName) {
	int countProducts = countLines(fileName);
	for (int i = 0; i < countProducts; i++)
	{
		for (int j = i + 1; j < countProducts+1; j++)
		{
			if (products[i].expirationDate.year > products[j].expirationDate.year)
			{
				struct Product temp = products[i];
				products[i] = products[j];
				products[j] = temp;
			}
			else if (products[i].expirationDate.year == products[j].expirationDate.year && products[i].expirationDate.month > products[j].expirationDate.month)
			{
				struct Product temp = products[i];
				products[i] = products[j];
				products[j] = temp;
			}
			else if (products[i].expirationDate.year == products[j].expirationDate.year && products[i].expirationDate.month == products[j].expirationDate.month && products[i].expirationDate.day > products[j].expirationDate.day)
			{
				struct Product temp = products[i];
				products[i] = products[j];
				products[j] = temp;
			}

		}
	}
	return products[countProducts-1];
}

void Product::out() {
	delete[] name;
	name = nullptr;

	delete[] nameOfProducer;
	nameOfProducer = nullptr;

	delete[] comment;
	comment = nullptr;

	expirationDate.day = 0;
	expirationDate.month = 0;
	expirationDate.year = 0;
	data.day = 0;
	data.month = 0;
	data.year = 0;
	amount = 0;
	place.number = 0;
	place.section = 0;
	place.shelf = 0;
}

void Product::infoAboutProduct(char* searchedName, int searchedAmount, Product* collection, const char* fileName) {
	int productsCount = countLines(fileName);
	for (int i = 0; i < productsCount; i++) {
		if (strcmp(searchedName, collection[i].name) == 0 && searchedAmount == collection[i].amount) {
			collection[i].print();
			collection[i].out();
			
		}
		if (strcmp(searchedName, collection[i].name) == 0 && (expirationDate.day != collection[i].expirationDate.day || expirationDate.month != collection[i].expirationDate.month || expirationDate.year != collection[i].expirationDate.year)) {
			maxObj(collection, fileName).out();
			
		}

		if (strcmp(searchedName, collection[i].name) == 0) {
			if (searchedAmount > collection[i].amount) {
				std::cout << "You are asking for too big amount"<<collection[i].amount<<std::endl;
				std::cout << collection[i].expirationDate.year<<"-"<< collection[i].expirationDate.month << "-" << collection[i].expirationDate.day<<std::endl;
				std::cout << "You can take that amount: " << collection[i].amount;
				collection[i].out();
			}
		}
	}
	productsCount--;
}


void Product::reference(Date startDate, Date endDate) {
	
}

char* formatDate(Date date) {
	char* newName = new char[50];
	char buff[12];
	newName = strcat(newName, "cleanup-");
	newName = strcat(newName, _itoa(date.year, buff, 4));
	newName = strcat(newName, "-");
	newName = strcat(newName, _itoa(date.month, buff, 4));
	newName = strcat(newName, "-");
	newName = strcat(newName, _itoa(date.day, buff, 4));
	newName = strcat(newName, ".txt");

	return newName;
}

void Product::cleaning(Date date, char* fileName) {
	int productsCount = countLines(fileName);
	std::ofstream outFile(formatDate(date));
	if (expirationDate.year > date.year
		|| expirationDate.year == date.year && expirationDate.month >= date.month
		|| expirationDate.year == date.year && expirationDate.month == date.month && expirationDate.day>=date.day
		) {
		outFile << name << " " << expirationDate.day << " " << expirationDate.month << " " << expirationDate.year
			<< " " << data.day << " " << data.month << " " << data.year << " " << nameOfProducer << " " << amount << " " <<
			place.number << " " << place.section << " " << place.shelf << " " << comment;

		out();
		productsCount--;
	}
}