//
//  CripTools.h
//  CriptBreaker
//
//  Created by Rodrigo Bueno Tomiosso on 09/09/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#ifndef CriptBreaker_CripTools_h
#define CriptBreaker_CripTools_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <strstream>


#define NIL 0
#define printDebug 1

#define FORCEREAD

using namespace std;

typedef unsigned int ui;
typedef vector<ui> vui;

//=======================================
#pragma mark - Std out
//=======================================


using namespace std;

void printUnsigedIntVector(vui vec);

void printCharVector(vui vec);

string stringOfCharCector(vui vec);

//=======================================
#pragma mark - File Reading
//=======================================


vui fileRead(string filePathIn);

string sfileRead(string filePathIn);
bool sfileWrite(string filePathOut, string content);
#endif
