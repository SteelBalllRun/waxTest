//
//  TDAnimationHelper.h
//  TDemo
//
//  Created by evans on 15/9/9.
//
//

#ifndef __TDemo__TDAnimationHelper__
#define __TDemo__TDAnimationHelper__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class TDAnimationHelper:public Node
{
public:
    virtual ~TDAnimationHelper();
    static TDAnimationHelper* getInstance();
    CREATE_FUNC(TDAnimationHelper);
    void loadAnimation(const std::string& animationPlist);
    void removeAnimation(std::string name);
    Animation* getFrameAnimate(std::string AnimationName);
    
private:
    virtual bool init();
    void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
};
#endif /* defined(__TDemo__TDAnimationHelper__) */
