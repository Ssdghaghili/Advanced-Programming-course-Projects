#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

const int MAX_CAPACITY_FOR_BORROW_STU = 2;
const int MAX_CAPACITY_FOR_BORROW_PROF = 5;
const int ZERO = 0;
const int ONE = 1;

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

class Student : public Person {
public:
    Student(string name, string id);
    string get_id(){return id; }
    virtual void get_duc(Document* duc, int user_name);
private:
    string id;
    void is_can_borrow_stu(Document* duc);
};

class Professor : public Person {
public:
    Professor(string name);
    virtual void get_duc(Document* duc, int user_name);
private:
    void is_can_borrow_prof(Document *duc);
};

class Book : public Document{
public:
    Book(string name, int copy);
private:
};

class Magazine : public Document{
public:
    Magazine(string magazine_title, int year, int number, int copies);
    int get_year(){return year; }
    int get_number(){return number; }
private:
    int year;
    int number;
};

class Reference : public Document{
public:
    Reference(string name, int copy);
private:
};
class Library {
public:
    void add_student_member(string student_id, string student_name);
    void add_prof_member(string prof_name);
    void add_book(string book_title, int copies);
    void add_magazine(string magazine_title, int year, int number, int copies);
    void add_reference(string reference_title, int copies);
    void borrow(string member_name, string document_title);
    void extend(string member_name, string document_title);
    void return_document(string member_name, string document_title);
    int get_total_penalty(string member_name);
    vector<string> available_titles();
    int time_pass(int days);
    int find_duc(string document_title);
    int find_user(string user_name);
    void borrow_document(vector<Document>document,int today);
    void check_document(string doc_name);
    void check_user(string user_name);
private:
    vector<Person*>users;
    vector<Document*>document;
    int today;
};

Person::Person(string _name){
    if(_name=="")
        throw runtime_error("empty field\n");
    name =_name;
}
Student::Student(string name, string _id)
        : Person(name)
{
    if(_id=="")
        throw runtime_error("empty field\n");
}
Professor::Professor(string name)
          : Person(name){}
Document::Document(string _name, int _copy){
    if(_name=="")
        throw runtime_error("empty field\n");
    else if (copy<=0)
        throw runtime_error("This document does not exist\n");
    name =_name;
    copy = _copy;
}
Book::Book(string name, int copy)
     : Document(name ,copy){}
Magazine::Magazine(string magazine_title, int _year, int _number, int copies)
         : Document(magazine_title, copies)
{
    if(_year<=0)
        throw runtime_error("Invalid year\n");
    else if (_number<=0)
        throw runtime_error("Invalid number\n");
    year = _year;
    number = _number;
}
Reference::Reference(string name, int copy)
          :Document(name, copy){}
void Document::chenge_doc_copy(int new_copy){
    copy = new_copy;
}
void Person::check_doc_avalible(Document* duc){
    int correct_copy = duc->get_copy();
    int new_copies;
    if (duc->get_copy() == ZERO)
        throw runtime_error("This document does not exist\n");
    else{
        new_copies = correct_copy - ONE;
        duc->chenge_doc_copy(new_copies);
    }
}
void Person::check_doc_not_dublicated(Document *duc, int user_name){
    for (int i=0; i < owned_duc.size() ;i++) {
        if (users[user_name]->get_duc() == duc->get_name())
            throw runtime_error("You borrowed this document already\n");
    else
        continue;
    }
}
void Student::is_can_borrow_stu(Document *duc){
    if (owned_duc.size() > MAX_CAPACITY_FOR_BORROW_STU)
        throw runtime_error("Maximum number of allowed borrows exceeded\n");
}
void Professor::is_can_borrow_prof(Document *duc){
    if (owned_duc.size() > MAX_CAPACITY_FOR_BORROW_PROF)
        throw runtime_error("Maximum number of allowed borrows exceeded\n");
}
void Student::get_duc(Document* duc, int user_name){
    check_doc_avalible(duc);
    check_doc_not_dublicated(duc, user_name);
    is_can_borrow_stu(duc);
    owned_duc.push_back(duc);
}
int Library::find_duc(string document_title){
    for (int i = 0; i < document.size(); i++) {
        if (document[i]->get_name() == document_title)
            return i;
    }
        throw runtime_error("ducument does not exist\n");
}
int Library::find_user(string user_name){
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->get_name() == user_name)
            return i;
    }
    throw runtime_error("user does not exist\n");
}
void Library::check_document(string duc_name){
    for (int i = 0; i < document.size(); i++) {
        if (document[i]->get_name() == duc_name){
            throw runtime_error("A document with the specified name already exists\n");
        }
    }
}
void Library::check_user(string user_name){
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->get_name() == user_name){
            throw runtime_error("Name already exists\n");
        }
    }
}
void Library::add_student_member(string student_id, string student_name){
    try{
        Student *new_std = new Student(student_id,student_name);
        check_user(new_std->get_name());
        users.push_back(new_std);
    }
    catch(runtime_error &ex){
        cout<<ex.what()<<endl;
        exit(EXIT_SUCCESS);
    }
}

void Library::add_prof_member(string prof_name){
    try{
        Professor *new_prof = new Professor(prof_name);
        check_user(new_prof->get_name());
        users.push_back(new_prof);
    }
    catch(runtime_error &ex){
        cout<<ex.what()<<endl;
        exit(EXIT_SUCCESS);
    }
}
void Library::add_book(string book_title, int copies){
    try{
        Book *new_Book = new Book(book_title, copies);
        check_document(new_Book->get_name());
        document.push_back(new_Book);
    }
    catch(runtime_error &ex){
        cout<<ex.what()<<endl;
        exit(EXIT_SUCCESS);
    }
}
void Library::add_magazine(string magazine_title, int year, int number, int copies){
    try{
        Magazine *new_mag = new Magazine(magazine_title, year, number, copies);
        check_document(new_mag->get_name());
        document.push_back(new_mag);
    }
    catch(runtime_error &ex){
            cout<<ex.what()<<endl;
            exit(EXIT_SUCCESS);
    }
}
void Library::add_reference(string reference_title, int copies){
    try{
        Reference *new_ref = new Reference(reference_title, copies);
        check_document(new_ref->get_name());
        document.push_back(new_ref);
    }
    catch(runtime_error &ex){
            cout<<ex.what()<<endl;
            exit(EXIT_SUCCESS);
    }
}
void Library::borrow(string member_name, string document_title){
    try{
    int duc_name = find_duc(document_title);
    int user_name = find_user(member_name);
    users[user_name]->get_duc(document[duc_name], user_name);
    }
    catch(runtime_error &ex){
        cout<<ex.what()<<endl;
        exit(EXIT_SUCCESS);
    }
}
void Person::return_doc(int doc_name, int user_name){
    for (int i=0; i < owned_duc.size() ;i++) {
        if (users[user_name]->get_duc(i) == document_title){
            owned_duc[i].erese;
        }
    }
}
void Library::return_document(string member_name, string document_title){
    try{
        int doc_name = find_duc(document_title);
        int user_name = find_user(member_name);
        return_doc(doc_name, user_name);
    }
    catch(runtime_error &ex){
        cout<<ex.what()<<endl;
        exit(EXIT_SUCCESS);
    }
}
vector<string>Library:: available_titles(){
    for (int i=0; i<document.size(); i++) {
        if (document[i]->get_copy() > 0) {
            cout << document[i]->get_name();
        }
    }
}
void Library::extend(string member_name, string document_title){
    
}
