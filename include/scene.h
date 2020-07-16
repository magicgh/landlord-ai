#pragma once
#include<graphics.h>
#include<set>

class Scene{
    friend class Game;
protected:
    PIMAGE img;
    MUSIC bgm;
public:
    Scene() = default;
    ~Scene() = default;
    void BgmPlay();
    void BgmPause();
    virtual void init()=0;
    virtual void draw()=0;
    virtual int button()=0;
};

class StartScene : public Scene {
private:
    const char *img_file_path = "static\\start_scene.png";
    const char *bgm_path = "static\\bgm1.mp3";
public:
    StartScene() = default;

    void init() override;

    void draw() override;

    int button() override;
};

class GameScene : public Scene {
private:
    const char *img_file_path = "static\\game_scene.png";
    const char *bgm_path = "static\\bgm3.mp3";
    PIMAGE poke_img[55],player_img[3][2],button_img[6];
    const char *player_file[3][2] = {
            {"static\\landlord.png","static\\landlord_reverse.png"},
            {"static\\farmer1.png","static\\farmer1_reverse.png"},
            {"static\\farmer2.png","static\\farmer2_reverse.png"}
    };
    const char *button_file[6] = {"static\\shot.png","static\\pass.png","static\\score_0.png",
                                  "static\\score_1.png","static\\score_2.png","static\\score_3.png"};
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
    std::set<int> hand,select,player[3];
    bool status;
    int posx[3] = {0,0,880};
    int posy[3] = {470,0,0};
    int button_posx[6]={850,850,125,335,545,755};
    int button_posy[6]={470,550,400,400,400,400};
    int order;
public:
    GameScene() = default;

    void sethand(std::set<int> a);

    void setselect(std::set<int> a);

    void setdeal(std::set<int> a,std::set<int> b,std::set<int> c);

    void drawPlayer();

    void drawButton();

    void drawHand();

    void drawDeal();

    void Order(int a);

    void ready();

    void begin();

    void init() override;

    void draw() override;

    int button() override;
};

class EndScene : public Scene {
private:
    PIMAGE win_img,lose_img,img1;
    MUSIC win_bgm,lose_bgm;

    const char *img_file_path = "static\\new_game.png";
    const char *win_file_path = "static\\win.png";
    const char *lose_file_path = "static\\lose.png";

    const char *win_bgm_path = "static\\end_win.mp3";
    const char *lose_bgm_path = "static\\end_lose.mp3";
public:
    EndScene() = default;

    void init() override;

    void draw() override;

    int button() override;

    void SetType(bool type);
};

class ExplainScene : public Scene {
private:
    const char *img_file_path = "static\\rule.png";
    const char *bgm_path = "static\\bgm2.mp3";
public:
    ExplainScene() = default;

    void init() override;

    void draw() override;

    int button() override;
};
