#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_key(int argc, string argv[]);
int arg_error();
string encrypt(int key, string text);
char cipher(int key, char c);

int main(int argc, string argv[])
{
    int key = get_key(argc, argv);
    if (key < 0)
    {
        return 1;
    }
    printf("%d\n", key);

    string text = get_string("plaintext:  ");
    string cypher = encrypt(key, text);
    printf("ciphertext: %s\n", cypher);
    return 0;
}

int get_key(int argc, string argv[])
{
    if (argc == 2)
    {
        string keystr = argv[1];
        long key = 0;
        for (int i = 0; i < strlen(keystr); i++)
        {
            if (!isdigit(keystr[i]))
            {
                return arg_error();
            }
        }
        key = atol(keystr);
        if (key < 0 || key > INT_MAX - 26)
        {
            return arg_error();
        }
        return key;
    }
    return arg_error();
}

int arg_error()
{
    printf("Usage: ./caesar key\n");
    return -1;
}

string encrypt(int key, string text)
{
    string ret = text;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        char c = text[i];
        ret[i] = cipher(key, c);
    }
    return ret;
}

char cipher(int key, char c)
{
    char x = c;
    if (isalpha(c))
    {
        if (islower(c))
        {
            x = ((c - 'a' + key) % 26) + 'a';
        }
        else
        {
            x = ((c - 'A' + key) % 26) + 'A';
        }
    }
    return x;
}
