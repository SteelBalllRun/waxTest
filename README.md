# waxTest
Private test  data for wax loader

CCDirector.h
/**
     *  可设置动画的推出转场
     *
     *  @param t 动画时间
     */
    template <class T>
    void popSceneWithTransition(float t)
    {
        CCASSERT(_runningScene != nullptr, "running scene should not null");
        _scenesStack.popBack();
        ssize_t c = _scenesStack.size();
        if (c == 0) {
            end();
        }else
        {
            _sendCleanupToScene = true;
            Scene* scene = T::create(t, _scenesStack.at(c-1));
            _scenesStack.replace(c-1, scene);
            _nextScene = scene;
        }
    };
