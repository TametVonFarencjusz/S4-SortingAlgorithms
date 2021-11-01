#include <string>
#include <fstream>
#include <exception>

//***Dodatkowe wyjatki***//

//Wyjatek nieposortowanej listy
struct NotSortedListException : public std::exception{
	const char* what () const throw ()
	{
		return "List is not sorted";
	}
};

//***Dodatkowe funkcje dzialajace na Liscie***//

//Srednia wartosc elementow Listy
//Wejscie: Lista S
//Wyjscie: Wartosc srednia
float mean(const List & S)
{
	float a=0;
	ListElement * ptr = S.getFront();
	while(ptr != 0) //Sumowanie wszystkich wartosci
	{
		a+=ptr->getValue().rating;
		ptr = ptr->getNext();
	}
	return a/S.size();
}

//Sprawdzenie, czy Lista jest posortowana
//Wejscie: Lista S
//Wyjscie: true - Lista jest posortowana, false - Lista nie jest posortowana
bool isSorted(const List & S)
{
	if (S.isEmpty()) return true;

	int a = S.getFront()->getValue().rating;
	ListElement * ptr = S.getFront();	
	while(ptr != 0)
	{
		if (a > ptr->getValue()) return false;
		ptr = ptr->getNext();
	}
	return true;
}

//Mediana Listy
//Wejscie: Lista S
//Wyjscie: Wartosc srednia
float median(const List & S)
{
	if (!isSorted(S)) throw NotSortedListException();
	int size = S.size();
	ListElement * ptr = S[(int)size/2];
	return size%2==0?(ptr->getValue().rating+ptr->getPrev()->getValue().rating)*0.5f:ptr->getValue().rating;
}



//Wypisanie wartosci ocen Listy
//Wejscie: Lista S
//Wyjscie: Wypisanie wartosci elementow Listy w kolejnosci
void printRating(const List & S)
{
	for (int i = 0; i < S.size(); i++)
	{
		std::cout << S[i]->getValue().rating << " ";
	}
	std::cout << std::endl;
}

//Wypisanie wartosci ocen oraz filmow Listy
//Wejscie: Lista S
//Wyjscie: Wypisanie wartosci elementow Listy w kolejnosci
void printFull(const List & S)
{
	std::cout << std::endl;
	for (int i = 0; i < S.size(); i++)
	{
		std::cout << S[i]->getValue().title << ": " << S[i]->getValue().rating << std::endl;
	}
	std::cout << std::endl;
}

//Najwieksza wartosc w Liscie
//Wejscie: Lista S
//Wyjscie: Najwieksza wartosc w Liscie
int maxValue(const List & S)
{
	int max = -2147483648; //INT_MIN;
	ListElement * ptr = S.getFront();
	while(ptr != 0)
	{
		if(max < ptr->getValue().rating) max=ptr->getValue().rating;
		ptr = ptr->getNext();
	}
	return max;
}


//***Funkcje potrzebne do sortowania przez scalanie***//

//*Laczenie 2 List w jedna z porownywaniem najmniejszych wartosci*//
//Wejscie: 
//Listy S1,S2, z ktorych pobierane sa elementy
//Pusta Lista S, do ktorej dodawane sa posortowane elementy z List S1,S2
//Wyjscie: 
//Puste Listy S1,S2
//Posortowana lista S
void mergeCompare(List & S1, List & S2, List & S)
{
	while (!S1.isEmpty() && !S2.isEmpty()) //dodawanie najmniejszego elementu z list S1 i S2
	{
		if (S1.getFront()->getValue() < S2.getFront()->getValue()) S.addLast(S1.remove(0));
		else S.addLast(S2.remove(0));
	}
	while (!S1.isEmpty()) S.addLast(S1.remove(0)); //Dodawanie reszty elementow jesli Lista S2 jest pusta
	while (!S2.isEmpty()) S.addLast(S2.remove(0)); //Dodawanie reszty elementow jesli Lista S1 jest pusta
}

//*Dzielenie Listy na 2 mniejsze*//
//Wejscie: 
//Puste Listy S1,S2, do ktorej dodawane beda elementy z Listy S
//Lista S, z ktorej beda dzielone elementy do list S1,S2
//int split - ilosc elementow, ktore trafia do list S1
//Wyjscie: 
//Pusta Lista S
//Listy S1,S2 z elementami z Listy S
void split(List & S1, List & S2, List & S, int split)
{
	for(int i = 0; i < split; i++) S1.addLast(S.remove(0));
	while(!S.isEmpty()) S2.addLast(S.remove(0));
}

//***Sortowanie przez scalanie***//

//*Sortowanie przez scalanie*//
//Wejscie: Nieposortowana Lista S
//Wyjscie: Posortowana Lista S
void mergeSort(List & S)
{
	if (S.size() > 1)
	{
		int n = S.size();
		List S1, S2;
		split(S1, S2, S, (int)(n/2));
		mergeSort(S1);
		mergeSort(S2);
		mergeCompare(S1, S2, S);
	}
}

//***Funkcje potrzebne do sortowania przez scalanie***//
void merge(List & SLow, List & SSame, List & SHigh, List & S)
{
	while (!SLow.isEmpty()) S.addLast(SLow.remove(0));
	while (!SSame.isEmpty()) S.addLast(SSame.remove(0));;
	while (!SHigh.isEmpty()) S.addLast(SHigh.remove(0));
}

//***Sortowania szybkie***//

//*Sortowania szybkie*//
//Wejscie: Nieposortowana Lista S
//Wyjscie: Posortowana Lista S
void quickSort(List & S)
{
	if (S.size() <= 1) return;

	int pivot = S.getFront()->getValue().rating;
	List SLow, SSame, SHigh;
	while (!S.isEmpty())
	{
		if (pivot > S.getFront()->getValue())
		{
			SLow.addFirst(S.remove(0));
		}
		else if(pivot < S.getFront()->getValue())
		{
			SHigh.addFirst(S.remove(0));
		} 
		else
		{
			SSame.addFirst(S.remove(0));
		}
	}
	quickSort(SLow);
	quickSort(SHigh);
	
	merge(SLow, SSame, SHigh, S);
}

//***Sortowania kubelkowe***//

//*Sortowania kubelkowe*//
//Wejscie: Nieposortowana Lista S
//Wyjscie: Posortowana Lista S
void bucketSort(List & S, unsigned int maxValue)
{
	List * listArray;
	listArray = new List [maxValue+1];
	ListElement * ptr = S.getFront();
	while(!S.isEmpty())
	{
		ListElement * element = S.getFront();
		listArray[element->getValue().rating].addFirst(S.remove(element));
	}
	for (int i=0; i < maxValue+1; i++)
	{
		while(!(listArray[i].isEmpty())) S.addLast(listArray[i].remove(0));
	}
	
	delete []listArray;
}

