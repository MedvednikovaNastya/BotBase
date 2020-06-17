<<<<<<< HEAD
=======
#include <thread>;
>>>>>>> d47293430cb762a6215380645ae403d11eba61f3
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>


<<<<<<< HEAD
std::string path = "C:/Users/Àíàñòàñèÿ/mine/Ñåññèÿ/practice/practice/vizdoom";
auto game = std::make_unique<vizdoom::DoomGame>();
const unsigned int sleepTime = 1000 / vizdoom::DEFAULT_TICRATE;
auto screenBuff = cv::Mat(480, 640, CV_8UC3);

void RunTask1(int episodes)
{
    try
    {
        game->loadConfig(path + "/scenarios/task1.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    auto greyscale = cv::Mat(480, 640, CV_8UC1);

=======
auto game = std::make_unique<vizdoom::DoomGame>();
std::string path = "C:/practice/practice/vizdoom"; //C:/Users/ÐÐ½Ð°ÑÑ‚Ð°ÑÐ¸Ñ/mine/Ð¡ÐµÑÑÐ¸Ñ/practice/practice/vizdoom
const unsigned int sleepTime = 1000 / vizdoom::DEFAULT_TICRATE;
auto screenBuff = cv::Mat(480, 640, CV_8UC3);


void runTask1(int episodes) {

    try {
        game->loadConfig(path + "/scenarios/task1.cfg");
        game->setScreenResolution(vizdoom::RES_640X480);
        game->setWindowVisible(true);
        game->setRenderWeapon(true);
        game->init();
    }
    catch (vizdoom::FileDoesNotExistException e) {
        std::cout << e.what() << std::endl;
        return;
    }

    auto greyscale = cv::Mat(480, 640, CV_8UC1);
>>>>>>> d47293430cb762a6215380645ae403d11eba61f3
    std::vector<double> action;

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
<<<<<<< HEAD
        std::cout << "Episode #" << i + 1 << std::endl;
=======
        std::cout << "Episode #" << (i + 1) << std::endl;
>>>>>>> d47293430cb762a6215380645ae403d11eba61f3

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());
<<<<<<< HEAD

            cv::extractChannel(screenBuff, greyscale, 2);

            cv::threshold(greyscale, greyscale, 180, 255, cv::THRESH_BINARY);

            cv::imshow("Output Window", greyscale);

            double reward = game->makeAction({ 0, 0, 1 });


            std::cout << reward << " ";
            cv::waitKey(sleepTime);
        }

        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}
=======
>>>>>>> d47293430cb762a6215380645ae403d11eba61f3

            cv::extractChannel(screenBuff, greyscale, 2);

            cv::threshold(greyscale, greyscale, 180, 255, cv::THRESH_BINARY);

            cv::imshow("Output Window", greyscale);

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

<<<<<<< HEAD
    cv::namedWindow("Control Window", cv::WINDOW_AUTOSIZE);

    auto episodes = 10;


    RunTask1(episodes);


    game->close();
}
=======
    cv::namedWindow("Output Window", cv::WINDOW_AUTOSIZE);

    auto episodes = 10;
 
    runTask1(episodes);

    game->close();
  
}
>>>>>>> d47293430cb762a6215380645ae403d11eba61f3
