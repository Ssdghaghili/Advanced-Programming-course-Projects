#ifndef __STUDENT_HH__
#define __STUDENT_HH__

#include <vector>
#include <string>

class Document;
class Person;

class Student : public Person {
public:
    Student(string name, string id);
    string get_id(){return id; }
    virtual void get_duc(Document* duc, int user_name);
private:
    string id;
    void is_can_borrow_stu(Document* duc);
};

#endif