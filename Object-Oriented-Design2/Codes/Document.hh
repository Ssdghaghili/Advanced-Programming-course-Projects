#ifndef __DOCUMENT_HH__
#define __DOCUMENT_HH__

#include <vector>
#include <string>

class Document;
class Person;

class Document{
public:
    Document(string book, int copy);
    string get_name(){return name; }
    int get_copy(){return copy; }
    void chenge_doc_copy(int new_copy);
protected:
    string name;
    int copy;
    int day_borrow;
    int return_day;
};

#endif