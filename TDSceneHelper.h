//
//  TDSceneHelper.h
//  TDemo
//
//  Created by evans on 15/10/12.
//
//

#ifndef __TDemo__TDSceneHelper__
#define __TDemo__TDSceneHelper__

#define TD_SCENE_HELPER_KEY     "sh_xib"

#define TD_SCENE_HELPER_PUSH_SECENE(NAME,CLASS_NAME) \
 do{\
        Scene *scene = Scene::create();\
        CLASS_NAME* view = CLASS_NAME::create();\
        scene->addChild(view);\
        TMXTiledMap* mapInfo = TMXTiledMap::create(NAME);\
        view->addChild(mapInfo,-1,TD_SCENE_HELPER_KEY);\
        Director::getInstance()->pushScene(scene);\
    }while(false);

#define TD_SCENE_HELPER_PUSH_SECENE_1(NAME) \
do{\
Scene *scene = Scene::create();\
Layer* view = Layer::create();\
scene->addChild(view);\
TMXTiledMap* mapInfo = TMXTiledMap::create(NAME);\
view->addChild(mapInfo,-1,TD_SCENE_HELPER_KEY);\
Director::getInstance()->pushScene(scene);\
}while(false);

#define TD_SCENE_HELPER_PUSH_SECENE_2(NAME,CLASS_NAME,TRANSITION) \
do{\
Scene *scene = Scene::create();\
CLASS_NAME* view = CLASS_NAME::create();\
scene->addChild(view);\
TMXTiledMap* mapInfo = TMXTiledMap::create(NAME);\
view->addChild(mapInfo,-1,TD_SCENE_HELPER_KEY);\
TRANSITION* trans = TRANSITION::create(0.3f, scene);\
\
Director::getInstance()->pushScene(trans);\
}while(false);


#define TD_SCENE_HELPER_POP_SECENE(TRANSITION) \
do{\
Director::getInstance()->popSceneWithTransition<TRANSITION>(0.3f);\
}while(false);

#define TD_SCENE_HELPER_BIND_OBJ(REF,SCENE,GROUP_NAME,OBJ_NAME) \
do{\
    Layer* root_node =dynamic_cast<Layer*>(SCENE->getChildren().at(0));\
    TMXTiledMap* mapInfo;\
if (SCENE->getChildByName(TD_SCENE_HELPER_KEY)) {\
        mapInfo = dynamic_cast<TMXTiledMap*>(SCENE->getChildByName(TD_SCENE_HELPER_KEY));\
    }else\
    {\
        mapInfo = dynamic_cast<TMXTiledMap*>(root_node->getChildByName(TD_SCENE_HELPER_KEY));\
    }\
    TMXObjectGroup* objGroup = mapInfo->getObjectGroup(GROUP_NAME);\
    REF = objGroup->getObject(OBJ_NAME);\
}while(false);

#endif /* defined(__TDemo__TDSceneHelper__) */
