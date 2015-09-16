//
//  main.cpp
//  CriptCesar
//
//  Created by Rodrigo Bueno Tomiosso on 29/07/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#include "CripTools.h"
#include "CriptCesar.h"

unsigned int cesarOffset(int in, unsigned int offset){
    return in+(offset%255);
}

vui cesarEncrypt(vui in,unsigned int offset){
    vui out;
    for (int x = 0; x<in.size(); x++) {
        out.push_back(cesarOffset(in.at(x), offset));
    }
    return out;
}

