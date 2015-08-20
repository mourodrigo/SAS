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

typedef unsigned int ui;
typedef vector<ui> vui;

int printDebug = 1;

unsigned int transposeEncrypt(int in, unsigned int offset){
    return in+(offset%255);
}

void outputTransposed(vector<vui> v, string output){
    bool writeToFile = strcmp(output.c_str(), "v") ? 1 : 0;
    ofstream out;
    
    if (writeToFile)
        out.open(output, ofstream::app);
    
    for ( vector<vui>::iterator vectors = v.begin(); vectors != v.end(); ++vectors )
    {
        for ( vui::iterator ints = (*vectors).begin(); ints != (*vectors).end(); ++ ints )
        {
            if ((*ints)!=255){
                if (writeToFile) {
                        out << (unsigned char)(*ints);
                }else if (!writeToFile || printDebug){
                    cout << (unsigned char)(*ints);
                }
            }
        }
    }
    
    if (writeToFile)
        out.close();
    
    if (printDebug)
        cout << "File out done " << output << endl;
}


vector<vui> transposeFileReading(string filePathIn,unsigned int offset){
    vector<vui> v;

    FILE *in;
    
    in = fopen(filePathIn.c_str(), "rb");
    if(!in) {
        cout << "Erro: Arquivo de entrada nao encontrado " << filePathIn << endl;
    }
    
    unsigned int character;
    unsigned char ccharacter = '\0';
    
    int x=0;
    while(character!=255){
        if (x<offset) {
            vui column;
            v.push_back(column);
        }
        ccharacter = getc(in);
        character = ccharacter;
        if (printDebug) {
            cout << ccharacter << " - " << character << endl;
        }
        v.at(x%offset).push_back(ccharacter);
        x++;
    }
    return v;
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
    
    if (out.is_open() && printDebug) {
        cout << "File in open" << filePathIn << endl;
    }
    
    vector<vui> v;
    
    int x=0;
    while(character!=255){
        if (x<offset) {
            vui column;
            v.push_back(column);
        }
        ccharacter = getc(in);
        character = ccharacter;
        if (printDebug) {
            cout << ccharacter << " - " << character << endl;
        }
        v.at(x%offset).push_back(ccharacter);
        x++;
    }
    for ( vector<vui>::iterator vectors = v.begin(); vectors != v.end(); ++vectors )
    {
        for ( vui::iterator ints = (*vectors).begin(); ints != (*vectors).end(); ++ ints )
        {
            if (printDebug) {
                std::cout << (*ints) << "\n"; // print the strings
            }
            if (*ints != 255) {
                out << (unsigned char)(*ints);
            }
        }
    }

    
    out.close();

    if (printDebug) {
        cout << "File out done " << filePathOut << endl;
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << argv[0];
    if (printDebug) {
        std::cout << "CriptTransposicao!\n";
    }
    
    char option = '\0';
    string filePathIn,output;
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
                output = string(argv[3]);
                break;
            case 4:
                offset = atoi(argv[x]);
                break;
        }
    }
    
    if (option == 'c') {
        outputTransposed(transposeFileReading(filePathIn, offset), output);
    }
    if (option == 'd') {
        ifstream fileIn (filePathIn);
        string line;
        int count = 0;
        
        while( getline ( fileIn, line ) )
        {
            count += line.length();
        }
        fileIn.close();
        
        if (printDebug) {
            cout << "tamanho" << count << endl;
        }
        outputTransposed(transposeFileReading(filePathIn, count/offset), output);
    }
    
    return 0;
}
