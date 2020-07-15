#include "scene.h"

void Scene::bgm_switch(){
    on?bgm.Pause():bgm.Play();
    on ^= 1;
}

<<<<<<< HEAD
StartScene::StartScene() {

<<<<<<< HEAD
}

void StartScene::draw() {

}

GameScene::GameScene() {

}

void GameScene::draw() {
=======
}

=======
>>>>>>> 1914137 (fix: rebuild the scene)
void StartScene::draw() {
    cleardevice();

    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);

    on = 1;
    bgm.OpenFile(bgm_path);
    bgm.Play();
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

void GameScene::draw() {
    cleardevice();

    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);

    for(int i=0;i<=54;i++){
        poke_img[i] = newimage();
        getimage(poke_img[i], poke_file[i]);
    }

    on = 1;
    bgm.OpenFile(bgm_path);
    bgm.Play();
}



void GameScene::drawCards(std::set<int> hand,std::set<int> select) {
    int n = hand.size(), i = 0;
    int pos = (1000 - 75 - 30 * n) / 2;
    for (auto it = hand.begin(); it != hand.end(); i++, it++) {
        if (select.find(*it) != select.end())
            putimage_withalpha(NULL, poke_img[(*it)], pos + i * 30, 360);
        else
            putimage_withalpha(NULL, poke_img[(*it)], pos + i * 30, 330);
    }
}

void EndScene::draw() {
    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);
}

void ExplainScene::draw() {
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> f15c3b2 (pressed)

=======
=======
    cleardevice();
>>>>>>> 9816fe7 (:bug: rebuild the scene)
    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);
>>>>>>> 1914137 (fix: rebuild the scene)
}

int EndScene::button() {
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

int ExplainScene::button() {
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
            if (x >= 650 && x <= 950) {
                if(y >= 127 && y <= 222) return 0;
                else if(y >= 257 && y <= 344) return 1;
                else if(y >= 382 && y <= 470) return 2;
            }
        }
    }
}