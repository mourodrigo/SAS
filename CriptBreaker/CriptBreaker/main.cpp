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

using namespace std;

typedef unsigned int ui;
typedef vector<ui> vui;

int printDebug = 0;



vui decryptVigenere(vui offsetVector){
    vui result;
    int index = 0;
    ui last=offsetVector.at(0);
    for (int t=1; t< offsetVector.size();t++){
        if (offsetVector.at(t)==last) {
            cout << "repete - " << index << last << endl;
            index = t;
        }
    }
    cout << endl << endl;
    for (int s = 0; s<=index; s++) {
        cout << offsetVector.at(s);
    }
    
    return result;
}

vui getOffsetOfFiles(vui plainText, vui darkText){
    vui table (256,NIL);
    for (int h=0; h<darkText.size()||h<plainText.size(); h++) {
        table[h] = plainText.at(h)-darkText.at(h);
    }
    return table;
}

int decryptCesar(vui plainText, vui darkText){
    int offset=0,assert=0;
    for (int h=0; h<darkText.size()||h<plainText.size()||1; h++) {
        if (h==0) {
            offset=(int)plainText.at(h)-(int)darkText.at(h);
        }else if (offset==(int)plainText.at(h)-(int)darkText.at(h)) {
            assert++;
        }else if (offset!=(int)plainText.at(h)-(int)darkText.at(h)){
            cout << "WARNING: Provavelmente não é cifra de Cesar." << endl;
            break;
        }
        if (assert>100) {
            break;
        }
    }
    if (offset<0) {
        offset=offset*(-1);
    }
    return offset;
}

void printUnsigedIntVector(vui vec){
    cout << endl << "{";
    for ( vui::iterator ints = (vec).begin(); ints != (vec).end(); ++ ints )
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

vui decryptSubstitute(vui plainText, vui darkText){
    
    vui table (256,NIL);
    for (int k=0; k<plainText.size(); k++) {
        if (table[(int)plainText.at(k)]==NIL) {
            table[(int)plainText.at(k)] = darkText.at(k);
            
        }else if(table[(int)plainText.at(k)]!=darkText.at(k)){
            cout << "table.at(plainText.at("<<k<<")) == " << table.at(plainText.at(k)) << endl;
            cout << "atribuindo " << darkText.at(k) << endl;
            cout << "WARNING: Provavelmente não é cifra de substitução." << endl;
//            break;
        }
    }
    
    return table;
    
}

vui fileRead(string filePathIn){
    FILE *in;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
    }
    
    ui character;
    unsigned char ccharacter;
//    string read;
    
    vui v;
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
    ui type = 0;
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
    
    vui plainText = fileRead(plainTextPath);
    vui darkText = fileRead(darkTextPath);
    vui result;
    

    switch (type) {
        case 1:
            cout << endl << endl << "CRITOGRAFIA CESAR -- Chave identificada: " << decryptCesar(plainText, darkText) << endl;
            break;

        case 2:
            cout << endl << endl << "CRITOGRAFIA SUBSTITUIÇÃO -- Mapa:: " << endl;
            printUnsigedIntVector(decryptSubstitute(plainText, darkText));
            break;

        case 3:
            decryptVigenere(getOffsetOfFiles(plainText, darkText));
            break;
    }
    
    
    
    return 0;
}
