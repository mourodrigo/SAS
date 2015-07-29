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

using namespace std;

int encrypt(char option,string filePathIn,string filePathOut,int offset){
    FILE *in, *out;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        printf("Erro: Arquivo de entrada nao encontrado\n");
        return 0;
    }

    out = fopen(filePathOut.c_str(), "wb");
    
    unsigned int character;
    unsigned char ccharacter;
    
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character << endl;
     }
    return true;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptCesar!\n";

    
    char option = '\0';
    string filePathIn,filePathOut;
    int offset = 0;
    for (int x = 1; x<argc; x++) {
        switch (x) {
            case 1:
                option = *(char*)argv[x];
            break;
            case 2:
                filePathIn = string(argv[2]);
            break;
            case 3:
                filePathOut = string(argv[2]);
                break;
            case 4:
                offset = *(char*)argv[x];
            break;
        }
    }
    
    if (option == 'c') {
        encrypt(option,filePathIn,filePathOut,offset);
    }
    
    std::cout << "CriptCesar!\n";


    
    return 0;
}
