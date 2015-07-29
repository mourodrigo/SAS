//
//  main.cpp
//  CriptCesar
//
//  Created by Rodrigo Bueno Tomiosso on 29/07/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

unsigned int cesarEncrypt(int in, unsigned int offset){
    return in+(offset%255);
}

int fileManage(char option,string filePathIn,string filePathOut,unsigned int offset){
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
        cout << "open";
    }
    
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character <<  " - " << character+offset<< endl;
        out << (unsigned char)cesarEncrypt(character, offset);
    }
    out.close();
    return true;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptCesar!\n";

    
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
        fileManage(option,filePathIn,filePathOut,offset);
    }
    if (option == 'd') {
        fileManage(option,filePathIn,filePathOut,0-offset);
    }
    std::cout << "CriptCesar!\n";


    
    return 0;
}
