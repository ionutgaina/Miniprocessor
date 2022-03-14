#include <stdio.h>

unsigned int is_set(unsigned int byte, int i)
{
    int mask = (1 << i);
    return (byte & mask) != 0;
}

unsigned int set(unsigned int byte, int i)
{
    int mask = (1 << i);
    return (byte | mask);
}

// unsigned int reset(unsigned int byte, int i)
// {
//     int mask = ~(1 << i);
//     return (byte & mask);
// }

int main()
{
    int i;
    unsigned int N = 0, dim = 0, instr;
    scanf("%u", &instr);

    // obtinem N-ul
    for (i = 0; i < 3; i++)
    {
        if (is_set(instr, 32 - 3 + i))
            N = set(N, i);
    }
    N++;
    printf("%u ", N);

    // obtinem operatorii
    for (i = 28; i > 28 - N * 2; i -= 2)
    {
        if (is_set(instr, i) == 0 && is_set(instr, i - 1) == 0)
        {
            printf("+ ");
        }
        if (is_set(instr, i) == 0 && is_set(instr, i - 1) == 1)
        {
            printf("- ");
        }
        if (is_set(instr, i) == 1 && is_set(instr, i - 1) == 0)
        {
            printf("* ");
        }
        if (is_set(instr, i) == 1 && is_set(instr, i - 1) == 1)
        {
            printf("/ ");
        }
    }

    // obtinem dim
    unsigned c = 0; // contor dimensiune
    for (i = 28 - N * 2 - 3; i < 29 - N * 2; i++)
    {
        if (is_set(instr, i))
            dim = set(dim, c);
        c++;
    }
    dim++;
    printf("%u\n", dim);

    return 0;
}