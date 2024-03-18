Document::Document(string _name, int _copy){
    if(_name=="")
        throw runtime_error("empty field\n");
    else if (copy<=0)
        throw runtime_error("This document does not exist\n");
    name =_name;
    copy = _copy;
}

void Document::chenge_doc_copy(int new_copy){
    copy = new_copy;
}