#include <stdio.h>
#include <stdlib.h>
#include "openssl/bn.h"

//int getRes(BN_ULONG p)
//{
//    BN_ULONG r = 0;
//    for(int i = 0; i < 64; i ++)
//    {
//        r += p % 2;
//        p /= 2;
//    }
//    if(r % 2 == 0)
//        return 0;
//    else
//        return 1;
//}

int getRes(BN_ULONG p)
{
    BN_ULONG r = 0;
    r = p % 2;
    return r;
}

void BBSGen(BIGNUM *s, BIGNUM *m, int length)
{
    BIGNUM *ctx, *xp, *x;
    FILE *fp1, *fp2;
    int res;
    ctx = BN_CTX_new();
    xp = BN_new();
    x = BN_new();
    BN_copy(xp, s);
    fp1 = fopen("./BBSInTxt.txt","w");
    fp2 = fopen("./BBSInBin.bin","wb");
    for(int i = 0; i < length; i ++)
    {
        BN_mod_sqr(x, xp, m, ctx);
        res = getRes(BN_get_word(x));
        printf("%d",res);
        fprintf(fp1, "%d", res);
        fprintf(fp2, "%d", res);
        BN_copy(xp, x);
    }
    BN_free(xp);
    BN_free(x);
    BN_CTX_free(ctx);
    fclose(fp1);
    fclose(fp2);
}

int main()
{
    int length, quantity;
    BN_ULONG x;
    BIGNUM *s;
    BIGNUM *p, *q, *m, *ctx, *temp1, *temp2;
    p = BN_new();
    q = BN_new();
    m = BN_new();
    s = BN_new();
    temp1 = BN_new();
    temp2 = BN_new();
    ctx = BN_CTX_new();

    BN_set_word(temp1, 4);
    BN_set_word(temp2, 3);
    BN_generate_prime_ex(p, 20, NULL ,temp1, temp2, NULL);
    BN_generate_prime_ex(q, 20, NULL ,temp1, temp2, NULL);
    BN_mul(m, p, q, ctx);

    printf("Please enter your seed, which should be co-prime to %ul = %ul * %ul\n", BN_get_word(m), BN_get_word(p), BN_get_word(q));
    scanf("%ul", &x);
    BN_set_word(s, x);
    printf("Please enter your length\n");
    scanf("%d", &length);

    BBSGen(s, m, length);

    BN_free(p);
    BN_free(q);
    BN_free(m);
    BN_free(s);
    BN_free(temp1);
    BN_free(temp2);
    BN_CTX_free(ctx);
}
