//
//  main.cpp
//  CriptBreaker
//
//  Created by Rodrigo Bueno Tomiosso on 06/08/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define NIL 0

#define FORCEREAD

int printDebug = 0;

using namespace std;

int decryptCesar(vector<unsigned int> plainText, vector<unsigned int> darkText){
    int offset=0;
    for (int h=0; h<darkText.size()||h<plainText.size(); h++) {
        if (h==0) {
            offset=plainText.at(0)-darkText.at(0);
        }else if (offset==plainText.at(0)-darkText.at(0) && h>100) {
                break;
        }
    }
    if (offset<0) {
        offset=offset*(-1);
    }
    return offset;
}

void printUnsigedIntVector(vector<unsigned int> vec){
    cout << endl << "{";
    for ( vector<unsigned int>::iterator ints = (vec).begin(); ints != (vec).end(); ++ ints )
    {
        if ((*ints)!=NIL) {
            cout << (*ints);
            if (*ints!=vec.at(vec.size()-1)) {
                cout << " , ";
            }
        }else{
            cout << " , ";
        }
    }
    cout << "}";
}

vector<unsigned int> decryptSubstitute(vector<unsigned int> plainText, vector<unsigned int> darkText){
    
    vector<unsigned int> table (256,NIL);
    for (int k=0; k<plainText.size(); k++) {
        if (table.at(plainText.at(k))==NIL) {
            table[(int)plainText.at(k)] = darkText.at(k);
        }else{
            cout << "WARNING: Provavelmente não é cifra de substitução." << endl;
            break;
        }
    }
    
    return table;
    
}

vector<unsigned int> fileRead(string filePathIn){
    FILE *in;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
    }
    
    unsigned int character;
    unsigned char ccharacter;
//    string read;
    
    vector<unsigned int> v;
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        if (printDebug) {
            cout << ccharacter << " - " << character <<  " - " << endl;
        }
        v.push_back(character);
    }
    fclose(in);

#ifdef FORCEREAD
    if (v.size()==0) {
        return fileRead(filePathIn);
    }
#endif
    return v;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptBreaker!\n";
    
    char option = '\0';
    string plainTextPath, darkTextPath;
    unsigned int type = 0;
    for (int x = 1; x<argc; x++) {
        switch (x) {
            case 1:
                plainTextPath = string(argv[1]);
                break;
            case 2:
                darkTextPath = string(argv[2]);
                break;
            case 3:
                type = atoi(argv[x]);
                break;
            case 4:
                break;
        }
    }
    
    vector<unsigned int> plainText = fileRead(plainTextPath);
    vector<unsigned int> darkText = fileRead(darkTextPath);

    switch (type) {
        case 1:
            cout << endl << endl << "CRITOGRAFIA CESAR -- Chave identificada: " << decryptCesar(plainText, darkText) << endl;
            break;

        case 2:
            cout << endl << endl << "CRITOGRAFIA SUBSTITUIÇÃO -- Mapa:: " << endl;
            printUnsigedIntVector(decryptSubstitute(plainText, darkText));
            break;

    }
    
    
    return 0;
}
