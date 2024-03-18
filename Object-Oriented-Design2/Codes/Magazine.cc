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