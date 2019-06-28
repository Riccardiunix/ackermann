#include <stdio.h>
#include <gmp.h>

#define MAXM 6
#define MAXN 3
#define MAXDIM 100000
#define FID 3

MP_INT ans[MAXM-FID][MAXDIM];
MP_INT risult, one, two;

int ack(MP_INT m, MP_INT n){
    MP_INT res;
    mpz_init(&res);
    if (mpz_cmp_ui(&m, 0) == 0){
        mpz_add_ui(&risult, &n, 1);
        return 0;
    }
    if (mpz_cmp_ui(&m, 1) == 0){
        mpz_add_ui(&risult, &n, 2);
        return 0;
    }
    if (mpz_cmp_ui(&m, 2) == 0){
        mpz_mul_ui(&res, &n, 2);
        mpz_add_ui(&risult, &res, 3);
        return 0;
    }
    
    MP_INT mlFID, ml1, nl1;
    
    mpz_init(&mlFID);
    mpz_init(&ml1);
    mpz_init(&nl1);
    
    mpz_sub_ui(&mlFID, &m, FID);
    mpz_sub_ui(&ml1, &m, 1);
    mpz_sub_ui(&nl1, &n, 1);
    
    if (mpz_cmp_ui(&m, 3) == 0 && mpz_cmp_si(&n, 0) > 0 && mpz_cmp_si(&n, MAXDIM) < 0){
        if (mpz_cmp_ui(&ans[mpz_get_ui(&mlFID)][mpz_get_ui(&nl1)], 0) != 0){
            mpz_mul_ui(&res, &ans[mpz_get_ui(&mlFID)][mpz_get_ui(&nl1)], 2);
            mpz_add_ui(&risult, &res, 3);
        }
        else{
            ack(m, nl1);
            mpz_mul_ui(&res, &risult, 2);
            mpz_add_ui(&risult, &res, 3);
        }
        return 0; 
    }

    if (mpz_cmp_ui(&m, 4) == 0 && mpz_cmp_si(&n, 0) > 0 && mpz_cmp_si(&n, MAXDIM) < 0){
        if (mpz_cmp_ui(&ans[mpz_get_ui(&mlFID)][mpz_get_ui(&nl1)], 0) != 0){
            mpz_add_ui(&res,  &ans[mpz_get_ui(&mlFID)][mpz_get_ui(&nl1)], 3);
            mpz_pow_ui(&res, &two, mpz_get_ui(&res));
            mpz_sub_ui(&risult, &res, 3);   
        }
        else{
            ack(m, nl1);
            mpz_add_ui(&res,  &risult, 3);
            mpz_pow_ui(&res, &two, mpz_get_ui(&res));
            mpz_sub_ui(&risult, &res, 3);
        }
        return 0;
    }

    if (mpz_cmp_si(&n, 0) == 0) ack(ml1, one);
    else if (mpz_cmp_si(&n, 0) > 0 && mpz_cmp_si(&n, MAXDIM) < 0 && mpz_cmp_ui(&ans[mpz_get_ui(&mlFID)][mpz_get_ui(&nl1)], 0) != 0) ack(ml1, ans[mpz_get_ui(&mlFID)][mpz_get_ui(&nl1)]);
    else if (mpz_cmp_si(&n, 1) == 0){
        ack(ml1, one);
        ack(m, risult);
    }
    else{
        ack(m, nl1);
        ack(ml1, risult);
    }

    mpz_init_set(&ans[mpz_get_ui(&mlFID)][mpz_get_ui(&n)], &risult);
    return 0;
}

int main(){
    mpz_init(&risult);
    mpz_init_set_ui(&one, 1);
    mpz_init_set_ui(&two, 2);

    MP_INT i, j;
    mpz_init_set_ui(&i, 0);
    mpz_init_set_ui(&j, 0);
    
    while (mpz_cmp_ui(&i, MAXM) < 0){
        while (mpz_cmp_ui(&j, MAXN) < 0){
            ack(i, j);
            char *res = mpz_get_str(NULL, 10, &risult);
            printf("ackermann (%lu, %lu): %s\n", mpz_get_ui(&i), mpz_get_ui(&j), res);
            mpz_add_ui(&j, &j, 1);
        }
        mpz_set_ui(&j, 0);
        mpz_add_ui(&i, &i, 1);
    }

    return 0;
}
