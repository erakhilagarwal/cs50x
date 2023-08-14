#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

string get_message(void);
void encrypt_message(string text);
void to_binary(char c, int byte[]);
void print_bulb(int bit);

int main(void)
{
    string msg = get_message();
    encrypt_message(msg);
}

string get_message(void)
{
    return get_string("Message: ");
}

void encrypt_message(string text)
{
    long len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        int binary_sequence[BITS_IN_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};
        to_binary(text[i], binary_sequence);
        for (int bit = 0; bit < BITS_IN_BYTE; bit++)
        {
            print_bulb(binary_sequence[bit]);
        }
        printf("\n");
    }
}

void to_binary(char c, int byte[])
{
    int x = c;
    int idx = 7;
    while (x > 0 && idx >= 0)
    {
        byte[idx] = x % 2;
        x = x / 2;
        idx--;
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
