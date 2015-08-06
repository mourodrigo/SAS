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


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptVigenere\n\n";
    string key = vigenereKey("VIGENERECIPHER");
    string original = "Beware the Jabberwock, my son! The jaws that bite, the claws that catch!";
    string encrypted = encrypt(original, key);
    string decrypted = decrypt(encrypted, key);
    
    cout << encrypted;
    
    return 0;
}
