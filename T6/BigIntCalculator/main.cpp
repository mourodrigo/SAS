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
    if (d <= 0)
        return NULL;
    else {
        b = MultiplyDigit( d - 1, n);
        return AddBigInt( b, n);
    }
}

bigIntT setNUllForLeadingDigits(bigIntT n){
    if (!n) {
        return NULL;
    }
    if (n->leadingDigits) {
        n->leadingDigits=setNUllForLeadingDigits(n->leadingDigits);
    }
    if (!n->leadingDigits&&n->finalDigit==0) {
        return NULL;
    }else{
        return n;
    }
    
}

int SubtractFromCarry(bigIntT n1){
//    if (n1->finalDigit==0 && n1->leadingDigits) {
//        if (n1->leadingDigits==0 && n1->leadingDigits->leadingDigits) {
//            return SubtractFromCarry(n1->leadingDigits);
//        }else if(n1->finalDigit==0 && n1->leadingDigits>0){
//            n1->leadingDigits->finalDigit--;
//            n1->finalDigit+=10;
//            return 1;
//        }
//        return 0;
//    }else{
//        return 0;
//    }
    if (n1->leadingDigits==0&&!n1->leadingDigits) {
        n1->leadingDigits=NULL;
        n1=NULL;
        return 0;
    }
    if (n1->leadingDigits->finalDigit==0) {
        SubtractFromCarry(n1->leadingDigits);
    }
    n1->leadingDigits->finalDigit--;
    if (n1->leadingDigits->finalDigit<0) {
        return 0;
    }
    n1->finalDigit+=10;
    if(!n1->leadingDigits->leadingDigits && n1->leadingDigits==0){
        n1->leadingDigits=NULL;
        n1=NULL;
    }
    return 1;
}

bigIntT SubtractBigInt(bigIntT n1, bigIntT n2){
    if (!n2) {
        return n1;
    }
    if (!n1&&n2) {
        n2->finalDigit=0-n2->finalDigit;
        return n2;
    }
    if (n1->finalDigit<n2->finalDigit) {
        if (SubtractFromCarry(n1)<1) return n1;
    }
    n1->finalDigit-=n2->finalDigit;
    while (n1->leadingDigits && n2->leadingDigits) {
        SubtractBigInt(n1->leadingDigits, n2->leadingDigits);
    }
//    if (n1->finalDigit && n2->finalDigit) {
//        n1->finalDigit = n1->finalDigit-n1->finalDigit;
//    }else if (!n1->finalDigit && n2->finalDigit && SubtractFromCarry(n1)){
////        n1->finalDigit = n1->finalDigit+10;
//        n1->finalDigit = n1->finalDigit-n2->finalDigit;
//    }
//    if (n1->leadingDigits && n2->leadingDigits) {
//        SubtractBigInt(n1->leadingDigits, n2->leadingDigits);
//    }
    return n1;
}

int CompareBigInt(bigIntT n1, bigIntT n2){
    int result=0;
    if (n1->leadingDigits && n2->leadingDigits) {
        result =  CompareBigInt(n1->leadingDigits , n2->leadingDigits);
    }else if(n1->leadingDigits && !n2->leadingDigits){
        return 1;
    }else if (!n1->leadingDigits && n2->leadingDigits){
        return -1;
    }
    if (result==0){
        if (n1->finalDigit>n2->finalDigit) {
            return 1;
        }else if(n1->finalDigit==n2->finalDigit) {
            if (n1->leadingDigits && n2->leadingDigits) {
                result =  CompareBigInt(n1->leadingDigits , n2->leadingDigits);
            }else{
                return 0;
            }
        }else{
            return -1;
        }
    }
    return result;
}

bigIntT ModBigInt(bigIntT n1, bigIntT n2){
//    int diff=CompareBigInt(n1, n2);
    
    while (1) {
        setNUllForLeadingDigits(n1);
        if (!n1&&n2) {
            return n2;
        }
        if (n1->finalDigit<n2->finalDigit && !n1->leadingDigits) {
            return n1;
        }else{
            n1=SubtractBigInt(n1, n2);
        }
//        if (CompareBigInt(n1, zero)<0) {
//            return lastn1;
//        }
//        diff=CompareBigInt(n1, n2);
    }
    return n1;
}

void euclidianoEstendido(int a, int b, int *alpha, int *beta, int *mdc) {
    int x[2] = {1, 0};
    int y[2] = {0, 1};
//    mdc=0;
//    beta=0;
//    alpha=0;
//    /* Enquanto o resto da divisão de a por b não for zero, eu continuo o algoritmo. */
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


void extendedEuclideanAlgorithm(bigIntT a, bigIntT b, bigIntT *alpha, bigIntT *beta, bigIntT *mdc) {
    bigIntT x[2] = {StringToBigInt("1"), StringToBigInt("0")};
    bigIntT y[2] = {StringToBigInt("0"), StringToBigInt("1")};
    //    mdc=0;
    //    beta=0;
    //    alpha=0;
    //    /* Enquanto o resto da divisão de a por b não for zero, eu continuo o algoritmo. */
    while (ModBigInt(a, b)->finalDigit!=0) {
        bigIntT quociente = ModBigInt(a, b);
        
        /* Atualizando os valores de a e b. */
        bigIntT temp = StringToBigInt(BigIntToString(a));
        a = b;
        b = ModBigInt(temp, b);
        
        /* Atualizando os valores de x e y. */
        bigIntT X = SubtractBigInt(x[0], MultiplyBigInt(x[1], quociente));
        bigIntT Y = SubtractBigInt(y[0], MultiplyBigInt(y[1], quociente));
        
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
        int option,expoente;
        bigIntT alpha, beta, mdc;
        bigIntT result,value;
        string resultstdout = "Resultado: ";
        if (argc<4) {
            cout << "\n1 - Soma\n2 - Multiplicação\n3 - Exponenciacao \n4 - Inverso Multiplicativo\n\n Opção:";
            cin >> option;
        }else{
            option = atoi(argv[1]);
            a = string(argv[2]);
            b = string(argv[3]);
            resultstdout="";
        }
        switch (option) {
            case 1:
                if(strcmp("",a.c_str())==0){
                    cout << "Valor a:" ;
                    cin >> a;
                }
                if(strcmp("",b.c_str())==0){
                    cout << "Valor b:" ;
                    cin >> b;
                }
                cout <<resultstdout<< BigIntToString(AddBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;
                break;
            case 2:
                if(strcmp("",a.c_str())==0){
                    cout << "Valor a:" ;
                    cin >> a;
                }
                if(strcmp("",b.c_str())==0){
                    cout << "Valor b:" ;
                    cin >> b;
                }
                cout <<resultstdout<< BigIntToString(MultiplyBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;

                break;
            case 3:
                if(strcmp("",a.c_str())==0){
                    cout << "Valor Base:" ;
                    cin >> a;
                }
                
                if(strcmp("",b.c_str())==0){
                    cout << "Valor Expoente:" ;
                    cin >> b;
                }
                expoente = atoi(b.c_str());
                result = StringToBigInt(a);
                value = StringToBigInt(a);
                while (expoente>1) {
                    result = MultiplyBigInt(value, result);
                    expoente--;
                }
                cout <<resultstdout<< BigIntToString(result) << endl;
                break;
            case 4:
                
                if(strcmp("",a.c_str())==0) {
                    cout << "Valor Base:" ;
                    cin >> a;
                }
                if(strcmp("",b.c_str())==0){
                    cout << "Valor Expoente:" ;
                    cin >> b;
                }
                
//                euclidianoEstendido(atoi(a.c_str()), atoi(b.c_str()), &alpha, &beta, &mdc);
                extendedEuclideanAlgorithm(StringToBigInt(a), StringToBigInt(b), &alpha, &beta, &mdc);
                if (argc>1) {
                    cout << "\n" << alpha << "\n" << beta << "\n" << mdc << endl;
                }else{
                    cout << "alpha " << BigIntToString(alpha) << " beta " << BigIntToString(beta) << " MDC: " << BigIntToString(mdc) << endl;
                }
                break;

            case 5:
                cout << "Dividendo:" ;
                if(strcmp("",a.c_str())==0) cin >> a;
                cout << "Divisor:" ;
                if(strcmp("",b.c_str())==0) cin >> b;
                cout <<resultstdout<< BigIntToString(ModBigInt(StringToBigInt(a), StringToBigInt(b))) << endl;
                break;

            default:
                free(&a);
                free(&b);
                break;
        }
        if (argc>1) {
            break;
        }
    }
    
    return 0;
}
