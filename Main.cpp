#include <thread>;
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>


<<<<<<< HEAD
auto game = std::make_unique<vizdoom::DoomGame>();
std::string path = "C:/practice/practice/vizdoom";
const unsigned int sleepTime = 1000 / vizdoom::DEFAULT_TICRATE;
auto screenBuff = cv::Mat(480, 640, CV_8UC3);


void runTask1(int episodes) {

    try {
        game->loadConfig(path + "/scenarios/task1.cfg");
       // game->setRenderWeapon(true);
       // game->setWindowVisible(true);
        game->init();
    }
    catch (vizdoom::FileDoesNotExistException e) {
        std::cout << e.what() << std::endl;
        return;
    }

    auto greyscale = cv::Mat(480, 640, CV_8UC1);
    std::vector<double> action;

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << (i + 1) << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::extractChannel(screenBuff, greyscale, 2);

            cv::threshold(greyscale, greyscale, 200, 255, cv::THRESH_BINARY);

            cv::imshow("Output Window", screenBuff);

            double reward = game->makeAction({ 0, 0, 0 });

            //std::cout << reward << " ";
            cv::waitKey(sleepTime);
        }

        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}

int main()
{
    game->setViZDoomPath(path + "/vizdoom.exe");
    game->setDoomGamePath(path + "/freedoom2.wad");

    cv::namedWindow("Output Window", cv::WINDOW_AUTOSIZE);

    auto episodes = 10;
 
    runTask1(episodes);

    game->close();
  
}
=======
int main()
{
    vizdoom::DoomGame* game = new vizdoom::DoomGame();
    try {
        std::string path = "C:\practice\practice\vizdoom";
        game->setViZDoomPath(path + "\vizdoom.exe");
        game->setDoomGamePath(path + "\freedoom2.wad");
        game->loadConfig(path + "\scenarios\basic.cfg");
        game->setRenderWeapon(true);
        game->setWindowVisible(true);
        game->init();
    }
    catch (std::exception e) {
        std:: cout << e.what() << std::endl;
        return 0;
    }
    cv::namedWindow("Control Window", cv::WINDOW_AUTOSIZE);
    auto image = cv::Mat(480, 640, CV_BACK);

    auto episodes = 10;
    unsigned int sleepTime = 1000 / vizdoom::DEFAULT_TICRATE;


    std::vector<double> actions[3];
    actions[0] = { 1, 0, 0 };
    actions[1] = { 0, 1, 0 };
    actions[2] = { 0, 0, 1 };

    for (auto i = 0; i < episodes; i++) {
        game->newEpisode();
        std::cout << "Episode #" << i << std::endl;

        auto flag1 = 30;
        auto flag2 = true;
        while (!game->isEpisodeFinished()) {

            auto gameState = game->getState();
            auto screenBuff = gameState->screenBuffer;
            image.data = screenBuff->data();

            if (flag1 > 0) {
                game->makeAction(actions[0]);
                flag1--;
            }
            else if (flag2 == true) {
                game->makeAction(actions[1]);
            }
            else {
                game->makeAction(actions[2]);
            }

            flag2 = !flag2;
            cv::waitKey(sleepTime);
        }
        std::cout << game->getTotalReward() << std::endl;
    }

    game->close();
    delete game;

}
>>>>>>> d2c2c1421828408ddbd1c1b16ce44e4787d0ccd1
