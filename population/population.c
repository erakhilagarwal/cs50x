#include <cs50.h>
#include <stdio.h>

int get_start(int minsize)
{
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < minsize);
    return n;
}

int get_end(int minsize)
{
    int n;
    do
    {
        n = get_int("End size: ");
    }
    while (n < minsize);
    return n;
}

int calculate_years(int start, int end)
{
    int yr = 0;
    int curr = start;
    while (curr < end)
    {
        yr++;
        curr = curr - (curr / 4) + (curr / 3);
    }
    return yr;
}

int main(void)
{
    // TODO: Prompt for start size
    int start = get_start(9);

    // TODO: Prompt for end size
    int end = get_end(start);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    years = calculate_years(start, end);

    // TODO: Print number of years
    printf("Years: %d", years);
  
    return 0;
}
