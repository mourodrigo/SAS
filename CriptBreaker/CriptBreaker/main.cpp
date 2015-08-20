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

int printDebug = 1;



//=======================================
#pragma mark - Std out
//=======================================


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

void printCharVector(vui vec){
    for ( vui::iterator ints = (vec).begin(); ints != (vec).end(); ++ ints )
    {
        if ((*ints)!=NIL)
            cout << (char)(*ints);
    }
}

string stringOfCharCector(vui vec){
    string str;
    for ( vui::iterator ints = (vec).begin(); ints != (vec).end(); ++ ints )
    {
        if ((*ints)!=NIL) {
            if (*ints!=vec.at(vec.size()-1)) {
            str = str + (char)(*ints);
          }
        }
    }
    return str;
}


//=======================================
#pragma mark - Vigenere
//=======================================
vui decryptVigenere(vui offsetVector){
    vui result;

    for (int t=0; t< offsetVector.size();t++){
        vui::iterator it = find(result.begin(), result.end(), offsetVector.at(t));

        if (it==result.end()) {
            result.push_back(offsetVector.at(t));
        }else{
            break;
        }
        
    }
    
    for (int s = 0; s<result.size(); s++) {
        cout << (char)result.at(s);
    }
    
    return result;
}

vui getOffsetOfFiles(vui plainText, vui darkText){
    vui table;
    for (int h=0; h<darkText.size()&&h<plainText.size(); h++) {
        table.push_back((unsigned int)((darkText.at(h)-plainText.at(h))%256));
    }
    return table;
}

//=======================================
#pragma mark - Cesar
//=======================================
int decryptCesar(vui plainText, vui darkText){
    int offset=0,assert=0;
    for (int h=0; h<darkText.size()||h<plainText.size()||1; h++) {
        if (h==0) {
            offset=(int)plainText.at(h)-(int)darkText.at(h);
        }else if (offset==(int)plainText.at(h)-(int)darkText.at(h)) {
            assert++;
        }else if (offset!=(int)plainText.at(h)-(int)darkText.at(h)){ //rever
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

//=======================================
#pragma mark - Substitute
//=======================================

vui decryptSubstitute(vui plainText, vui darkText){
    
    vui table (256,NIL);
    for (int k=0; k<plainText.size(); k++) {
        if (table[(int)plainText.at(k)]==NIL) {
            table[(int)plainText.at(k)] = darkText.at(k);
            
        }else if(table[(int)plainText.at(k)]!=darkText.at(k)){
            cout << "table.at(plainText.at("<<k<<")) == " << table.at(plainText.at(k)) << endl;
            cout << "atribuindo " << darkText.at(k) << endl;
            cout << "WARNING: Provavelmente não é cifra de substitução." << endl;
        }
    }
    
    return table;
    
}

//=======================================
#pragma mark - Transpose
//=======================================

std::string exec(string cmd) {
    
    FILE* pipe = popen((char*)cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

void decryptTranspose(vui plainText, vui darkText, string outFilePath){
    string execFile = "./CriptTransposicao";
    int bruteForceIndex = 1;
    string plainTextString = stringOfCharCector(plainText);
    while (true) {
        string execStr = "cd /Users/mourodrigo/Developer/SAS/CriptBreaker/CriptBreaker;"+execFile+" d " + outFilePath + " v "+to_string(++bruteForceIndex);
        string execReturn = exec(execStr);
        execReturn.replace(execReturn.begin(),execReturn.begin()+execFile.length(),"");
        if (strcmp(execReturn.c_str(), plainTextString.c_str())==0)
            break;
        if (printDebug) {
            cout << execStr << endl;
            cout << execReturn << " tamanho " << execReturn.length() <<endl;
//            cout << plainTextString  << " tamanho " << plainTextString.length() << endl<<endl;
        }
    }
    
    cout <<  "CHAVE DE TRANSPOSIÇÃO " << bruteForceIndex;
    
}

//=======================================
#pragma mark - File Reading
//=======================================


vui fileRead(string filePathIn){
    FILE *in;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo nao encontrado " << filePathIn << endl;
    }
    
    ui character;
    unsigned char ccharacter;
    
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
            cout << endl << endl << "CRITOGRAFIA SUBSTITUIÇÃO -- Mapa: " << endl;
            printUnsigedIntVector(decryptSubstitute(plainText, darkText));
            break;

        case 3:
            cout << endl << endl << "CRITOGRAFIA Vigenere -- Chave: " << endl;
            decryptVigenere(getOffsetOfFiles(plainText, darkText));
            
            break;
        case 4:
            decryptTranspose(plainText, darkText, darkTextPath);
            break;
            
    }
    
    
    
    return 0;
}
