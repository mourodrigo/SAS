//
//  CriptTools.cpp
//  CriptBreaker
//
//  Created by Rodrigo Bueno Tomiosso on 09/09/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//


#ifndef CriptBreaker_CripTools_h
    #include "CripTools.h"
#endif

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
#pragma mark - File Managing
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

string sfileRead(string filePathIn){
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

bool sfileWrite(string filePathOut, string content){
    ofstream out;
    out.open(filePathOut, ofstream::app);
    
    if (out.is_open()) {
        cout << "\n\nFile out open\n\n" << filePathOut << endl;
        out << content;
    }
    out.close();
    return true;
}

