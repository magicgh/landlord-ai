#pragma once
#include<graphics.h>

class Scene{
protected:
public:
    Scene() = default;
    ~Scene() = default;
    virtual void draw()=0;
    virtual int button() const{return 0;};
};

class StartScene : public Scene {
private:
    const char *img_file_path = "static\\start_scene.png";
    PIMAGE img;
public:
    StartScene() = default;

    void draw() override;

    int button();
};

class GameScene : public Scene {
private:
    const char *img_file_path = "static\\game_scene.png";
    PIMAGE img;
public:
    GameScene() = default;

    void draw() override;

    int button();
};

class EndScene : public Scene {
private:
    const char *img_file_path = "static\\end_scene.png";
    PIMAGE img;
public:
    EndScene() = default;

    void draw() override;

    void restart();

    int button();
};

class ExplainScene : public Scene {
private:
    const char *img_file_path = "static\\start_scene.png";
    PIMAGE img;
public:
    ExplainScene() = default;

    void draw() override;

    int button();
};
