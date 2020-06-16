#include <thread>;
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>


using namespace vizdoom;
using namespace cv;
using namespace std;


int main()
{
    DoomGame* game = new DoomGame();
    try {
        string path = "C:\practice\practice\vizdoom";
        game->setViZDoomPath(path + "\vizdoom.exe");
        game->setDoomGamePath(path + "\freedoom2.wad");
        game->loadConfig(path + "\scenarios\basic.cfg");
        game->setRenderWeapon(true);
        game->setWindowVisible(true);
        game->init();
    }
    catch (exception e) {
        cout << e.what() << endl;
        return 0;
    }
    namedWindow("Control Window", WINDOW_AUTOSIZE);
    auto image = Mat(480, 640, CV_BACK);

    auto episodes = 10;
    unsigned int sleepTime = 1000 / DEFAULT_TICRATE;


    std::vector<double> actions[3];
    actions[0] = { 1, 0, 0 };
    actions[1] = { 0, 1, 0 };
    actions[2] = { 0, 0, 1 };

    for (auto i = 0; i < episodes; i++) {
        game->newEpisode();
        cout << "Episode #" << i << endl;

        auto flag1 = 30;
        auto flag2 = true;
        while (!game->isEpisodeFinished()) {

            auto gameState = game->getState();
            auto screenBuff = gameState->screenBuffer;
            image.data = screenBuff->data();

            if (flag1 > 0) {
                game->makeAction(actions[0]);
                flag1--;
            } else if (flag2 == true) {
                game->makeAction(actions[1]);
            } else {
                game->makeAction(actions[2]);
            }

            flag2 = !flag2;
            waitKey(sleepTime);
        }
        cout << game->getTotalReward() << endl;
    }

    game->close();
    delete game;

}
