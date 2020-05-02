#include <stdio.h>
#include <cs50.h>

string validateCC(long long);

string card_type(long long);

bool identify_mastercard(long long);

bool identify_amex(long long);

bool identify_visa(long long);

bool luhn_s_algorithm(long long);

int sum_of_each_second_digit_from_the_zeroeth(long long);

int sum_of_digits_of_doubles_of_each_second_digit_from_the_oneth(long long);

int sum_of_digits_of_doubled_single_digit_number(int);

int digit(long long, int);

long power(int, int);

int main(void)
{
    long long input_int = get_long_long("CC:");
    string final = validateCC(input_int);
    printf("%s", final);
}

string validateCC(long long integer)
{
    if (luhn_s_algorithm(integer))
    {
        return card_type(integer);
    }
    else
    {
        return "INVALID\n";
    }
}

string card_type(long long valid_card_number)
{
    if (identify_mastercard(valid_card_number))
    {
        return "MASTERCARD\n";
    }
    else if (identify_amex(valid_card_number))
    {
        return "AMEX\n";
    }
    else if (identify_visa(valid_card_number))
    {
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}

bool identify_mastercard(long long valid_card_number)
{
    //we are counting from zero, not one so this is the 16th digit
    int d15 = digit(valid_card_number, 15);
    int d14 = digit(valid_card_number, 14);
    //  MasterCard numbers start with 51, 52, 53, 54, or 55 - 16 digits
    return d15 == 5 && (d14 == 1 || d14 == 2 || d14 == 3 || d14 == 4 || d14 == 5);
}

bool identify_amex(long long valid_card_number)
{
    //we are counting from zero, not one so this is the 16th digit
    int d15 = digit(valid_card_number, 15);
    int d14 = digit(valid_card_number, 14);
    int d13 = digit(valid_card_number, 13);
    // All American Express numbers start with 34 or 37 - 15 digits
    return d15 == 0 && d14 == 3 && (d13 == 4 || d13 == 7);
}

bool identify_visa(long long valid_card_number)
{
    //we are counting from zero, not one so this is the 16th digit
    int d15 = digit(valid_card_number, 15);
    int d14 = digit(valid_card_number, 14);
    int d13 = digit(valid_card_number, 13);
    int d12 = digit(valid_card_number, 12);
    // and all Visa numbers start with 4 - 13 0r 16 digits
    return d15 == 4 || (d15 == 0 && d14 == 0 && d13 == 0 && d12 == 4);
}

// function leading_digit_validation(sixteen_digit_int, four_leading_digits) {
//   function compare_two_digits(n_sixteen, n_four) {
//     return (
//       digit(sixteen_digit_int, n_sixteen) == digit(four_leading_digits, n_four)
//     );
//   }
//   //fifteen because we are counting from 0, three for the same reason
//   return (
//     compare_two_digits(15, 3) &&
//     compare_two_digits(14, 2) &&
//     compare_two_digits(13, 1) &&
//     compare_two_digits(12, 0)
//   );
// }

bool luhn_s_algorithm(long long integer)
{
    int first_part = sum_of_digits_of_doubles_of_each_second_digit_from_the_oneth(integer);
    int second_part = sum_of_each_second_digit_from_the_zeroeth(integer);

    bool validation = (first_part + second_part) % 10 == 0;

    return validation;
}

int sum_of_each_second_digit_from_the_zeroeth(long long integer)
{
    //no cc is longer than 16 digits
    int MAX_CC_DIGITS = 16;
    int total = 0;
    int ith_digit;
    for (int i = 0; i < MAX_CC_DIGITS; i += 2)
    {
        ith_digit = digit(integer, i);
        total += ith_digit;
    }
    return total;
}

int sum_of_digits_of_doubles_of_each_second_digit_from_the_oneth(long long integer)
{
    //no cc is longer than 16 digits
    int MAX_CC_DIGITS = 16;
    int total = 0;
    int ith_digit;
    for (int i = 1; i < MAX_CC_DIGITS; i += 2)
    {
        ith_digit = digit(integer, i);
        total += sum_of_digits_of_doubled_single_digit_number(ith_digit);
        // console.log("total: ", total);
    }
    return total;
}

int sum_of_digits_of_doubled_single_digit_number(int single_digit_number)
{
    int doubled_single_digit_number = single_digit_number * 2;
    //no single digit integer multiplied by 2 can be higher than 18 so we only have two digits to consider
    // console.log("number :", doubled_single_digit_number);
    int d0 = digit(doubled_single_digit_number, 0);
    int d1 = digit(doubled_single_digit_number, 1);
    // console.log("do: ", d0, ";", " ", "d1: ", d1);
    return d0 + d1;
}

int digit(long long integer, int n)
{
    return (integer / power(10, n)) % 10;
}

long power(int base, int exponent)
{
    long result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result = result * base;
    }
    return result;
}