#include "scene.h"

void Scene::BgmPlay() {
    bgm.Play(0);
}

void Scene::BgmPause() {
    bgm.Pause();
}

void StartScene::init() {
    img = newimage();
    getimage(img, img_file_path);

    bgm.OpenFile(bgm_path);
}

void EndScene::init() {
    img = newimage();
    getimage(img, img_file_path);

    win_img = newimage();
    getimage(win_img,win_file_path);

    lose_img = newimage();
    getimage(lose_img,lose_file_path);

    win_bgm.OpenFile(win_bgm_path);
    lose_bgm.OpenFile(lose_bgm_path);
}

void ExplainScene::init() {
    img = newimage();
    getimage(img, img_file_path);

    bgm.OpenFile(bgm_path);
}

void GameScene::init() {
    img = newimage();
    getimage(img, img_file_path);

    for(int i = 0;i <= 54;i++){
        poke_img[i] = newimage();
        getimage(poke_img[i], poke_file[i]);
    }

    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 2;j++){
            player_img[i][j] = newimage();
            getimage(player_img[i][j],player_file[i][j]);
        }

    for(int i = 0;i < 6;i++){
        button_img[i] = newimage();
        getimage(button_img[i], button_file[i]);
    }

    prepare = 1;

    bgm.OpenFile(bgm_path);
}

void StartScene::draw() {
    cleardevice();
    putimage_withalpha(NULL,img,0,0);
}

void ExplainScene::draw() {
    cleardevice();
    putimage_withalpha(NULL,img,0,0);
}

void EndScene::draw() {
    putimage_withalpha(NULL,img1,220,50);
    putimage_withalpha(NULL,img,400,430);
}

void GameScene::draw(){
    cleardevice();
    putimage_withalpha(NULL,img,0,0);
    drawButton();
    drawDeal();
    drawHand();
    drawPlayer(0);
}

void GameScene::drawPlayer(int id) {
    for(int i=0;i<3;i++) putimage_withalpha(NULL,player_img[(i+3-id)%3][i==2],posx[i],posy[i]);
}

void GameScene::drawButton() {
    if(prepare)
        for(int i=2;i<6;i++) putimage_withalpha(NULL,button_img[i],button_posx[i],button_posy[i]);
    else
        for(int i=0;i<2;i++) putimage_withalpha(NULL,button_img[i],button_posx[i],button_posy[i]);

    putimage_withalpha(NULL,poke_img[54],150,0);
    putimage_withalpha(NULL,poke_img[54],760,0);
}

void GameScene::drawDeal() {
    int pos = (1000 - 75 - 30 * deal.size()) / 2;
    for (auto it = deal.begin(); it != deal.end();it++,pos += 30)
        putimage_withalpha(NULL, poke_img[(*it)], pos, 300);

    pos=0;
    for (auto it = player1.begin(); it != player1.end();it++,pos+=30)
        putimage_withalpha(NULL, poke_img[(*it)], pos, 150);

    pos=1000-75-30*player2.size();
    for (auto it = player2.begin(); it != player2.end();it++,pos+=30)
        putimage_withalpha(NULL, poke_img[(*it)], pos, 150);
}

void GameScene::drawHand() {
    int pos = 150;
    for (auto it = hand.begin(); it != hand.end();it++,pos+=30) {
        if (select.find(*it) != select.end())
            putimage_withalpha(NULL, poke_img[(*it)], pos, 440);
        else
            putimage_withalpha(NULL, poke_img[(*it)], pos, 470);
    }
}

void GameScene::sethand(std::set<int> a){
    hand = a;
}

void GameScene::shot(){
    deal = select;
    for (auto it = select.begin(); it != select.end();it++) hand.erase(*it);
    select.clear();
}

void GameScene::pass(){
    deal.clear();
    select.clear();
}

void GameScene::choose(int num){
    int i = 1;
    for (auto it = hand.begin(); it != hand.end();it++,i++)
        if(i == num)
        {
            if(select.find(*it)!=select.end()) select.erase(*it);
            else select.insert(*it);
            break;
        }
}

void GameScene::work(int state){
    if(prepare) {
        prepare = 0;
        return;
    }
    if(state==-1) shot();
    else if(state==0) pass();
    else if(state<=hand.size()) choose(state);
}

void GameScene::shuffle() {
    std::set<int> a;
    for(int i=0;i<=5;i++) a.insert(i);
    hand = a;

    a.clear();

    deal.clear();
    player1.clear();
    player2.clear();

    for(int i=10;i<=14;i++) a.insert(i);
    player1 = a;

    a.clear();

    for(int i=20;i<=24;i++) a.insert(i);
    player2 = a;

    prepare = 1;
}

int GameScene::size(){
    return hand.size();
}

int StartScene::button() {
    while (1) {
        mouse_msg mouseMsg = getmouse();
        if (mouseMsg.is_left() && mouseMsg.is_down()) {
            int x = mouseMsg.x;
            int y = mouseMsg.y;
            if (x >= 650 && x <= 950) {
                if(y >= 127 && y <= 222) return 0;
                else if(y >= 257 && y <= 344) return 1;
                else if(y >= 382 && y <= 470) return 2;
            }
        }
    }
}

int GameScene::button() {
    while (1) {
        mouse_msg mouseMsg = getmouse();
        if (mouseMsg.is_left() && mouseMsg.is_down()) {
            int x = mouseMsg.x;
            int y = mouseMsg.y;
            int n = hand.size();
            if(prepare){
                if(y >= 400 && y <= 450){
                    if( x >= 125 && x<=255) return 0;
                    else if( x >= 335 && x <= 465) return 1;
                    else if( x >= 545 && x <= 675) return 2;
                    else if( x >= 755 && x <= 885) return 3;
                }
            }
            else{
                if(y >= 440 && y<=600 && x >= 150 && x<=225+30*n) return std::min((x-150)/30+1,n);
                else if (x >= 850 && x <= 980)
                {
                    if(y >= 470 && y<= 520) return -1;
                    else if(y>=550 && y<=600) return 0;
                }
            }
        }
    }
}

int EndScene::button() {
    while (1) {
        mouse_msg mouseMsg = getmouse();
        if (mouseMsg.is_left() && mouseMsg.is_down()) {
            int x = mouseMsg.x;
            int y = mouseMsg.y;
            if (x >= 400 && x <= 600 && y >= 430 && y<=510) return 1;
        }
    }
}

void EndScene::SetType(bool type) {
    if(type) bgm = lose_bgm, img1 = lose_img;
    else bgm = win_bgm, img1 = win_img;
}

int ExplainScene::button() {
    while (1) {
        mouse_msg mouseMsg = getmouse();
        if (mouseMsg.is_left() && mouseMsg.is_down()) {
            int x = mouseMsg.x;
            int y = mouseMsg.y;
            if (x >= 866 && x <= 962 && y >= 15 && y <= 110) return 1;
        }
    }
}