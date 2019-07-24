#include <stdio.h>
int main()
{
    int r, g, b;
    while (!feof(stdin))
    {
        r = getchar() >> 5;
        g = getchar() >> 5;
        b = getchar() >> 5;
        printf("%03X\n", (r << 6) | (g << 3) | (b << 0));
    }
}