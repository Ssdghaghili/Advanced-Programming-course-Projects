Person::Person(string _name){
    if(_name=="")
        throw runtime_error("empty field\n");
    name =_name;
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

void Person::return_doc(int doc_name, int user_name){
    for (int i=0; i < owned_duc.size() ;i++) {
        if (users[user_name]->get_duc(i) == document_title){
            owned_duc[i].erese;
        }
    }
}