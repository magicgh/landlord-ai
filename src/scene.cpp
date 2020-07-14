#include "scene.h"


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
    img = newimage();
    getimage(img, img_file_path);
    PlaySound(TEXT("static\\start.wav"),NULL,SND_FILENAME | SND_ASYNC);
    putimage_withalpha(NULL,img,0,0);
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
                else if(x >= 382 && x <= 470) return 2;
            }
        }
    }
}

void GameScene::draw() {
    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);
}


void EndScene::draw() {
    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);
}

void ExplainScene::draw() {
<<<<<<< HEAD
>>>>>>> f15c3b2 (pressed)

=======
    img = newimage();
    getimage(img, img_file_path);
    putimage_withalpha(NULL,img,0,0);
>>>>>>> 1914137 (fix: rebuild the scene)
}
