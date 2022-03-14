#include <stdio.h>

#define MAXOP 8
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

int formula(unsigned int N, unsigned int dim)
{
    if (((N + 1) * dim) % 16 != 0)
        return ((N + 1) * dim) / 16 + 1;
    else
        return ((N + 1) * dim) / 16;
}
// unsigned int reset(unsigned int byte, int i)
// {
//     int mask = ~(1 << i);
//     return (byte & mask);
// }

int main()
{
    int i, j, rezultat;
    unsigned int N = 0, dim = 0, instr, c, v[16];
    char op[MAXOP];
    scanf("%u", &instr);

    // obtinem N-ul
    for (i = 0; i < 3; i++)
    {
        if (is_set(instr, 32 - 3 + i))
            N = set(N, i);
    }
    N++;

    // obtinem operatorii
    c = 0; // contor vector operanzi
    for (i = 28; i > 28 - N * 2; i -= 2)
    {
        if (is_set(instr, i) == 0 && is_set(instr, i - 1) == 0)
        {
            op[c] = '+';
        }
        if (is_set(instr, i) == 0 && is_set(instr, i - 1) == 1)
        {
            op[c] = '-';
        }
        if (is_set(instr, i) == 1 && is_set(instr, i - 1) == 0)
        {
            op[c] = '*';
        }
        if (is_set(instr, i) == 1 && is_set(instr, i - 1) == 1)
        {
            op[c] = '/';
        }
        c++;
    }

    // obtinem dim
    c = 0; // contor dimensiune
    for (i = 29 - N * 2 - 4; i < 29 - N * 2; i++)
    {
        if (is_set(instr, i))
            dim = set(dim, c);
        c++;
    }
    dim++;

    // citim numarul si despartim in operanzi
    unsigned short nr;
    c = 0;
    for (i = 0; i < formula(N, dim); i++)
    {
        scanf("%hu", &nr);
        for (j = 0; j < 16 / dim; j++)
            v[c++] = (nr >> (16 - dim - j * dim)) & ((1 << dim) - 1);
    } // 1<<dim - 1 in biti sunt primiile dim pozitii

    // obtinem rezultatul
    rezultat = v[0];
    for (i = 1; i < formula(N, dim) * 16 / dim; i++)
    {
        if (op[i - 1] == '+')
        {
            rezultat += v[i];
        }
        if (op[i - 1] == '-')
        {
            rezultat -= v[i];
        }
        if (op[i - 1] == '*')
        {
            rezultat *= v[i];
        }
        if (op[i - 1] == '/')
        {
            rezultat /= v[i];
        }
    }

    printf("%d\n", rezultat);
    return 0;
}