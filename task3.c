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

int power(int baza, int exponent)
{
    int rezultat = 1, i;
    for (i = exponent; i > 0; i--)
    {
        rezultat *= baza;
    }
    return rezultat;
}

int main()
{
    int i, j, rezultat;
    unsigned int N = 0, dim = 0, instr, c, v[16] = {0};
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
    // printf("dim: %hu\n",dim);
    // citim numarele in vectorul v_bit
    unsigned short nr, v_bit[160] = {0};
    for (i = 0; i < formula(N, dim); i++)
    {
        scanf("%hu", &nr);
        for (j = 0; j < 16; j++)
            v_bit[i * 16 + j] = is_set(nr, 15 - j);
    }

    // calculam lungimea vectorului v_bit
    int lnght_v_bit = (i - 1) * 16 + j;

    // calculam operanzii
    // contor vector de operanzi
    c = 0;
    for (i = 0; i < (lnght_v_bit / dim) + 1; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (v_bit[i * dim + j])
                v[c] += power(2, dim - (j + 1));
        }
        c++;
    }

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