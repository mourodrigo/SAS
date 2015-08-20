//
//  main.cpp
//  CriptVigenere
//
//  Created by Rodrigo Bueno Tomiosso on 05/08/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <strstream>

using namespace std;

string vigenereKey(string key)
{
    string newKey = key;
    for(int i = 0; i < key.size(); ++i)
    {
        if(key[i] >= 'A' && key[i] <= 'Z')
            newKey += key[i];
        else if(key[i] >= 'a' && key[i] <= 'z')
            newKey += key[i] + 'A' - 'a';
    }
    return newKey;
}

string encrypt(string text, string key)
{
    string out;
    cout << text;
    for(int i = 0, j = 0; i < text.length(); ++i)
    {
        char c = text[i];
        
        if(c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        else if(c < 'A' || c > 'Z')
            continue;
        
        out += (c + key[j] - 2*'A') % 26 + 'A';
        j = (j + 1) % key.length();
    }
    
    return out;
}

string decrypt(string text, string key)
{
    string out;
    
    for(int i = 0, j = 0; i < text.length(); ++i)
    {
        char c = text[i];
        
        if(c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        else if(c < 'A' || c > 'Z')
            continue;
        
        out += (c - key[j] + 26) % 26 + 'A';
        j = (j + 1) % key.length();
    }
    
    return out;
}

string fileRead(string filePathIn){
    FILE *in;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
    }
    
    unsigned int character;
    unsigned char ccharacter;
    string read;
    
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character <<  " - " << endl;
        read.append(string(1, (char)ccharacter));
    }
    cout << read;
    return read;
}

bool fileWrite(string filePathOut, string content){
    ofstream out;
    out.open(filePathOut, ofstream::app);
    
    if (out.is_open()) {
        cout << "\n\nFile out open\n\n" << filePathOut << endl;
        out << content;
    }
    out.close();
    return true;
}


int main(int argc, const char * argv[]) {
    std::cout << "CriptVigenere\n\n";
    
    char option = '\0';
    string filePathIn,filePathOut,key,fileInContent;
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
                key = string(argv[4]);
                break;
        }
    }
    
    key = vigenereKey(key);
    fileInContent = fileRead(filePathIn);
    
    if (option == 'c') {
        fileWrite(filePathOut, encrypt(fileInContent, key));
    }
    if (option == 'd') {
        fileWrite(filePathOut, decrypt(fileInContent, key));
    }
    std::cout << "CriptVigenere!\n";
    
    return 0;
}
