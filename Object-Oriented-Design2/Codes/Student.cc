Student::Student(string name, string _id)
        : Person(name)
{
    if(_id=="")
        throw runtime_error("empty field\n");
}
void Student::is_can_borrow_stu(Document *duc){
    if (owned_duc.size() > MAX_CAPACITY_FOR_BORROW_STU)
        throw runtime_error("Maximum number of allowed borrows exceeded\n");
}
void Student::get_duc(Document* duc, int user_name){
    check_doc_avalible(duc);
    check_doc_not_dublicated(duc, user_name);
    is_can_borrow_stu(duc);
    owned_duc.push_back(duc);
}