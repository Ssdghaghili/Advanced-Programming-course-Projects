#ifndef __BOOK_HH__
#define __BOOK_HH__

#include <vector>
#include <string>

class Document;

class Book : public Document{
public:
    Book(string name, int copy);
private:
};

#endif