#ifndef __MAGAZINE_HH__
#define __MAGAZINE_HH__

#include <vector>
#include <string>

class Magazine : public Document{
public:
    Magazine(string magazine_title, int year, int number, int copies);
    int get_year(){return year; }
    int get_number(){return number; }
private:
    int year;
    int number;
};

#endif