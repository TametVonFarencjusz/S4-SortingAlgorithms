#ifndef RECORD_H
#define RECORD_H

#include <string>

struct Record {
	std::string title;
	int rating;
	
	Record()
	{
		title = "";
		rating = 0;
	}
	
	Record(const std::string & m, int r)
	{
		title = m;
		rating = r;
	}
	
	Record & operator = (const Record & r) 
	{
		rating = r.rating;
		title = r.title;
		return *this;
	}
	
	bool operator == (const Record & r) {return rating == r.rating;}
	bool operator >  (const Record & r) {return rating >  r.rating;}
	bool operator <  (const Record & r) {return rating <  r.rating;}
	bool operator >= (const Record & r) {return rating >= r.rating;}
	bool operator <= (const Record & r) {return rating <= r.rating;}
	
	bool operator == (int a) {return rating == a;}
	bool operator >  (int a) {return rating >  a;}
	bool operator <  (int a) {return rating <  a;}
	bool operator >= (int a) {return rating >= a;}
	bool operator <= (int a) {return rating <= a;}
};

bool operator == (int a, const Record & r) {return a == r.rating;}
bool operator >  (int a, const Record & r) {return a >  r.rating;}
bool operator <  (int a, const Record & r) {return a <  r.rating;}
bool operator >= (int a, const Record & r) {return a >= r.rating;}
bool operator <= (int a, const Record & r) {return a <= r.rating;}

#endif

