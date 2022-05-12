#include <iostream>
#include "Storage.h"
#include "Product.h"


int main()
{
	

	

	Date first(1, 10, 2021);
	Date second(1, 4, 2022);

	Place place(3, 5, 8);

	Product B(" ", first, second, " ", 10, place, " ");
	Product C("Second", first, second, " ", 10, place, " ");
	B.print();
	//B.addProduct(" ", first, second, " ", 10, place, " ", 1, "myNewFile.txt");
}
