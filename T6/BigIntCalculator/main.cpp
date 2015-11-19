//
//  main.c
//  bigIntCalculator
//
//  Created by Rodrigo Bueno Tomiosso on 15/11/15.
//  Copyright © 2015 mourodrigo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct cellT *bigIntT;
bigIntT NewBigInt( int i);
bigIntT StringToBigInt( string str);
string BigIntToString( bigIntT n);
bigIntT DigitCons( bigIntT n, int d);
bigIntT LeadingDigits( bigIntT n);
int FinalDigit( bigIntT n);
bigIntT AddBigInt( bigIntT n1, bigIntT n2);
bigIntT AddWithCarry( bigIntT n1, bigIntT n2, int carry);
bigIntT MultiplyBigInt( bigIntT n1, bigIntT n2);
bigIntT MultiplyDigit( int d, bigIntT n);


struct cellT {

    int     finalDigit;    // cabeça (dígito das unidades)
    bigIntT leadingDigits; // cauda (dezenas, centenas etc.)
} ;

// A função NewBigInt cria um bigint com valor i.

bigIntT NewBigInt( int i) {
    bigIntT b;
    if (i < 0) exit( EXIT_FAILURE);
    if (i == 0)
        return NULL;
    else {
        b = NewBigInt( i / 10);
        return DigitCons( b, i % 10);
    }
}

// A função abaixo converte uma string str de dígitos
// em um bigint. Exemplos: "1234" é convertida em 1234,
// "001" é convertido em 1, "00" é convertida em NULL.

bigIntT StringToBigInt( string str) {
    int len;
    char ch;
    bigIntT b;
    len = (int)strlen( str.c_str());
    if (len == 0)
        return NULL;
    else {
        ch = str[len - 1];
        str[len - 1] = '\0';
        b = StringToBigInt( str);
        return DigitCons( b, ch - '0');
    }
}

// A função abaixo converte um bigint n em uma string.
// Exemplos: 1234 é convertido em "1234" e NULL é
// convertido em "0".

string BigIntToString( bigIntT n) {
    string newstr = "";
    while (n) {
        newstr = to_string(n->finalDigit).append(newstr);
        n=n->leadingDigits;
    }
    return newstr;
}

// A função DigitCons recebe um bigint n e um inteiro d
// entre 0 e 9 e devolve o bigint cujo valor é 10 * n + d.
// Se n é NULL ou d == 0 então a função devolve NULL.

bigIntT DigitCons( bigIntT n, int d) {
    bigIntT cp;
    if (n == NULL && d == 0)
        return NULL;
    else {
        cp = (bigIntT)malloc( sizeof (cellT));
        if (cp == NULL) exit( EXIT_FAILURE);
        cp->finalDigit = d;
        cp->leadingDigits = n;
        return cp;
    }
}

// A função LeadingDigits devolve o bigint formado pelos
// dígitos mais significativos (dezenas, centenas, etc) de n.

bigIntT LeadingDigits( bigIntT n) {
    return (n == NULL) ? NULL : n->leadingDigits;
}

// A função FinalDigit devolve o dígito das unidades de n.

int FinalDigit( bigIntT n) {
    return (n == NULL) ? 0 : n->finalDigit;
}

// Devolve o resultado da soma de n1 com n2.

bigIntT AddBigInt( bigIntT n1, bigIntT n2) {
    return AddWithCarry( n1, n2, 0);
}

// Devolve o valor de n1 + n2 + carry.

bigIntT AddWithCarry( bigIntT n1, bigIntT n2, int carry) {
    int sum;
    bigIntT p1, p2, b;
    p1 = LeadingDigits( n1);
    p2 = LeadingDigits( n2);
    sum = FinalDigit( n1) + FinalDigit( n2) + carry;
    if (sum == 0 && p1 == NULL && p2 == NULL)
        return NULL;
    else {
        b = AddWithCarry( p1, p2, sum / 10);
        return DigitCons( b, sum % 10);
    }
}

// A função MultiplyBigInt devolve o valor de n1 * n2.
// A recursão tem por base a expressão
// FinalDigit( n1) * n2 + LeadingDigits( n1) * n2 * 10.
// Por exemplo, 342 * 173 == 342 * 3 + 342 * 17 * 10.

bigIntT MultiplyBigInt( bigIntT n1, bigIntT n2) {
//     int sum;
    bigIntT b, c, n2vezes10;
    if (n1 == NULL)
        return NULL;
    else {
        b = MultiplyDigit( FinalDigit( n1), n2);
        n2vezes10 = DigitCons( n2, 0);
        c = MultiplyBigInt( LeadingDigits( n1), n2vezes10);
        return AddBigInt( b, c);
    }
}

// A função MultiplyDigit devolve o valor de d * n.

bigIntT MultiplyDigit( int d, bigIntT n) {
    bigIntT b;
    if (d == 0)
        return NULL;
    else {
        b = MultiplyDigit( d - 1, n);
        return AddBigInt( b, n);
    }
}

bigIntT SubtractBigInt(bigIntT n1, bigIntT n2){
    if (n1->finalDigit && n2->finalDigit) {
        n1->finalDigit = n1->finalDigit-n2->finalDigit;
    }
    if (n1->leadingDigits && n2->leadingDigits) {
        SubtractBigInt(n1->leadingDigits, n2->leadingDigits);
    }
    return n1;
}

int CompareBigInt(bigIntT n1, bigIntT n2){
    int result=0;
    if (n1->leadingDigits && n2->leadingDigits) {
        result =  CompareBigInt(n1->leadingDigits , n2->leadingDigits);
    }
    if (result==0){
        if (n1->finalDigit>n2->finalDigit) {
            return 1;
        }else if(n1->finalDigit==n2->finalDigit) {
            return 0;
        }else{
            return -1;
        }
    }
    return result;
}

void euclidianoEstendido(int a, int b, int *alpha, int *beta, int *mdc) {
    int x[2] = {1, 0};
    int y[2] = {0, 1};
    
    /* Enquanto o resto da divisão de a por b não for zero, eu continuo o algoritmo. */
    while (a % b != 0) {
        int quociente = a / b;
        
        /* Atualizando os valores de a e b. */
        int temp = a;
        a = b;
        b = temp % b;
        
        /* Atualizando os valores de x e y. */
        int X = x[0] - (x[1] * quociente);
        int Y = y[0] - (y[1] * quociente);
        
        x[0] = x[1];
        x[1] = X;
        y[0] = y[1];
        y[1] = Y;
    }
    
    *mdc = b;
    *alpha = x[1];
    *beta = y[1];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    while (1) {
        string a,b;
        cout << "\n1 - Soma\n2 - Subtração\n3 - Exponenciacao \n4 - Inverso Multiplicativo\n\n Opção:";
        int option, expoente;
        int *alpha, *beta, *mdc;
        bigIntT result,value;
        cin >> option;
        switch (option) {
            case 1:
                cout << "Valor a:" ;
                cin >> a;
                cout << "Valor b:" ;
                cin >> b;
                cout << "Resultado: " << BigIntToString(AddBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;
                break;
            case 2:
                cout << "Valor a:" ;
                cin >> a;
                cout << "Valor b:" ;
                cin >> b;
                cout << "Resultado: " << BigIntToString(SubtractBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;

                break;
            case 3:
                cout << "Valor Base:" ;
                cin >> a;
                cout << "Valor Expoente:" ;
                cin >> expoente;
                result = StringToBigInt(a);
                value = StringToBigInt(a);
                while (expoente>0) {
                    result = MultiplyBigInt(value, result);
                    expoente--;
                }
                cout << "Resultado: " << BigIntToString(result) << endl;
                break;
            case 4:
                cout << "Valor Base:" ;
                cin >> a;
                cout << "Valor Expoente:" ;
                cin >> b;
                
                euclidianoEstendido(atoi(a.c_str()), atoi(b.c_str()), alpha, beta, mdc);
                cout << "alpha " << alpha << "beta " << beta << "mds" << mdc << endl;
                
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
