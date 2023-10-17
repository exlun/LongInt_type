
#include <lib/number.h>
#include <iostream>

int main() {
    int2023_t value;
    int2023_t test;
    //char* value1 = new char[2] {"0"};
//    int32_t value1 = 32768;

    char* value1 = new char[2] {"1"};
//int value1 = 32768;
//int value2 = -32768;
    char* value2 = new char[2] {"1"};
//    value = from_int(value1);
value = from_string(value1);
//    value = from_int(value1);
    test = from_string(value2);
//    std::cout << value << ' ';
//    std::cout << test;
//    std::cout << "test output";
int2023_t sum = value - test;
    std::cout << value << test << sum;
    return 0;
}
