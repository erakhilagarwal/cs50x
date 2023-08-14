#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int CHAR_COUNT = 26;

string get_key(int argc, string argv[]);
string report_error();
bool validate_key(string str);
string encrypt(const string key, string text);

int main(int argc, string argv[])
{
    string key = get_key(argc, argv);
    if (strlen(key) != CHAR_COUNT)
    {
        return 1;
    }
    string text = get_string("plaintext:  ");
    string encrypted_text = encrypt(key, text);
    printf("ciphertext: %s\n", encrypted_text);
}

string get_key(int argc, string argv[])
{
    if (argc != 2)
    {
        return report_error();
    }
    string keystr = argv[1];
    if (!validate_key(keystr))
    {
        return report_error();
    }
    return keystr;
}

string report_error()
{
    printf("Usage: ./substitution key\n");
    return "";
}

bool validate_key(string str)
{
    bool mapping[CHAR_COUNT];
    for (int i = 0; i < CHAR_COUNT; i++)
    {
        mapping[i] = false;
    }
    int len = strlen(str);
    if (len != CHAR_COUNT)
    {
        return false;
    }

    for (int i = 0; i < len; i++)
    {
        char c = str[i];
        if (!isalpha(c))
        {
            return false;
        }
        if (mapping[tolower(c) - 'a'])
        {
            return false;
        }
        else
        {
            mapping[tolower(c) - 'a'] = true;
        }
    }
    return true;
}

string encrypt(const string key, string text)
{
    string enc_text = text;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            if (islower(c))
            {
                enc_text[i] = tolower(key[c - 'a']);
            }
            else
            {
                enc_text[i] = toupper(key[c - 'A']);
            }
        }
    }
    return enc_text;
}
