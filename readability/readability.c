#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string get_input();
int count_letters(const string text);
bool is_word_break(char c);
int count_words(const string text);
bool is_sentence_break(char c);
int count_sentences(const string text);
int compute_grade(int letters, int words, int sentences);
void print_grade(int grade);

int main(void)
{
    string input = get_input();

    int letters = count_letters(input);
    int words = count_words(input);
    int sentences = count_sentences(input);
    int grade = compute_grade(letters, words, sentences);
    print_grade(grade);
}

string get_input()
{
    return get_string("Text: ");
}

int count_letters(const string text)
{
    int len = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            len++;
        }
    }
    return len;
}

bool is_word_break(char c)
{
    return (isblank(c) || c == ',' || is_sentence_break(c));
}

int count_words(const string text)
{
    int len = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (is_word_break(text[i]) && (i == 0 || !is_word_break(text[i - 1])))
        {
            len++;
        }
    }
    return len;
}

bool is_sentence_break(char c)
{
    return (c == '.' || c == '?' || c == '!');
}

int count_sentences(const string text)
{
    int len = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (is_sentence_break(text[i]))
        {
            len++;
        }
    }
    return len;
}

int compute_grade(int letters, int words, int sentences)
{
    float L = (float) letters * 100.0 / (float) words;
    float S = (float) sentences * 100.0 / (float) words;
    return round(0.0588 * L - 0.296 * S - 15.8);
}

void print_grade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
