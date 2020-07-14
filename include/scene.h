/*
 * @Author: XuanLi
 * @Date: 2020-07-13 15:54:40
 * @LastEditTime: 2020-07-13 16:10:15
 * @LastEditors: Please set LastEditors
 * @Description:
 * @FilePath: \landlord-ai\include\scene.h
 */

#ifndef SCENE_H
#define SCENE_H

/*
 * Scene:  void BeginMenu: get the begin menu
 *         void QuitGame: quit
 *         void Game: start a game
 *         void GameExplain: explain how to play the game
 *
 */
class Scene {
public:
    void BeginMenu();
    void Game();
    void QuitGame();
    void GameExplain();
private:
    int menu_choice;
};


#endif