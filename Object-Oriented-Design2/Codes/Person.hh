#ifndef __PERSON_HH__
#define __PERSON_HH__

#include <vector>
#include <string>

class Document;

class Person{
public:
    Person(string name);
    string get_name(){return name; }
    vector<Document*> get_duc(){return owned_duc; }
    void return_doc(int doc_name, int user_name);
    virtual void get_duc(Document* duc, int user_name) = 0;
protected:
    vector<Document*>owned_duc;
    string name;
    void check_doc_avalible(Document* duc);
    void check_doc_not_dublicated(Document* duc, int user_name);
};

#endif