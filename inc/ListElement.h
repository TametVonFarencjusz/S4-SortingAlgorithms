#include <iostream>
#include "Record.h"

class ListElement {
private:
	Record value;		//Wartosc przechowywana w elemencie kolejki
	ListElement * next;	//Wskaznik na kolejny element kolejki
	ListElement * prev;
public:
	//Konstruktor 
	ListElement(Record a, ListElement * ptr = 0, ListElement * ptr2 = 0)
	{
		value = a;
		next = ptr;
		prev = ptr2;
	}
		
	//Destruktor
	~ListElement()
	{
		//delete next;
	}

	//Metoda zwracajaca wartosc przechowywana w elemencie
	Record getValue() const
	{
		return value;
	}
	
	//Metoda zwracajaca wartosc wskaznik na kolejny element kolejki
	ListElement * getNext() const
	{
		return next;
	}
	
	//Metoda zwracajaca wartosc wskaznik na kolejny element kolejki
	ListElement * getPrev() const
	{
		return prev;
	}
	
	//Metoda zmieniajaca wartosc wskaznika na kolejny element kolejki
	void setNext(ListElement * ptr)
	{
		next = ptr;
	}
	
	//Metoda zmieniajaca wartosc wskaznika na kolejny element kolejki
	void setPrev(ListElement * ptr)
	{
		prev = ptr;
	}
	
	//Metoda zmieniajaca wartosc elementu
	void setValue(Record a)
	{
		value = a;
	}
};


