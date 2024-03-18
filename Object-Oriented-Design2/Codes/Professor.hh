#ifndef __PROFESSOR_HH__
#define __PROFESSOR_HH__

#include <vector>
#include <string>

class Document;
class Person;

class Professor : public Person {
public:
    Professor(string name);
    virtual void get_duc(Document* duc, int user_name);
private:
    void is_can_borrow_prof(Document *duc);
};

#endif