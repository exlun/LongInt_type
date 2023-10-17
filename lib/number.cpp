#include "number.h"

char num[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void fill_up(int2023_t &val) {
    for (char &j: val.digit) {
        j = '0';
    }
}

int2023_t from_int(int32_t i) {
    int2023_t ans;
    fill_up(ans);
    if (i >= 0) {
        ans.digit[0] = '+';
    } else {
        ans.digit[0] = '-';
    }
    std::cout << '\n';
    int abs_i = abs(i);
    int count = 0;
    while (abs_i > 0) {
        ans.digit[252 - count] = num[abs_i % 10];
        abs_i /= 10;
        count++;
    }
    return ans;
}

int2023_t from_string(const char *buff) {
    int2023_t ans;
    int pos = 0;
    while (pos <= 253 && buff[pos] != NULL) {
        pos++;
    }
    pos--;
    int FML = 0;
    if (buff[0] == '-' || ans.digit[0] == '+') {
        FML = 1;
        ans.digit[0] = buff[0];
        pos++;
    } else {
        ans.digit[0] = '+';
        pos++;
    }
    for (int j = 1; j < 253; j++) {
        ans.digit[j] = '0';
    }
    for (int d = 1; d <= pos - FML; d++) {
        if (buff[pos - d] == '-') {
            ans.digit[253 - d] = '0';
        }
        ans.digit[253 - d] = buff[pos - d];
    }

    return ans;
}

char signs_comparison(const char &sign_left, const char &sign_right) {
    if (sign_left == sign_right) {
        if (sign_left == '-') {
            return '-';
        }
        if (sign_left == '+') {
            return '+';
        }
    }

    return 'd'; //d = different signs
}

//Finds the bigger number
char int_comparison(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 1; i < 253; i++) {
        if (lhs.digit[i] != rhs.digit[i]) {
            if (lhs.digit[i] > rhs.digit[i]) {
                return 'l';
            }
            else return 'r';
        }
    }

    return 'r';
}

int2023_t operator+(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t ans;
    fill_up(ans);
    bool carry_over = false;
    char sign_left = lhs.digit[0];
    char sign_right = rhs.digit[0];
    if (sign_left != '-') {
        sign_left = '+';
    }
    if (sign_right != '-') {
        sign_right = '+';
    }

    if (signs_comparison(sign_left, sign_right) != 'd') {
        ans.digit[0] = sign_left;
        for (int i = 252; i > 0; i--) {
            int digit_sum = abs((lhs.digit[i] - '0') + (rhs.digit[i] - '0'));
            if (carry_over) {
                digit_sum++;
                carry_over = false;
            }
            if (digit_sum > 9) {
                carry_over = true;
                digit_sum %= 10;
            }
            ans.digit[i] = (char) (digit_sum + '0');
        }
    } else {
        switch (int_comparison(lhs, rhs)) {
            case 'l':
                ans.digit[0] = sign_left;
                for (int i = 252; i > 0; i--) {
                    int digit_diff = (lhs.digit[i] - '0') - (rhs.digit[i] - '0');
                    if (carry_over) {
                        digit_diff--;
                        carry_over = false;
                    }
                    if (digit_diff < 0) {
                        carry_over = true;
                        digit_diff+=10;
                    }
                    ans.digit[i] = (char) (digit_diff + '0');
                }
                break;
            case 'r':
                ans.digit[0] = sign_right;
                for (int i = 252; i > 0; i--) {
                    int digit_diff = (rhs.digit[i] - '0') - (lhs.digit[i] - '0');
                    if (carry_over) {
                        digit_diff--;
                        carry_over = false;
                    }
                    if (digit_diff < 0) {
                        carry_over = true;
                        digit_diff+=10;
                    }
                    ans.digit[i] = (char) (digit_diff + '0');
                }
                break;
        }
    }

    return ans;
}

int2023_t operator-(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t ans;
    fill_up(ans);
    bool carry_over = false;
    char sign_left = lhs.digit[0];
    char sign_right = rhs.digit[0];
    if (sign_left != '-') {
        sign_left = '+';
    }
    if (sign_right != '-') {
        sign_right = '+';
    }

    if (signs_comparison(sign_left, sign_right) != 'd') {
        switch (int_comparison(lhs, rhs)) {
            case 'l':
                ans.digit[0] = sign_left;
                for (int i = 252; i > 0; i--) {
                    int digit_diff = (lhs.digit[i] - '0') - (rhs.digit[i] - '0');
                    if (carry_over) {
                        digit_diff--;
                        carry_over = false;
                    }
                    if (digit_diff < 0) {
                        carry_over = true;
                        digit_diff += 10;
                    }
                    ans.digit[i] = (char) (digit_diff + '0');
                }
                break;
            case 'r':
                ans.digit[0] = sign_left == '+' ? '-' : '+';
                for (int i = 252; i > 0; i--) {
                    int digit_diff = (rhs.digit[i] - '0') - (lhs.digit[i] - '0');
                    if (carry_over) {
                        digit_diff--;
                        carry_over = false;
                    }
                    if (digit_diff < 0) {
                        carry_over = true;
                        digit_diff += 10;
                    }
                    ans.digit[i] = (char) (digit_diff + '0');
                }
                break;
        }
    } else {
        ans.digit[0] = sign_left;
        for (int i = 252; i > 0; i--) {
            int digit_sum = (lhs.digit[i] - '0') + (rhs.digit[i] - '0');
            if (carry_over) {
                digit_sum++;
                carry_over = false;
            }
            if (digit_sum > 9) {
                carry_over = true;
                digit_sum %= 10;
            }
            ans.digit[i] = (char) (digit_sum + '0');
        }
    }

    //Check if after operation result is equal 0 and sign is equal to '-'.
    bool all_zeros = true;
    for (int temp = 1; temp < 253; temp++) {
        if (ans.digit[temp] != '0') {
            all_zeros = false;
        }
    }
    if (all_zeros) {
        ans.digit[0] = '+';
    }

    return ans;
}

// Function to find the local maximum index in a number
int find_pos(const int2023_t &nums) {
    int pos = 1;
    while (pos < 253) {
        if (nums.digit[pos] != '0') {
            break;
        }
        pos++;
    }
    return pos;
}

int2023_t operator*(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t ans;
    fill_up(ans);

    char sign_left = lhs.digit[0];
    char sign_right = rhs.digit[0];
    if (sign_left != '-') {
        sign_left = '+';
    }
    if (sign_right != '-') {
        sign_right = '+';
    }

    // Initialize nums array
    int2023_t nums[253];
    for (int i = 1; i < 253; ++i) {
        nums[i] = from_int(0);
    }

    // Find the biggest digit
    int lhs_start_pos = find_pos(lhs);
    int rhs_start_pos = find_pos(rhs);

    int over = 0;
    int cnt = 0;
    int rhs_num;
    int lhs_num;
    for (int i = 252; i >= rhs_start_pos; --i) {
        rhs_num = rhs.digit[i] - '0';
        for (int j = 252; j >= lhs_start_pos; --j) {
            lhs_num = lhs.digit[j] - '0';
            int temp = ((lhs_num * rhs_num) + over) % 10;
            over = ((lhs_num * rhs_num + over) / 10);
            nums[i].digit[j - cnt] = (char) (temp + '0');
        }
        if (over != 0) {
            if ((lhs_start_pos - 1 - cnt) <= 0) {

                break;
            }
            nums[i].digit[lhs_start_pos - 1 - cnt] = (char) (over + '0');
            over = 0;
        }
        cnt++;
    }
    // Sum up the intermediate results in nums array
    for (int i = 252; i >= rhs_start_pos; --i) {
        ans = ans + nums[i];
    }
    // Determine the sign of the result
    ans.digit[0] = (sign_left == sign_right) ? '+' : '-';

    return ans;
}



int2023_t operator/(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t ans;
    fill_up(ans);

    char sign_left = lhs.digit[0];
    char sign_right = rhs.digit[0];
    if (sign_left != '-') {
        sign_left = '+';
    }
    if (sign_right != '-') {
        sign_right = '+';
    }

    //Find the biggest digit
    int rhs_start_pos = find_pos(rhs);
    int lhs_start_pos = find_pos(lhs);

    //"Division by zero" and "Division of zero" cases
    if (lhs == from_int(0) || rhs == from_int(0)) {
        return rhs;
    }

    //"Divisor is bigger than dividend" case
    if ((rhs_start_pos <= lhs_start_pos) && (lhs.digit[lhs_start_pos] < rhs.digit[rhs_start_pos])) {
        ans = from_int(0);
        return ans;
    }

    int2023_t partial_quotient;
    fill_up(partial_quotient);
    int2023_t diff;
    fill_up(diff);

    int flag_rhs_digit = 0;
    if (rhs.digit[rhs_start_pos] > lhs.digit[lhs_start_pos]) {
        flag_rhs_digit = 1;
    }

    //Find the first partial quotient that is bigger than divisor
    for (int i = 0; i < (253 - rhs_start_pos) + flag_rhs_digit; i++) {
        partial_quotient.digit[rhs_start_pos + i - flag_rhs_digit] = lhs.digit[lhs_start_pos + i];
    }

    //Calculation of resulting array length
    int position = lhs_start_pos + 253 - rhs_start_pos + flag_rhs_digit;
    int result_length = 254 - position;
    char result[result_length];


    int2023_t remainder = partial_quotient;
    int2023_t temp;
    fill_up(temp);
    int2023_t multiplication;
    fill_up(multiplication);

    for (int i = 0; i < result_length; i++) {
        int res_raz = 0;
        temp = remainder - rhs;
        std::cout << temp.digit[0];
        if (temp.digit[0] != '-') {
            for (int j = 0; j < 253; j++) {
                temp.digit[j] = remainder.digit[j];
            }
            int j = 0;
            while (remainder.digit[0] == '+') {
                remainder = remainder - rhs;
                j++;
            }
            result[res_raz] = num[j - 1];
            res_raz++;

            int t = j - 1;
            multiplication = from_int(t);
            multiplication = rhs * multiplication;
            remainder = temp - multiplication;

            //Shift left for one position

            for (j = 2; j < 253; j++) {
                remainder.digit[j-1] = remainder.digit[j];
            }

            //While remainder is less than divisor - right position should be added (Position is shifted this way)
            remainder.digit[252] = lhs.digit[position];
            position++;

        } else {
            //If remainder is less than divisor even with shift - zero is result for current position; shift again
            result[res_raz] = '0';
            res_raz++;
            //сдвигаем остаток на один разряд влево
            for (int k = 2; k < 253; k++) {
                remainder.digit[k-1] = remainder.digit[k];
            }
            //While remainder is less than divisor - right position should be added (Position is shifted this way)
            remainder.digit[252] = lhs.digit[position];
            position++;
        }
    }

    for (int i = 0; i < result_length; i++) {
        ans.digit[254 - result_length + i - 1] = result[i];
    }
    if (signs_comparison(sign_left, sign_right) == 'd') {
        ans.digit[0] = '-';
    }

    return ans;
}


bool operator==(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 0; i < 253; i++) {
        if (lhs.digit[i] != rhs.digit[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 0; i < 253; i++) {
        if (lhs.digit[i] != rhs.digit[i]) {
            return true;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const int2023_t &value) {
    if (value == from_int(0)) {
        stream << '0';
        return stream;
    }
    stream << value.digit[0];
    bool leading_zero = true;
    for (int temp = 1; temp < 253; temp++) {
        if (value.digit[temp] != '0') {
            leading_zero = false;
        }
        if (!leading_zero && isdigit(value.digit[temp])) {
            stream << value.digit[temp];
        }
    }

    return stream;
}
