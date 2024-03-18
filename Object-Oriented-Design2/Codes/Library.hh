#ifndef __LIBRARY_HH__
#define __LIBRARY_HH__

#include <vector>
#include <string>

class Person;
class Document;

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

#endif