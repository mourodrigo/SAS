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

int encrypt(char option,string filePath,int offset){
    FILE *in;
    
    in = fopen(filePath.c_str(), "rb");
    if(!in) {
        printf("Erro: Arquivo de entrada n„o encontrado\n");
        return 0;
    }
    
    unsigned char character;
    
    while(true){
        character = getc(in);
        cout << character << endl;
    }
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptCesar!\n";

    
    char option;
    string filePath;
    int offset;
    for (int x = 1; x<argc; x++) {
        switch (x) {
            case 1:
                option = *(char*)argv[x];
            break;
            case 2:
                filePath = string(argv[2]);
            break;
            case 3:
                offset = *(char*)argv[x];
            break;
        }
    }
    
    if (option == 'c') {
        encrypt(option, filePath, offset);
    }
    
    std::cout << "CriptCesar!\n";


    
    return 0;
}
