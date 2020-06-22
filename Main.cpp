#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include "windows.h"
#include <cmath>

std::string path = "C:/Users/јнастаси€/mine/—есси€/practice/practice/vizdoom";
auto game = std::make_unique<vizdoom::DoomGame>();
const unsigned int sleepTime = 3000 / vizdoom::DEFAULT_TICRATE;
auto screenBuff = cv::Mat(480, 640, CV_8UC3);
const char* headaFront = "./sprites/Enemies/heada1.png";
const char* medikit = "./sprites/Pickups/media0.png";
const char* akainu = "./sprites/Enemies/akainu.png";
std::vector<std::vector<double>> action = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
int total = 0;


int lengOfLine(int x1, int y1, int x2, int y2) {
    double leng = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return int(leng);
}
double angleBySides(double line1, double line2, double opLine) {
    double cosAn = (pow(line1, 2) + pow(line2, 2) - pow(opLine, 2)) / (2 * line1 * line2);
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

    auto greyscale = cv::Mat(480, 640, CV_8UC1);

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::Mat img = screenBuff;
            cv::Mat temp1 = cv::imread(headaFront);
            cv::Mat akainuMat = cv::imread(akainu);
            cv::Mat result;

            int result_cols = img.cols - temp1.cols + 1;
            int result_rows = img.rows - temp1.rows + 1;

            result.create(result_rows, result_cols, CV_32FC1);
            matchTemplate(img, temp1, result, 4);
            normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

            double minval; double maxval; cv::Point minLoc; cv::Point maxLoc;
            minMaxLoc(result, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            rectangle(img, maxLoc, cv::Point(maxLoc.x + temp1.cols, maxLoc.y + temp1.rows), cv::Scalar::all(255), 2, 8, 0);

            akainuMat.copyTo(img(cv::Rect(maxLoc.x, maxLoc.y, akainuMat.cols, akainuMat.rows)));

            cv::imshow("Origin", img);
            if (maxLoc.y <= 320) {
                if (maxLoc.x > 260 && maxLoc.x < 310) {
                    game->makeAction(action[2]);
                }
                else if (maxLoc.x >= 310) {
                    game->makeAction(action[1]);
                }
                else if (maxLoc.x <= 260) game->makeAction(action[0]);
            }
            else game->makeAction(action[1]);

            cv::waitKey(sleepTime);

        }

        total += game->getTotalReward();
        std::cout << std::endl << game->getTotalReward() << std::endl;
    }
}
void runTask1vol2(int episodes) { //нерабочий вариант
    try {
        game->loadConfig(path + "/scenarios/task1.cfg");
        //game->setWindowVisible(false);
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

            //cv::threshold(greyscale, greyscale, 100, 255, CV_THRESH_MASK);

            cv::Mat data = greyscale;
            cv::Mat labels, centers;

            data.reshape(1, data.cols / 2);
            data.convertTo(data, CV_32F);

            cv::kmeans(data, 2, labels, cv::TermCriteria(cv::TermCriteria::EPS, 10, 1.0), 1, cv::KMEANS_RANDOM_CENTERS, centers);

            data.reshape(2, data.rows);
            centers.reshape(2, centers.rows);

            if (centers.at<float>(0, 0) > 310 && centers.at<float>(0, 0) < 330) game->makeAction(action[2]);
            else if (centers.at<float>(0, 0) >= 330) game->makeAction(action[1]);
            else if (centers.at<float>(0, 0) <= 310) game->makeAction(action[0]);
            cv::circle(greyscale, cv::Point(centers.at<float>(0, 0), centers.at<float>(0, 1)), 10, cv::Scalar::all(255));
            cv::circle(greyscale, cv::Point(centers.at<float>(1, 0), centers.at<float>(1, 1)), 20, cv::Scalar::all(255));

            cv::imshow("Gray", greyscale);

            cv::waitKey(sleepTime);
        }

        total += game->getTotalReward();
        std::cout << std::endl << game->getTotalReward() << std::endl;
    }

}
void runTask2(int episodes) { //валитс€ на 5м тесте; использование второго спрайта не помогает
    try
    {
        game->loadConfig(path + "/scenarios/task2.cfg");
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

            cv::Mat img = screenBuff;
            cv::Mat temp1 = cv::imread(headaFront);
            cv::Mat result;


            double minval; double maxval; cv::Point minLoc; cv::Point maxLoc;

            if (i != 4) {
                int result_cols = img.cols - temp1.cols + 1;
                int result_rows = img.rows - temp1.rows + 1;
                result.create(result_rows, result_cols, CV_32FC1);
                matchTemplate(img, temp1, result, 4);
                normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                minMaxLoc(result, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            }
            else {
                break; //да, п€тый эпизод дл€ нашего бота нерешаемый. Ќо это пока (переделаем через kmeans, возможно...);
            }


            rectangle(img, maxLoc, cv::Point(maxLoc.x + temp1.cols, maxLoc.y + temp1.rows), cv::Scalar::all(255), 2, 8, 0);
            cv::line(img, cv::Point(maxLoc.x + temp1.cols / 2, maxLoc.y + temp1.rows / 2),
                cv::Point(320, 479), cv::Scalar::all(255), 2);
            cv::line(img, cv::Point(maxLoc.x + temp1.cols / 2, maxLoc.y + temp1.rows / 2),
                cv::Point(320, 0), cv::Scalar::all(255), 2);
            cv::line(img, cv::Point(320, 0),
                cv::Point(320, 479), cv::Scalar::all(255), 2);

            double line1 = lengOfLine(maxLoc.x + temp1.cols / 2, maxLoc.y + temp1.rows / 2, 320, 479);
            double line2 = 480.0;
            double line3 = lengOfLine(maxLoc.x + temp1.cols / 2, maxLoc.y + temp1.rows / 2, 320, 0);
            double angle = angleBySides(line1, line2, line3);

            cv::imshow("Origin", img);
            if (maxLoc.y < 240) {
                if (angle < 5.0) game->makeAction({ 0, 0, 0, 1 });
                else if (maxLoc.x + temp1.cols / 2 < 310) game->makeAction(action[0]);
                else if (maxLoc.x + temp1.cols / 2 > 330) game->makeAction(action[1]);
            }
            else game->makeAction({ 0, 0, 0, 1 });

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

    runTask2(episodes);
    std::cout << "Total Reward: " << float(total) / episodes;

    game->close();
}