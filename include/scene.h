//
// Created by magicgh on 7/14/2020.
//

#pragma once


class Scene{
protected:
public:
    Scene() = default;
    ~Scene() = default;

    virtual void draw()=0;
};

class StartScene : public Scene {
public:
    StartScene();

    void draw() override;
};

class GameScene : public Scene {
public:
    GameScene();

    void draw() override;
};

class EndScene : public Scene {
public:
    EndScene();

    void draw() override;

    void restart();
};

class ExplainScene : public Scene {
public:
    ExplainScene();

    void draw() override;

};
