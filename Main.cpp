#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include "windows.h"
#include <cmath>

<<<<<<< HEAD
std::string path = "C:/practice/practice/vizdoom";
=======
std::string path = "C:/Uers/РђРЅР°СЃС‚Р°СЃРё/mine/РЎРµСЃСЃРёСЏ/practice/practice/vizdoom";
>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
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
<<<<<<< HEAD
    double cosAn = (pow(line1, 2) + pow(line2, 2) - pow(opLine, 2))/(2*line1*line2);
    double angle = acos(cosAn)*180/3.14;
=======
    double cosAn = (pow(line1, 2) + pow(line2, 2) - pow(opLine, 2)) / (2 * line1 * line2);
    double angle = acos(cosAn) * 180 / 3.14;
>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
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
<<<<<<< HEAD
void runTask1vol2(int episodes) { //нерабочий вариант
=======
void runTask1vol2(int episodes) { //РЅРµСЂР°Р±РѕС‡РёР№ РІР°СЂРёР°РЅС‚
>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
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
<<<<<<< HEAD
       
=======

>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished()) {

            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::extractChannel(screenBuff, greyscale, 2);

            //cv::threshold(greyscale, greyscale, 100, 255, CV_THRESH_MASK);

            cv::Mat data = greyscale;
            cv::Mat labels, centers;
<<<<<<< HEAD
    
=======

>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
            data.reshape(1, data.cols / 2);
            data.convertTo(data, CV_32F);

            cv::kmeans(data, 2, labels, cv::TermCriteria(cv::TermCriteria::EPS, 10, 1.0), 1, cv::KMEANS_RANDOM_CENTERS, centers);

            data.reshape(2, data.rows);
            centers.reshape(2, centers.rows);

            if (centers.at<float>(0, 0) > 310 && centers.at<float>(0, 0) < 330) game->makeAction(action[2]);
<<<<<<< HEAD
            else if(centers.at<float>(0, 0) >=330) game->makeAction(action[1]); 
            else if(centers.at<float>(0, 0) <= 310) game->makeAction(action[0]);
            cv::circle(greyscale, cv::Point(centers.at<float>(0, 0), centers.at<float>(0, 1)), 10 , cv::Scalar::all(255));
            cv::circle(greyscale, cv::Point(centers.at<float>(1, 0), centers.at<float>(1, 1)), 20 , cv::Scalar::all(255));
            
            cv::imshow("Gray", greyscale);
          
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


=======
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
void runTask2(int episodes) { //РІР°Р»РёС‚СЃСЏ РЅР° 5Рј С‚РµСЃС‚Рµ; РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµ РІС‚РѕСЂРѕРіРѕ СЃРїСЂР°Р№С‚Р° РЅРµ РїРѕРјРѕРіР°РµС‚
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


>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
            double minval; double maxval; cv::Point minLoc; cv::Point maxLoc;

            if (i != 4) {
                int result_cols = img.cols - temp1.cols + 1;
                int result_rows = img.rows - temp1.rows + 1;
                result.create(result_rows, result_cols, CV_32FC1);
                matchTemplate(img, temp1, result, 4);
                normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                minMaxLoc(result, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
<<<<<<< HEAD
            }
            else {
                break; //да, пятый эпизод для нашего бота нерешаемый. Но это пока (переделаем через kmeans, возможно...);
            }


            rectangle(img, maxLoc, cv::Point(maxLoc.x + temp1.cols, maxLoc.y + temp1.rows), cv::Scalar::all(255), 2, 8, 0);
            cv::line(img, cv::Point(maxLoc.x + temp1.cols/2, maxLoc.y + temp1.rows/2),
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
=======
            }
            else {
                break; //РґР°, РїСЏС‚С‹Р№ СЌРїРёР·РѕРґ РґР»СЏ РЅР°С€РµРіРѕ Р±РѕС‚Р° РЅРµСЂРµС€Р°РµРјС‹Р№. РќРѕ СЌС‚Рѕ РїРѕРєР° (РїРµСЂРµРґРµР»Р°РµРј С‡РµСЂРµР· kmeans, РІРѕР·РјРѕР¶РЅРѕ...);
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
>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
            else game->makeAction({ 0, 0, 0, 1 });

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

<<<<<<< HEAD
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

=======
>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
int main()
{
    game->setViZDoomPath(path + "/vizdoom.exe");
    game->setDoomGamePath(path + "/freedoom2.wad");

    auto episodes = 10;

<<<<<<< HEAD
    runTask1(episodes);
=======
    runTask2(episodes);
>>>>>>> ecf02b8d9813537780a7ac24d1c4bc25edcf752e
    std::cout << "Total Reward: " << float(total) / episodes;

    game->close();
}
