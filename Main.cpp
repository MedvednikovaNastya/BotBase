#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include "windows.h"
#include <cmath>

std::string path = "C:/practice/practice/vizdoom";
auto game = std::make_unique<vizdoom::DoomGame>();
const unsigned int sleepTime = 1000 / vizdoom::DEFAULT_TICRATE;
auto screenBuff = cv::Mat(480, 640, CV_8UC3);
const char* headaFront = "./sprites/Enemies/heada1.png";
const char* headaSide = "./sprites/Enemies/heada2a8.png";
const char* medikit = "./sprites/Pickups/media0.png";
const char* akainu = "./sprites/Enemies/akainu.png";
std::vector<std::vector<double>> action = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
int total = 0;


int lengOfLine(int x1, int y1, int x2, int y2) {
    double leng = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return int(leng);
}
double angleBySides(double line1, double line2, double opLine) {
    double cosAn = (pow(line1, 2) + pow(line2, 2) - pow(opLine, 2))/(2*line1*line2);
    double angle = acos(cosAn) * 180 / 3.14;
    return angle;
}

void runTask1(int episodes)
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

    cv::namedWindow("Result window", cv::WINDOW_AUTOSIZE);


    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::Mat img = screenBuff;
            cv::Mat front = cv::imread(headaFront);
            cv::Mat left = cv::imread(headaSide);
            cv::Mat akainuMat = cv::imread(akainu);
            cv::Mat right; cv::flip(left, right, +1);
            cv::Mat resultF, resultL, resultR;

            int resultF_cols = img.cols - front.cols + 1;
            int resultF_rows = img.rows - front.rows + 1;
            int resultS_cols = img.cols - left.cols + 1;
            int resultS_rows = img.rows - left.rows + 1;

            double minval; double maxval; cv::Point minLoc; cv::Point maxLoc;

            resultF.create(resultF_rows, resultF_cols, CV_32FC1);
            matchTemplate(img, front, resultF, 4);
            normalize(resultF, resultF, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            minMaxLoc(resultF, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            if (maxLoc.y > 240) {
                resultL.create(resultS_rows, resultS_cols, CV_32FC1);
                matchTemplate(img, left, resultL, 4);
                normalize(resultL, resultL, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                minMaxLoc(resultL, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
                if (maxLoc.y > 240) {
                    resultR.create(resultS_rows, resultS_cols, CV_32FC1);
                    matchTemplate(img, right, resultR, 4);
                    normalize(resultR, resultR, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                    minMaxLoc(resultR, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
                }
            }
            rectangle(img, maxLoc, cv::Point(maxLoc.x + front.cols, maxLoc.y + front.rows), cv::Scalar::all(255), 2, 8, 0);

            akainuMat.copyTo(img(cv::Rect(maxLoc.x, maxLoc.y, akainuMat.cols, akainuMat.rows)));

            cv::imshow("Result window", img);

            if (maxLoc.x > 260 && maxLoc.x < 310) {
                game->makeAction(action[2]);
            }
            else if (maxLoc.x >= 310) {
                game->makeAction(action[1]);
            }
            else if (maxLoc.x <= 260) game->makeAction(action[0]);

            cv::waitKey(sleepTime);

        }

        total += game->getTotalReward();
        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}
void runTask2(int episodes) { //валится на 5м тесте; использование второго спрайта не помогает
    try
    {
        game->loadConfig(path + "/scenarios/task2.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    cv::namedWindow("Result window", cv::WINDOW_AUTOSIZE);


    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::Mat img = screenBuff;
            cv::Mat front = cv::imread(headaFront);
            cv::Mat left = cv::imread(headaSide);
            cv::Mat right; cv::flip(left, right, +1);
            cv::Mat resultF, resultL, resultR;

            int resultF_cols = img.cols - front.cols + 1;
            int resultF_rows = img.rows - front.rows + 1;
            int resultS_cols = img.cols - left.cols + 1;
            int resultS_rows = img.rows - left.rows + 1;

            double minval; double maxval; cv::Point minLoc; cv::Point maxLoc;

            resultF.create(resultF_rows, resultF_cols, CV_32FC1);
            matchTemplate(img, front, resultF, 4);
            normalize(resultF, resultF, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            minMaxLoc(resultF, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            if (maxLoc.y > 240) {
                resultL.create(resultS_rows, resultS_cols, CV_32FC1);
                matchTemplate(img, left, resultL, 4);
                normalize(resultL, resultL, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                minMaxLoc(resultL, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
                if (maxLoc.y > 240) {
                    resultR.create(resultS_rows, resultS_cols, CV_32FC1);
                    matchTemplate(img, right, resultR, 4);
                    normalize(resultR, resultR, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                    minMaxLoc(resultR, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
                }
               
            }
            rectangle(img, maxLoc, cv::Point(maxLoc.x + front.cols, maxLoc.y + front.rows), cv::Scalar::all(255), 2, 8, 0);

            cv::imshow("Result window", img);
           
            if (maxLoc.x > 260 && maxLoc.x < 310) {
                game->makeAction({ 0, 0, 0, 1 });
            }
            else if (maxLoc.x >= 310) {
                game->makeAction(action[1]);
            }
            else if (maxLoc.x <= 260) game->makeAction(action[0]);

            cv::waitKey(sleepTime);

        }

        total += game->getTotalReward();
        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}
void runTask2vol2(int episodes) {
    try {
        game->loadConfig(path + "/scenarios/task2.cfg");
        game->init();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    auto greyscale = cv::Mat(480, 640, CV_8UC1);

    for (auto i = 0; i < episodes; i++) {

        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished()) {

            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::extractChannel(screenBuff, greyscale, 2);

            cv::threshold(greyscale, greyscale, 185, 255, CV_THRESH_BINARY);

            int white = 0;
            for (int i = 0; i < 640; i++) {
                if (greyscale.at<uchar>(245, i) == 255) {
                    white = i;
                    break;
                }
            }

            cv::line(greyscale, cv::Point(white, 240), cv::Point(320, 479), cv::Scalar::all(255), 2);
            cv::line(greyscale, cv::Point(white, 240), cv::Point(320, 0), cv::Scalar::all(255), 2);
            cv::line(greyscale, cv::Point(320, 0), cv::Point(320, 479), cv::Scalar::all(255), 2);

            double line1 = lengOfLine(white, 240, 320, 479);
            double line2 = 480.0;
            double line3 = lengOfLine(white, 240, 320, 0);
            double angle = angleBySides(line1, line2, line3);

            cv::imshow("Gray", greyscale);

            if (angle < 6.5) game->makeAction({ 0, 0, 0, 1 });
            else if (white < 320) game->makeAction(action[0]);
            else if (white > 320) game->makeAction(action[1]);

            cv::waitKey(sleepTime);
        }

        total += game->getTotalReward();
        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}
void runTask3(int episodes) { //пока только шаблон, можно даже не запускать
    try
    {
        game->loadConfig(path + "/scenarios/task3.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    auto greyscale = cv::Mat(480, 640, CV_8UC1);

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::waitKey(sleepTime);

        }

        total += game->getTotalReward();
        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}

int main()
{
    game->setViZDoomPath(path + "/vizdoom.exe");
    game->setDoomGamePath(path + "/freedoom2.wad");

    auto episodes = 10;

    runTask2vol2(episodes);
    std::cout << "Total Reward: " << float(total) / episodes;

    game->close();
}
