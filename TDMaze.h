//
//  TDMaze.h
//  TDemo
//
//  Created by 舒 方昊 on 15/10/18.
//
//

#ifndef __TDemo__TDMaze__
#define __TDemo__TDMaze__

#include <stdio.h>
#include "cocos2d.h"
#include "TDDefine.h"

USING_NS_CC;

typedef enum
{
    MAZE_DIRECTION_NEW      = 0,
    MAZE_DIRECTION_NONE     = 1,
    MAZE_DIRECTION_UP       = 1<<1,
    MAZE_DIRECTION_DOWN     = 1<<2,
    MAZE_DIRECTION_LEFT     = 1<<3,
    MAZE_DIRECTION_RIGHT    = 1<<4
}MAZE_DIRECTION_MARK;

class TDMaze:Node {
    
    int width;
    int height;
    Point beginLocation;
    Point targetLocation;
    Vec2 **mapDetail;
public:
    TDMaze();
    virtual ~TDMaze();
    virtual bool init();
    CREATE_FUNC(TDMaze);
    bool isInLegalRange(Point location);
    bool setBeginLocation(Point _beginLocation);

    bool markMazeWithValue(Point position,int value);
    void markMazeWithCenterValueAndRoundValue(Point position, int c_value,int r_value);
    void markMazeDirectionValue(Point position,int direction_value);
    //当超出范围时返回-1
    int getMazeValue(Point position);
    int getMazeDirectionValue(Point position);
    void printMazeMap();
    
    bool getMazeWalkEnable(int x, int y);
};

#endif /* defined(__TDemo__TDMaze__) */
