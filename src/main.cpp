#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string>

#include "../inc/List.h"
#include "../inc/CSV.h"
#include "../inc/Sort.h"
#include "../inc/Record.h"


#include <thread>
#include <chrono>

int main()
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    
    Clock::time_point t0, t1;
    milliseconds ms;
	//const int count = 25; //Ilosc elementow wczytanych, wartosci mniejsze od 0 i wieksze od ilosci elementow w pliku wczytuja wszystkie elementy z pliku
	int elementCount;
	
	std::string tempString;
	std::cout << "Count of elements to load: ";
	std::cin >> tempString;
	int count = std::stoi(tempString);
	
	
	//Merge Sort
	{
		List SMS;
		t0 = Clock::now();
		elementCount = loadCSV(SMS, "dane.csv", count);
		t1 = Clock::now();
		ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::cout << "Loading time: "<< ms.count() << "ms\n" <<std::endl;

		t0 = Clock::now();
		mergeSort(SMS);
		t1 = Clock::now();
		//Info
		std::cout << "Element count: " << elementCount << std::endl;
		std::cout << "Sorted (Merge Sort): ";
		isSorted(SMS)?std::cout<<"Yes\n":std::cout<<"No\n";
		ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::cout << "Time: "<< ms.count() << "ms\n";
		std::cout << "Size: " << SMS.size() << std::endl;
		std::cout << "Mean: " << mean(SMS) << std::endl;
		std::cout << "Median: " << median(SMS) << std::endl;
		if (SMS.size() <= 25) printFull(SMS);
	}
	//Quick Sort
	{
		List SQS;
		elementCount = loadCSV(SQS, "dane.csv", count);
		t0 = Clock::now();
		quickSort(SQS);
		t1 = Clock::now();
		//Info
		std::cout << "Element count: " << elementCount << std::endl;
		std::cout << "Sorted (Quick Sort): ";
		isSorted(SQS)?std::cout<<"Yes\n":std::cout<<"No\n";
		ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::cout << "Time: "<< ms.count() << "ms\n";
		std::cout << "Size: " << SQS.size() << std::endl;
		std::cout << "Mean: " << mean(SQS) << std::endl;
		std::cout << "Median: " << median(SQS) << std::endl;
		if (SQS.size() <= 25) printFull(SQS);
	}
	//Bucket Sort
	{
		List SBS;
		elementCount = loadCSV(SBS, "dane.csv", count);
		t0 = Clock::now();
		bucketSort(SBS, maxValue(SBS));
		t1 = Clock::now();
		//Info
		std::cout << "Element count: " << elementCount << std::endl;
		std::cout << "Sorted (Bucket Sort): ";
		isSorted(SBS)?std::cout<<"Yes\n":std::cout<<"No\n";
		ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::cout << "Time: "<< ms.count() << "ms\n";
		std::cout << "Size: " << SBS.size() << std::endl;
		std::cout << "Mean: " << mean(SBS) << std::endl;
		std::cout << "Median: " << median(SBS) << std::endl;
		if (SBS.size() <= 25) printFull(SBS);
	}
	
}

