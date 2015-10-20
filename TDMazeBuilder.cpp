//
//  TDMazeBuilder.cpp
//  TDemo
//
//  Created by 舒 方昊 on 15/10/18.
//
//

#include "TDMazeBuilder.h"

#define MAZE_MARK_ROAD     1
#define MAZE_MARK_WALL     8

//加入栈中，push到下一位.
#define MAZE_GONEXT_MARK(DIR,DIRENABLE) \
if ((DIRENABLE & DIR) > 0) {\
int offset= (int)log2f(DIRENABLE & DIR);\
int p_x = direction[MAX(0, offset-1)][0] + p.x;\
int p_y = direction[MAX(0, offset-1)][1] + p.y;\
Point np = Point(p_x, p_y);\
int w_x = (int)((p.x + np.x)/2);\
int w_y = (int)((p.y + np.y)/2);\
Point wall_p = Point(w_x, w_y);\
maze->markMazeWithCenterValueAndRoundValue(wall_p, MAZE_MARK_ROAD, MAZE_MARK_WALL);\
DIRENABLE = DIRENABLE & ~(DIR);\
if (DIRENABLE == 0) {\
DIRENABLE = MAZE_DIRECTION_NONE;\
}\
maze->markMazeDirectionValue(p, DIRENABLE);\
if (maze->getMazeDirectionValue(np) == MAZE_DIRECTION_NEW) {\
locationStack.push(np);\
}\
continue;\
}\

/*
 迷宫是个矩形区域
 墙会占用地图格
 墙和路是相隔的
 
 这里制作的地图迷宫默认为边界起点
 */
const static int direction[4][2] = {{0,2},{0,-2},{-2,0},{2,0}};

TDMaze* TDMazeBuidler::buildMazeWithType(TDMazeBuildTtype type, Point startLocation)
{
    TDMaze* maze = TDMaze::create();
    if (maze) {
        std::stack<Point> locationStack = std::stack<Point>();
        
        Point p = startLocation;
        //TODO:1.起点当作当前格并标记
        bool startIsLegal = maze->setBeginLocation(p);
        if (!startIsLegal) {
            return NULL;
        }
        locationStack.push(p);
        while (!locationStack.empty()) {
            //2.当还存在未标记的格时
            //2.1如果当前格有未标记的邻格：随机选择一个未标记的邻格／将当前格入栈／移除当前格与邻格的墙／标记邻格并用它当作当前格
            
            //2.2如果栈不空:栈顶个字出栈／令其成为当前格子
            //3. 反之，选择一个格子为当前格并标记
            p = locationStack.top();
            int direction_satus = maze->getMazeDirectionValue(p);
            
            if (direction_satus == MAZE_DIRECTION_NEW) {
                maze->markMazeWithCenterValueAndRoundValue(p, MAZE_MARK_ROAD, MAZE_MARK_WALL);
                //未处理过，检索周围可用点
                bool flag = false;
                int new_dir_status = maze->getMazeDirectionValue(p);
                for (int i = 0; i < 4; i++) {
                    Point q = Point(p.x + direction[i][0], p.y + direction[i][1]);
                    if (!maze->isInLegalRange(q) || !(maze->getMazeValue(q)==0)) {
                        new_dir_status = new_dir_status | 1;
                        continue;
                    }
                    flag = true;
                    new_dir_status = (new_dir_status | (1<<(i+1)));
                }
                if (flag) {
                    new_dir_status = new_dir_status &(~1);  //掩码清掉低位
                }else
                {
                    new_dir_status = MAZE_DIRECTION_NONE;
                }
                maze->markMazeDirectionValue(p,new_dir_status);
            }
            direction_satus = maze->getMazeDirectionValue(p);
            if (direction_satus == MAZE_DIRECTION_NONE)
            {
                //周围没有可用点
                maze->markMazeWithValue(p, MAZE_MARK_ROAD);
                locationStack.pop();
                continue;
            }else if (direction_satus > MAZE_DIRECTION_NONE)
            {
                //周围有可用点
                int shuffle_direction[4] = {1,2,3,4};
                int i_1 = arc4random()%4;
                int i_2 = arc4random()%4;
                shuffle_direction[i_2] = shuffle_direction[i_1] + shuffle_direction[i_2];
                shuffle_direction[i_1] = shuffle_direction[i_2] - shuffle_direction[i_1];
                shuffle_direction[i_2] = shuffle_direction[i_2] - shuffle_direction[i_1];
                
                for (int index = 0; index < 4; ++ index) {
                    MAZE_GONEXT_MARK(1<<shuffle_direction[index],direction_satus);
                }
            }else
            {
                locationStack.pop();
                continue;
            }
        }
    }
    return maze;
}


