
#include <lib/number.h>
#include <iostream>

int main() {
    char* value_1 = new char[2] {"1"};
    char* value_2 = new char[2] {"1"};
int2023_t value1 = from_string(value_1);
int2023_t value2 = from_string(value_2);
int2023_t sum = value1 + value2;
    std::cout << value1 << ' ' << value2 << ' ' << sum;
    return 0;
}
