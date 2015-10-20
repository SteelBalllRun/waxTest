//
//  TDMazeBuilder.h
//  TDemo
//
//  Created by 舒 方昊 on 15/10/18.
//
//

#ifndef __TDemo__TDMazeBuilder__
#define __TDemo__TDMazeBuilder__

#include <stdio.h>
#include "cocos2d.h"
#include "TDMaze.h"

typedef enum
{
    TDMazeDFSTYPE,
    TDMazePrimTYPE,
    TDMazeClipTYPE
}TDMazeBuildTtype;

USING_NS_CC;
class TDMazeBuidler:Node {
public:
    static TDMaze* buildMazeWithType(TDMazeBuildTtype type, Point startLocation);
};

#endif /* defined(__TDemo__TDMazeBuilder__) */
