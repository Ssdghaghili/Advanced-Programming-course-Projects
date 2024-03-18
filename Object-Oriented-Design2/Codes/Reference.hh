#ifndef __REFERENCE_HH__
#define __REFERENCE_HH__

#include <vector>
#include <string>

class Document;
class Person;

class Reference : public Document{
public:
    Reference(string name, int copy);
private:
};

#endif