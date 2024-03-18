#include <iostream>
#include <string>
using namespace std;
bool subSeq(string sub1 , string sub2 , string str);
bool subSeq1(string sub1 , string sub2 , string str);

int main() {
    string sub1,sub2,str;
    cin >> sub1 >> sub2 >> str;
    subSeq(sub1,sub2,str);
    bool returnValue = subSeq(sub1,sub2,str);
    bool returnValue1 = subSeq1(sub1,sub2,str);
    if (!returnValue && !returnValue1){
        cout << "Not Interleaving";
    }
    else {
        cout << "Interleaving";
    }
    return 0;
}

bool subSeq(string sub1 , string sub2 , string str){
    if (sub1.empty() && sub2.empty() && str.empty())
        return true;
    if (str.empty())
        return false;
    if (sub1[0] == sub2[0] == str[0]){
        subSeq1(sub1 , sub2.substr(1) , str.substr(1));
        return subSeq(sub1 , sub2.substr(1) , str.substr(1));
    }
    if (sub2[0] == str[0])
        return subSeq(sub1 , sub2.substr(1) , str.substr(1));
    if (sub1[0] == str[0])
        return subSeq(sub1.substr(1) , sub2 ,  str.substr(1));
    else
        return false;
}
bool subSeq1(string sub1 , string sub2 , string str){
    if (sub1.empty() && sub2.empty() && str.empty())
        return true;
    if (str.empty())
        return false;
    if (sub1[0] == sub2[0] == str[0]){
        subSeq(sub1 , sub2.substr(1) , str.substr(1));
        return subSeq1(sub1 , sub2.substr(1) , str.substr(1));
    }
    if (sub1[0] == str[0])
        return subSeq1(sub1.substr(1) , sub2 ,  str.substr(1));
    if (sub2[0] == str[0])
        return subSeq1(sub1 , sub2.substr(1) , str.substr(1));
    else
        return false;
}