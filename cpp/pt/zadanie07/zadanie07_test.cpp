
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

void map_test(const map<string, string> & translator, const string word) {
    try {
        translator.at(word);
    }
    catch (std::out_of_range const&) {
        cout << "error" << std::endl;
    }
}

void list_print(const list<int> & list) {
    for (int num : list) {
        cout << num << endl;
    }
}

int main() {
    map_test({{"fero", "1"}, {"duri", "2"}}, "adam");
    // list_print({1,2,3});
    return 0;
}
