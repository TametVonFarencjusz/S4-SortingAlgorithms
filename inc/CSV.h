#include <string>
#include <fstream>
#include <iostream>
#include "../inc/List.h"

int loadCSV(List & S, std::string fileName = "dane.csv", int takeRecords = -1)
{
	std::fstream file;
	
	file.open(fileName, std::ios::in);
	//file.open("CSV.h", std::ios::in);
	
	std::string title;
	int rating;
	
	std::string line;
	int indexGoodRecords = 0;
	
	while (!file.eof() && takeRecords != indexGoodRecords)
	{
		try
		{
			std::getline(file,line);
			
			if (file.eof()) break;
			
			std::size_t index1 = line.find(",");			//szukanie pierwszego przecinka
			std::size_t index2 = line.find_last_of(",");	//szukanie ostatniego przecinka
			
			title = line.substr(index1+1,index2-index1-1);	//pobranie tytulu z linii
			
			if (index2 < line.length()-2) // sprawdzenie, czy po ostatnim przecinku jest wiecej niz jeden znak ("\n")
			{
				rating = std::stof(line.substr(index2+1, line.length()-index2)); 	//zamiania oceny na int
				Record r(title, rating);				//utworzenie obiketu record
				S.addLast(r);
				indexGoodRecords++;
			}
		}
		catch(std::invalid_argument){};
	} 
	
	file.close();
	
	return indexGoodRecords;
}
