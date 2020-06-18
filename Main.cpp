#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>


std::string path = "C:/practice/practice/vizdoom";
auto game = std::make_unique<vizdoom::DoomGame>();
const unsigned int sleepTime = 1000 / vizdoom::DEFAULT_TICRATE;
auto screenBuff = cv::Mat(480, 640, CV_8UC3);
const char* filename = "./sprites/Enemies/heada1.png";


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
    std::vector<std::vector<double>> action = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::Mat img = screenBuff;
            cv::Mat temp1 = cv::imread(filename);
            cv::Mat result;

            int result_cols = img.cols - temp1.cols + 1;
            int result_rows = img.rows - temp1.rows + 1;

            result.create(result_rows, result_cols, CV_32FC1);
            matchTemplate(img, temp1, result, 4);
            normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

            double minval; double maxval; cv::Point minLoc; cv::Point maxLoc;
            minMaxLoc(result, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            rectangle(img, maxLoc, cv::Point(maxLoc.x + temp1.cols, maxLoc.y + temp1.rows), cv::Scalar::all(255), 2, 8, 0);

            cv::imshow("Origin", img);

            if (maxLoc.x > 260 && maxLoc.x < 300) {
                game->makeAction(action[2]);
            }
            else if (maxLoc.x >= 300) {
                game->makeAction(action[1]);
            } else if(maxLoc.x <= 260) game->makeAction(action[0]);

            cv::waitKey(sleepTime);

        }

        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}


int main()
{
    game->setViZDoomPath(path + "/vizdoom.exe");
    game->setDoomGamePath(path + "/freedoom2.wad");

    auto episodes = 10;


    RunTask1(episodes);


    game->close();
}
