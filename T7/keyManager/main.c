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
#define TRUE 1
#define FALSE 0
#define base 10

#define argIndexForEmissorKey 1
#define argIndexForReceptorKey 2

#define tamanhoMaxEntrada 100
int verificaPrimo(long long nb);
int verificaSeNumero(char * valor);

int verificaModoVerbose(char *argumento){
    if (strcmp(argumento, "-v")==0) {
        return TRUE;
    }else{
        return FALSE;
    }
}



int verificaPrimo(long long nb){
    long long i, contar, teste,limite;
    teste = contar = 0;
    limite = sqrt(nb) + 1;
    
    if (nb % 2 == 0)
        teste = 1;
    else{
        for (i = 3 ; i < limite && ! teste; i+=2, contar++)
            if (nb % i == 0)
                teste = 1;
    }
    if (!teste){
        return 1;
    }else{
        return 0;
    }

}

int verificaSeNumero(char * valor){
    long val;
    char *next;

    val = strtol (valor, &next, 10);
    
    if ((next == valor) || (*next != '\0')) {
        return FALSE;
    } else {
        return TRUE;
    }
}
    
long double getld(){
    char numbers[] = "";
    scanf ("%s", numbers);
    if (verificaSeNumero(numbers)) {
        return strtold (numbers, NULL);
    }else{
        return -1;
    }
}



int main(int argc, const char * argv[])
{
        char *str;
    
    
        mpz_t n;
        mpz_init (n);
        printf("\nInsira n (valor inteiro primo) ");
        scanf("%s",str);
        mpz_set_str (n, str, base);
    
        mpz_t a;
        mpz_init (a);
        printf("\nInsira a (valor inteiro menor que %s) ",str);
        scanf("%s",str);
        mpz_set_str (a, str, base);
    
        mpz_t p;
        mpz_init (p);
        printf("\nInsira p ");
        scanf("%s",str);
        mpz_set_str (p, str, base);
        
        mpz_t r;
        mpz_init (r);
        printf("\nInsira r ");
        scanf("%s",str);
        mpz_set_str (r, str, base);
    
    
        mpz_t xEmissor;
        mpz_init (xEmissor);
        mpz_powm (xEmissor, a, p, n);

        mpz_t xReceptor;
        mpz_init (xReceptor);
        mpz_powm (xReceptor, a, r, n);

        mpz_t sE;
        mpz_init (sE);
        mpz_powm (sE, xEmissor, r, n);

        mpz_t sR;
        mpz_init (sR);
        mpz_powm (sR, xReceptor, p, n);

    
        printf("\nn ");
        mpz_out_str (stdout, base, n);

        printf("\na ");
        mpz_out_str (stdout, base, a);
        
        printf("\np ");
        mpz_out_str (stdout, base, p);
        
        printf("\nr ");
        mpz_out_str (stdout, base, r);
        
        printf("\nA q = ap (mod N) --> B ");
        mpz_out_str (stdout, base, xEmissor);
        
        printf("\nB s = ar (mod N) --> A ");
        mpz_out_str (stdout, base, xReceptor);
        
        printf("\nA: sp (mod N) = ");
        mpz_out_str (stdout, base, sE);
        
        printf("\nB: qr (mod N) = ");
        mpz_out_str (stdout, base, sR);
    
        printf("\n");
    
        mpz_clear(n);
        mpz_clear(a);
        mpz_clear(p);
        mpz_clear(r);
        mpz_clear(xEmissor);
        mpz_clear(xReceptor);
        mpz_clear(sE);
        mpz_clear(sR);
        

    getchar();
    return 0;
}

