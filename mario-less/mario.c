#include <cs50.h>
#include <stdio.h>

void print_blanks(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s", " ");
    }
}

void print_bricks(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s", "#");
    }
}

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    for (int i = 1; i <= height; i++)
    {
        print_blanks(height - i);
        print_bricks(i);
        printf("\n");
    }
    return 0;
}
