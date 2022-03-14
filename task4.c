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

int stergere_op(unsigned int v[], int p, int n)
{
    for( int i = p ; i <= n - 2; i += 2)
    {
        v[i] = v[i+2];
        v[i+1] = v[i+3];
    }
    return n - 2;
}

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
    int i, j, rezultat, nr_op, lnght_v_bit;
    unsigned int N = 0, dim = 0, instr, c, v[16+MAXOP] = {0};
    unsigned short nr, v_bit[160] = {0};

    scanf("%u", &instr);

    // obtinem N-ul
    for (i = 0; i < 3; i++)
    {
        if (is_set(instr, 32 - 3 + i))
            N = set(N, i);
    }
    N++;


    // obtinem operatorii
    c = 1; // contor vector operanzi
    for (i = 28; i > 28 - N * 2; i -= 2)
    {
        if (is_set(instr, i) == 0 && is_set(instr, i - 1) == 0)
        {
            v[c] = 0;
        }
        if (is_set(instr, i) == 0 && is_set(instr, i - 1) == 1)
        {
            v[c] = 1;
        }
        if (is_set(instr, i) == 1 && is_set(instr, i - 1) == 0)
        {
            v[c] = 2;
        }
        if (is_set(instr, i) == 1 && is_set(instr, i - 1) == 1)
        {
            v[c] = 3;
        }
        c+=2;
    }

    nr_op = c - 2;

    // obtinem dim
    c = 0; // contor dimensiune
    for (i = 29 - N * 2 - 4; i < 29 - N * 2; i++)
    {
        if (is_set(instr, i))
            dim = set(dim, c);
        c++;
    }
    dim++;

    // citim numarele in vectorul v_bit
    for (i = 0; i < formula(N, dim); i++)
    {
        scanf("%hu", &nr);
        for (j = 0; j < 16; j++)
            v_bit[i * 16 + j] = is_set(nr, 15 - j);
    }

    // calculam lungimea vectorului v_bit
    lnght_v_bit = (i - 1) * 16 + j;

    // calculam operanzii
    c = 0; // contor vector de operanzi
    for (i = 0; i < (lnght_v_bit / dim) + 1; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (v_bit[i * dim + j])
                v[c] += power(2, dim - (j + 1));
        }
        c+=2;
    }

    // calculam produsul si impartirea
    // creand un vector doar cu adunare si scadere
    // folosind algoritmul de stergere de elemente dintr-un vector
    c = 1;
    for ( i = 1 ; i <= nr_op ; i += 2 )
    {
        if ( v[i] == 2 )
        {
            v[i-1] *= v[i+1];
            nr_op = stergere_op(v,i,nr_op);
            i -= 2;
        }
        else if ( v[i] == 3 )
        {
            v[i-1] /= v[i+1];
            nr_op = stergere_op(v,i,nr_op);
            i -= 2;
        }
    }

    // obtinem rezultatul
    rezultat = v[0];
    for (i = 1; i <= nr_op ; i +=2 )
    {
        if (v[i] == 0)
        {
            rezultat += v[i+1];
        }
        if (v[i] == 1)
        {
            rezultat -= v[i+1];
        }
    }

    printf("%d\n", rezultat);
    return 0;
}