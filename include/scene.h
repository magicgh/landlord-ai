#pragma once
#include<graphics.h>
#include<set>

class Scene{
protected:
    PIMAGE img;
    MUSIC bgm;
    bool on;
public:
    Scene() = default;
    ~Scene() = default;
    virtual void draw()=0;
    virtual int button()=0;
    void bgm_switch();
};

class StartScene : public Scene {
private:
    const char *img_file_path = "static\\start_scene.png";
    const char *bgm_path = "static\\bgm1.mp3";
public:
    StartScene() = default;

    void draw() override;

    int button() override;
};

class GameScene : public Scene {
private:
    const char *img_file_path = "static\\game_scene.png";
    const char *bgm_path = "static\\bgm2.mp3";
    PIMAGE poke_img[55];
    const char *poke_file[55] = {
            "static\\poker\\0.png","static\\poker\\1.png","static\\poker\\2.png","static\\poker\\3.png",
            "static\\poker\\4.png","static\\poker\\5.png","static\\poker\\6.png","static\\poker\\7.png",
            "static\\poker\\8.png","static\\poker\\9.png","static\\poker\\10.png","static\\poker\\11.png",
            "static\\poker\\12.png","static\\poker\\13.png","static\\poker\\14.png","static\\poker\\15.png",
            "static\\poker\\16.png","static\\poker\\17.png","static\\poker\\18.png","static\\poker\\19.png",
            "static\\poker\\20.png","static\\poker\\21.png","static\\poker\\22.png","static\\poker\\23.png",
            "static\\poker\\24.png","static\\poker\\25.png","static\\poker\\26.png","static\\poker\\27.png",
            "static\\poker\\28.png","static\\poker\\29.png","static\\poker\\30.png","static\\poker\\31.png",
            "static\\poker\\32.png","static\\poker\\33.png","static\\poker\\34.png","static\\poker\\35.png",
            "static\\poker\\36.png","static\\poker\\37.png","static\\poker\\38.png","static\\poker\\39.png",
            "static\\poker\\40.png","static\\poker\\41.png","static\\poker\\42.png","static\\poker\\43.png",
            "static\\poker\\44.png","static\\poker\\45.png","static\\poker\\46.png","static\\poker\\47.png",
            "static\\poker\\48.png","static\\poker\\49.png","static\\poker\\50.png","static\\poker\\51.png",
            "static\\poker\\52.png","static\\poker\\53.png","static\\poker\\54.png"
    };
public:
    GameScene() = default;

    void drawCards(std::set<int> hand,std::set<int> select);

    void draw() override;

    int button() override;
};

class EndScene : public Scene {
private:
    const char *img_file_path = "static\\lose.png";
public:
    EndScene() = default;

    void draw() override;

    void restart();

    int button() override;
};

class ExplainScene : public Scene {
private:
    const char *img_file_path = "static\\rule.png";
public:
    ExplainScene() = default;

    void draw() override;

    int button() override;
};
