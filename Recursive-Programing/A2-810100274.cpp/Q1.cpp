#include <iostream>
#include <vector>
using namespace std;
const int ZERO = 0;
const int ONE = 1;

void GetInput(int n , int k , vector<int> number);
int replace(int n, int k ,vector<int> number);

int main() {
    vector<int> number={0};
    int k , n;
    GetInput(n , k , number);
    return 0;
}

void GetInput(int n , int k , vector<int> number){
    cin >> n >> k;
    replace(n, k , number);
}
int replace(int n, int k ,vector<int> number){
    vector <int> temp;
    for (int i = 0; i < number.size(); i++) {
        if (number.size() >= k) {
            cout << number[k - 1];
            exit(0);
        }
        if (number[i] == ZERO) {
            temp.push_back(0);
            temp.push_back(1);
        }
        if (number[i] == ONE) {
            temp.push_back(1);
            temp.push_back(0);
        }
        number = temp;
    }
    return replace(n, k, number);
}
