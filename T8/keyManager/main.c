//
//  main.c
//  keyManager
//
//  Created by Rodrigo Bueno Tomiosso on 23/07/14.
//  Copyright (c) 2014 zk. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "include/gmp.h"
#include <signal.h>
#include <sys/time.h>
#define base 10
volatile unsigned int i, counter, value;

static void handler(void);

unsigned int get_random(void){ //Busca um valor aleatorio baseado no timestamp
    struct itimerval x, y;
    
    i = 0;
    counter = 0;
    value = 0;
    
    x.it_interval.tv_sec = 0;
    x.it_interval.tv_usec = 1;
    x.it_value.tv_sec = 0;
    x.it_value.tv_usec = 1;
    
    if (setitimer(ITIMER_REAL, &x, &y) == -1)
    {
        perror("get_random()");
        return 0;
    }
    
    signal(SIGALRM, handler);
    
    while (counter < 8)
        i++;
    
    signal(SIGALRM, SIG_IGN);
    
    if (setitimer(ITIMER_REAL, &y, (struct itimerval *) NULL) == -1)
        perror("get_random()");
    
    return value;
}

void handler(void) {
    value = (value << 1) | (i & 0x1);
    counter++;
    i = 0;
    signal(SIGALRM, handler);
}


int main(int argc, char **argv){
    MP_INT p, q, phi, n;
    int i, bits, rdm, pp = 0;
    char *buf, *n_buf;
    
    bits = 32;
    
    rdm = 32;
    
    i = rdm;
    
    printf("Insira um valor para p ");
    scanf("%d", &pp);
    
start:
    mpz_init_set_ui(&p,pp);
    
    i = rdm;

    printf("\nBuscando valor para q ");

    
    mpz_init_set_ui(&q, 0);//busca um valor para q
    while ((i -= 2) > 0){
        mpz_mul_ui(&q, &q, base);
        mpz_add_ui(&q, &q, get_random());
    }
    
    while (!mpz_probab_prime_p(&q, 25))
        mpz_add_ui(&q, &q, 1);
    
    
    printf("\nValor primo para q encontrado ");
    mpz_out_str (stdout, 10, &q);
    
    printf("\nCalculando modulo n = p^q ");
    mpz_init(&n);
    mpz_mul(&n, &p, &q);
    
    n_buf = mpz_get_str((char *) NULL, base, &n);
    
    
    mpz_sub_ui(&p, &p, 1);
    mpz_sub_ui(&q, &q, 1);
    mpz_init(&phi);
    mpz_mul(&phi, &p, &q);
    mpz_clear(&p);
    
    mpz_init_set_ui(&p,pp);
    
    printf("\nCalculando  d = e-1 (mod φ(N))");

    buf = mpz_get_str((char *) NULL, base, &p);
    mpz_gcdext(&p, &q, &p, &p, &phi);
    
    if ( !mpz_cmp_ui(&q,1) || mpz_cmp(&q,&phi) >= 0) // verifica se é coprimo
    {
        goto start;
    }
    
    printf("\n\nCHAVE PUBLICA: \n\ne = %s\n", buf);
    printf("n = %s\n", n_buf);
    free(buf);
    
    mpz_clear(&p);
    
    if (mpz_cmp_ui(&q, 0) < 0)//se o valor é negativo aplica modulo
        mpz_add(&q, &q, &phi);
    
    mpz_clear(&phi);
    
    buf = mpz_get_str((char *) NULL, base, &q);
    printf("\n\nCHAVE PRIVADA: \n\nd = %s\n", buf);
    printf("n = %s\n\n", n_buf);
    free(buf);
    
    mpz_clear(&q);
    exit(0);
}