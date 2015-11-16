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


int main(int argc, const char * argv[]) {
    // insert code here...
    while (1) {
        string a,b;
        cout << "Valor a:" ;
        cin >> a;
        cout << "Valor b:" ;
        cin >> b;
        cout << "\n1 - Soma\n2 - Subtração\n3 - Multiplicação\n4 - Divisão\n\n Opção:";
        int option;
        cin >> option;
        switch (option) {
            case 1:
                cout << "Resultado: " << BigIntToString(AddBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;
                break;
            case 2:

                break;
            case 3:
                cout << "Resultado: " << BigIntToString(MultiplyBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;
                break;
            case 4:

                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
