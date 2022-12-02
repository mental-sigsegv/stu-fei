#include <algorithm>
#include <iostream>
#include <climits>

struct print_bits {
    int c=1;
    void operator()(char ch) {
        for (unsigned b = 1 << (CHAR_BIT - 1); b != 0; b >>= 1) {
            std::cout << (ch & b ? 1 : 0); 
            if (c%4==0) {
                std::cout << " ";
            }
            c++;
        }
        
    }
};

void print(const std::string &s) {
    std::for_each(s.begin(), s.end(), print_bits());
}

int main() {
    unsigned char uch = 128;
    print(uch);
}