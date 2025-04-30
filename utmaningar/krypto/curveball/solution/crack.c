#include <stdint.h>
#include <stdio.h>

#define CURVE_P 0xfffff6f5UL
#define CURVE_A 0x477b0389UL
#define CURVE_B 0x323d3e3bUL

typedef __int128_t num_t;

typedef struct
{
    num_t x;
    num_t y;
} ec_point;

static num_t power(num_t x, num_t y, num_t m)
{
    if(y == 0)
        return 1;
    num_t p = power(x,y/2, m) % m;
    p = (p * p) % m;
    return (y%2 == 0) ? p : (x*p) % m;
}

static num_t mod_inverse(num_t a, num_t m)
{
    if(a<0) a += m;
    a = a % m;
    num_t result = power(a, m-2, m);
    if(result < 0)
        result = (-result) % m;
    return result;
}

static ec_point ec_point_add(ec_point P, ec_point Q)
{
    num_t lambda;
    ec_point R;

    if (P.x == 0 && P.y == 0) return Q;
    if (Q.x == 0 && Q.y == 0) return P;

    if (P.x == Q.x) lambda = ( (3 * P.x * P.x + CURVE_A) * mod_inverse(2 * P.y, CURVE_P) ) % CURVE_P;
    else            lambda = ( (P.y - Q.y) * mod_inverse(P.x - Q.x, CURVE_P)) % CURVE_P;

    R.x = (lambda * lambda - P.x - Q.x) % CURVE_P;
    R.y = (-(P.y + lambda * (R.x - P.x))) % CURVE_P;

    if(R.x < 0) R.x += CURVE_P;
    if(R.y < 0) R.y += CURVE_P;

    return R;
}

int main()
{
    setbuf(stdout, NULL);

    ec_point G   = { 0x6fc97239, 0x56b4b074 };
    ec_point P   = { 0x6fc97239, 0x56b4b074 };
    ec_point pub = { 0x228def34, 0xfec0cf56 };

    num_t priv=1;
    for(;priv<=CURVE_P; ++priv)
    {
        if((priv & 0xfffff) == 0)
            printf("%x\r", (uint32_t)priv);

        if(P.x == pub.x && P.y == pub.y)
            printf("%x\n", (uint32_t)priv);

        P = ec_point_add(P, G);
    }
    printf("Done    \n");
    return 0;
}

