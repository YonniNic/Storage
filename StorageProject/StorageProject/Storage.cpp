#include<iostream>
#include "Product.h"
#include "Storage.h"

void Storage::printStorage() {
	for (int i = 0; i < countProducts; i++) {
		products[i].print();
	}
}

void Storage::addProductToStorage(const char* name, Date expirationDate, Date data, const char* nameOfProducer, int amount, Place place, const char* comment, const char* fileName) {
	for (int i = 0; i < countProducts+1; i++) {
		products[i].addProductToCollection(name, expirationDate, data, nameOfProducer, amount, place, comment, products, fileName);
	}
	countProducts += 1;
}

void Storage::takeProductFromStorage(char* name, int quantity, const char* fileName) {
	for (int i = 0; i < countProducts + 1; i++) {
		products[i].infoAboutProduct(name, quantity, products, fileName);
	}
}

void Storage::cleaningStorage(Date date, char* fileName) {
	for (int i = 0; i < countProducts; i++) {
		products[i].cleaning(date, fileName);
	}
}

void Storage::referenceStorage(Date startDate, Date endDate) {
	for (int i = 0; i < countProducts; i++) {
		products[i].reference(startDate, endDate);
	}
}