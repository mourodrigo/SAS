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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "CriptCesar!\n";

    
    char option;
    string file;
    int offset;
    for (int x = 1; x<argc; x++) {
        switch (x) {
            case 1:
                option = *(char*)argv[x];
            break;
            case 2:
                file = string(argv[2]);
            break;
            case 3:
                offset = *(char*)argv[x];
            break;
        }
    }
    
    
    
    std::cout << "CriptCesar!\n";


    
    return 0;
}
