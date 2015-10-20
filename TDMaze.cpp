//
//  TDMaze.cpp
//  TDemo
//
//  Created by 舒 方昊 on 15/10/18.
//
//

#include "TDMaze.h"
const static int round_direction[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

TDMaze::TDMaze()
{
    width = MAZE_WIDTH;
    height = MAZE_HEIGHT;
    mapDetail = new Vec2*[height];
    for (int i = 0; i < height; i++) {
        mapDetail[i] = new Vec2[width];
        for (int j = 0; j < width; j++) {
            mapDetail[i][j] = Point();
        }
    }
}

TDMaze::~TDMaze()
{
    delete [] mapDetail;
    mapDetail = NULL;
    width = 0;
    height = 0;
    beginLocation = Point(0,0);
    targetLocation = Point(0,0);
}

bool TDMaze::init()
{
    if (this && Node::init()) {
        return true;
    }
    return false;
}

bool TDMaze::setBeginLocation(Point _beginLocation)
{
    if (isInLegalRange(_beginLocation)) {
        beginLocation = _beginLocation;
        return true;
    }
    return false;
}

bool TDMaze::isInLegalRange(Point location)
{
    bool result = false;
    if (location.x < MAZE_WIDTH && location.x >= 0 && location.y < MAZE_HEIGHT && location.y >= 0) {
        result = true;
    }
    return result;
}

bool TDMaze::markMazeWithValue(Point position, int value)
{
    if (isInLegalRange(position)) {
        mapDetail[(int)position.y][(int)position.x].x = value;
        return true;
    }
    return false;
}

void TDMaze::markMazeWithCenterValueAndRoundValue(Point position, int c_value, int r_value)
{
    this->markMazeWithValue(position, c_value);
    for (int i = 0 ; i < 4; ++i) {
        Point n_p = Point(position.x+ round_direction[i][0],position.y + round_direction[i][1]);
        if (getMazeValue(n_p) == 0) {
            this->markMazeWithValue(n_p, r_value);
        }
    }
}

void TDMaze::markMazeDirectionValue(Point position, int direction_value)
{
    if (direction_value>1 && direction_value%2>0) {
        CCLOG("!!!!");
    }
    if (isInLegalRange(position)) {
        mapDetail[(int)position.y][(int)position.x].y = direction_value;
    }
}

bool TDMaze::getMazeWalkEnable(int x, int y)
{
    if (mapDetail && isInLegalRange(Point(x, y))){
        return mapDetail[y][x].x==1;
    }else{
        return false;
    }
}

int TDMaze::getMazeValue(Point position)
{
    if (isInLegalRange(position)) {
        return mapDetail[(int)position.y][(int)position.x].x;
    }
    return -1;
}

int TDMaze::getMazeDirectionValue(Point position)
{
    if (isInLegalRange(position)) {
        return mapDetail[(int)position.y][(int)position.x].y;
    }
    return -1;
}

void TDMaze::printMazeMap()
{
    printf("======================\n");
    for (int i = 0; i < MAZE_HEIGHT; ++i) {
        for (int j = 0; j < MAZE_WIDTH; ++j) {
            printf(" %d ",(int)mapDetail[i][j].x);
        }
        printf("\n");
    }
    printf("======================\n");
}
