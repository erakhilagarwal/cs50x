#include <cs50.h>
#include <stdio.h>

// returns the sum of digits for a single digit positive number multiplies by 2
// input : 8 
// output: 7 (1 + 6)
int double_sum(int i)
{
    int x = i * 2;
    return (x / 10) + (x % 10);
}

// Checks the validity of card
string check_card(long number)
{
    int x = -1;
    int y = -1;
    int checksumeven = 0;
    int checksumodd = 0;
    int count = 0;
    bool even_digit = false;
    while (number > 0)
    {
        count++;
        y = x;
        x = number % 10;
        number = number / 10;
        if (even_digit)
        {
            checksumeven += double_sum(x);
        }
        else
        {
            checksumodd += x;
        }
        even_digit = !even_digit;
    }
  
    int mod = (checksumeven + checksumodd) % 10;
    if (mod != 0)
    {
        return "INVALID\n";
    }
  
    if (count == 15)
    {
        int lastNumber = (x * 10) + y;
        if (lastNumber == 37 || lastNumber == 34)
        {
            return "AMEX\n";
        }
    }
  
    if (count == 16)
    {
        int lastNumber = (x * 10) + y;
        if (lastNumber == 51 || lastNumber == 52 || lastNumber == 53 || lastNumber == 54 || lastNumber == 55)
        {
            return "MASTERCARD\n";
        }
    }
  
    if ((count == 13 || count == 16) && x == 4)
    {
        return "VISA\n";
    }
  
    return "INVALID\n";
}

int main(void)
{
    long number = -1;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    printf("%s", check_card(number));

    return 0;
}
