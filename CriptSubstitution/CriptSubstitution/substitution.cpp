//
//  main.cpp
//  CriptSubstitution
//
//  Created by Rodrigo Bueno Tomiosso on 06/08/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <strstream>

using namespace std;


unsigned int uints[] = {80,237,68,95,30,132,240,32,223,20,46,163,125,210,71,102,200,238,140,19,215,142,122,88,156,85,24,45,169,219,235,118,228,101,225,107,196,52,180,221,206,27,152,84,149,242,166,171,162,205,250,38,170,183,75,111,148,18,23,116,159,98,175,22,28,6,1,185,67,119,109,59,129,11,202,124,37,79,188,231,144,179,48,207,74,8,245,82,164,17,100,254,184,62,249,3,31,243,120,182,155,92,193,90,114,104,154,73,217,55,66,112,60,239,54,160,241,15,110,246,194,40,135,192,103,57,247,78,0,131,13,145,178,224,216,64,134,174,137,209,123,2,203,165,5,189,141,91,128,61,63,58,222,230,121,167,16,81,198,201,12,191,56,87,195,25,36,53,218,42,34,89,49,147,214,139,157,51,108,213,204,158,173,7,96,26,227,143,211,190,133,35,248,69,41,127,50,117,255,105,251,252,197,39,21,253,172,168,14,220,77,186,199,187,244,44,208,83,33,177,151,93,153,130,99,234,136,113,138,146,233,115,72,94,212,161,10,181,47,76,29,236,176,70,97,65,126,43,9,232,106,226,86,4,229,150};


unsigned int substitute(unsigned int ui){
    cout << "substitute " << ui << " - " << uints[ui] << endl;
    return uints[ui];
}

int decrypt(string filePathIn,string filePathOut){
    FILE *in;
    ofstream out;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
        return 0;
    }
    
    out.open(filePathOut, ofstream::app);
    
    unsigned int character;
    unsigned char ccharacter;
    
    if (out.is_open()) {
        cout << "File in open" << filePathIn << endl;
    }
    
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character << endl;
        
        std::vector<int> myvector (uints,uints+255);
        std::vector<int>::iterator it;
        
        it = find (myvector.begin(), myvector.end(), character);
        if (it != myvector.end())
            std::cout << "Element found in myvector: " << *it << '\n';
        else
            std::cout << "Element not found in myvector\n";

        
        size_t i = it - myvector.begin();
        cout << i <<endl;
        
        out << (unsigned char)i;
    }
    out.close();
    cout << "File out done" << filePathOut << endl;
    
    return true;
}


int encrypt(string filePathIn,string filePathOut){
    FILE *in;
    ofstream out;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
        return 0;
    }
    
    out.open(filePathOut, ofstream::app);
    
    unsigned int character;
    unsigned char ccharacter;
    
    if (out.is_open()) {
        cout << "File in open" << filePathIn << endl;
    }
    
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character << endl;
        out << (unsigned char)substitute(character);
    }
    out.close();
    cout << "File out done" << filePathOut << endl;
    
    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptSubstitution!\n";

    char option = '\0';
    string filePathIn,filePathOut;
    unsigned int offset = 0;
    for (int x = 1; x<argc; x++) {
        switch (x) {
            case 1:
                option = *(char*)argv[x];
                break;
            case 2:
                filePathIn = string(argv[2]);
                break;
            case 3:
                filePathOut = string(argv[3]);
                break;
            case 4:
                offset = atoi(argv[x]);
                break;
        }
    }
    
    if (option == 'c') {
        encrypt(filePathIn, filePathOut);
    }
    if (option == 'd') {
        decrypt(filePathIn, filePathOut);
    }
    
    return 0;
}
