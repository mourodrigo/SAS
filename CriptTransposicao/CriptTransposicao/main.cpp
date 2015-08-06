//
//  main.cpp
//  CriptTransposicao
//
//  Created by Rodrigo Bueno Tomiosso on 29/07/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

unsigned int transposeEncrypt(int in, unsigned int offset){
    return in+(offset%255);
}

int fileManage(string filePathIn,string filePathOut,unsigned int offset){
    FILE *in;
    ofstream out;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
        return 0;
    }
    
    out.open(filePathOut, ofstream::app);
    
    unsigned int character;
    unsigned char ccharacter = '\0';
    
    if (out.is_open()) {
        cout << "File in open" << filePathIn << endl;
    }
    
    vector<vector<unsigned int>> v;
    
    
    int x=0;
    while(character!=255){
        if (x<offset) {
            vector<unsigned int> column;
            v.push_back(column);
        }
        ccharacter = getc(in);
        character = ccharacter;
        cout << ccharacter << " - " << character << endl;
        v.at(x%offset).push_back(ccharacter);
        x++;
    }
    for ( vector<vector<unsigned int>>::iterator vectors = v.begin(); vectors != v.end(); ++vectors )
    {
        for ( vector<unsigned int>::iterator ints = (*vectors).begin(); ints != (*vectors).end(); ++ ints )
        {
            
            std::cout << (*ints) << "\n"; // print the strings
            if (*ints != 255) {
                out << (unsigned char)(*ints);
            }
        }
    }

    
    out.close();
    cout << "File out done " << filePathOut << endl;

    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptTransposicao!\n";
    
    
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
        fileManage(filePathIn,filePathOut,offset);
    }
    if (option == 'd') {
        ifstream fileIn (filePathIn);
        string line;
        int count = 0;
        
        while( getline ( fileIn, line ) )
        {
            cout << line << endl;
            count += line.length();
        }
        fileIn.close();
        
        cout << "tamanho" << count << endl;

        fileManage(filePathIn,filePathOut,count/offset);
    }
    std::cout << "CriptCesar!\n";
    
    
    
    return 0;
}
