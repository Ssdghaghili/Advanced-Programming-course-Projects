#include<iostream>

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
