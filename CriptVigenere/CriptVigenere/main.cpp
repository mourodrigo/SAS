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

vector<unsigned char> fileRead(string filePathIn){
    FILE *in;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
    }
    
    unsigned int character;
    unsigned char ccharacter;
    vector<unsigned char> v;
    
    while(character!=255){
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character <<  " - " << endl;
        v.push_back(ccharacter);
    }
    return v;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptVigenere\n\n";
//    string key = vigenereKey("VIGENERECIPHER");
    string original = "Beware the Jabberwock, my son! The jaws that bite, the claws that catch!";
    string encrypted = encrypt(original, key);
    string decrypted = decrypt(encrypted, key);
    
    cout << encrypted;
    
    
    
    char option = '\0';
    string filePathIn,filePathOut,key;
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
    
    if (option == 'c') {
        
    }
    if (option == 'd') {
        fileManage(filePathIn,filePathOut,0-offset);
    }
    std::cout << "CriptCesar!\n";
    
    

    return 0;
}
