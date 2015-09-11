//
//  TDAnimationHelper.cpp
//  TDemo
//
//  Created by evans on 15/9/9.
//
//
#include <regex.h>
#include "TDAnimationHelper.h"

static TDAnimationHelper *_sharedAnimationHelper = nullptr;
TDAnimationHelper* TDAnimationHelper::getInstance()
{
    if (! _sharedAnimationHelper)
    {
        _sharedAnimationHelper = new (std::nothrow) TDAnimationHelper();
        _sharedAnimationHelper->init();
    }
    
    return _sharedAnimationHelper;
}

TDAnimationHelper::~TDAnimationHelper()
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("res/JYTextures.plist");
}

bool TDAnimationHelper::init()
{
    if (!Node::init()) {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/JYTextures.plist", "res/JYTextures.pvr.ccz");
    return true;
}

void TDAnimationHelper::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


void TDAnimationHelper::loadAnimation(const std::string &animationPlist)
{
    
    __Dictionary *dic = __Dictionary::createWithContentsOfFile(animationPlist.c_str());
    
    DictElement* pElement;
    CCDICT_FOREACH(dic, pElement)
    {
        const char* key = pElement->getStrKey();
        const char* range = dic->valueForKey(key)->getCString();

        std::vector<std::string> vector = std::vector<std::string>();
        this->SplitString(range, vector, "_");
        Animation *animation = Animation::create();
        
        int begin = atoi(vector[0].c_str());
        int finished = atoi(vector[1].c_str());
        
        for (int i = begin; i <= finished ; i ++) {
            char* frame_name = new char[20]();
            sprintf(frame_name, "%d-1.png",i);
            animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name));
            CC_SAFE_DELETE(frame_name);
        }
        animation->setDelayPerUnit(1.0f/60.0f);
        animation->setRestoreOriginalFrame(false);
        AnimationCache::getInstance()->addAnimation(animation, key);
    }
}

void TDAnimationHelper::removeAnimation(std::string name)
{
    AnimationCache::getInstance()->removeAnimation(name);
}

Animation* TDAnimationHelper::getFrameAnimate(std::string AnimationName)
{
    return AnimationCache::getInstance()->getAnimation(AnimationName);
}
