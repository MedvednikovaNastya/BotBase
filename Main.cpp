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
const char* worm = "./sprites/Enemies/sarga1.png";
const char* warrior = "./sprites/Enemies/cposa1.png";
const char* medikit = "./sprites/Pickups/media0.png";
const char* akainu = "./sprites/Enemies/akainu.png";
std::vector<std::vector<double>> action = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0},  {0, 0, 0, 1} , {0, 0, 0, 0} };
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
            matchTemplate(img, front, resultF, 5);
            normalize(resultF, resultF, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            minMaxLoc(resultF, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            if (maxLoc.y > 240) {
                resultL.create(resultS_rows, resultS_cols, CV_32FC1);
                matchTemplate(img, left, resultL, 5);
                normalize(resultL, resultL, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                minMaxLoc(resultL, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
                if (maxLoc.y > 240) {
                    resultR.create(resultS_rows, resultS_cols, CV_32FC1);
                    matchTemplate(img, right, resultR, 5);
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
void runTask2(int episodes) { 
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
            matchTemplate(img, front, resultF, 5);
            normalize(resultF, resultF, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            minMaxLoc(resultF, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
            if (maxLoc.y > 240) {
                resultL.create(resultS_rows, resultS_cols, CV_32FC1);
                matchTemplate(img, left, resultL, 5);
                normalize(resultL, resultL, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
                minMaxLoc(resultL, &minval, &maxval, &minLoc, &maxLoc, cv::Mat());
                if (maxLoc.y > 240) {
                    resultR.create(resultS_rows, resultS_cols, CV_32FC1);
                    matchTemplate(img, right, resultR, 5);
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
void runTask3(int episodes) {
    try
    {
        game->loadConfig(path + "/scenarios/task3.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    cv::namedWindow("Origin", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Result", CV_WINDOW_AUTOSIZE);

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::Mat img = screenBuff;
            cv::Mat medi = cv::imread(medikit);
            cv::Mat result;

            double minval, maxval; cv::Point minLoc, maxLoc;
            int res_cols = img.cols - medi.cols + 1;
            int res_rows = img.rows - medi.rows + 1;
            result.create(res_cols, res_rows, CV_32FC1);

            cv::matchTemplate(img, medi, result, 4);
            cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            cv::Rect roi(290, 0, 60, result.rows);
            result = result(roi);
            cv::minMaxLoc(result, &minval, &maxval, &minLoc, &maxLoc);

            circle(img, cv::Point(300 + maxLoc.x, maxLoc.y + 10), 8, cv::Scalar(0, 255, 255), -1);

            if (maxLoc.y < 390) {
                if (290 + maxLoc.x < 300) game->makeAction(action[0]);
                else if(290 + maxLoc.x > 340) game->makeAction(action[1]);
               else game->makeAction(action[3]);
            }
            else game->makeAction(action[0]);

            cv::imshow("Origin", img);
            cv::imshow("Result", result);
         
            cv::waitKey(sleepTime);

        }
        total += game->getEpisodeTime();
        std::cout << std::endl << game->getEpisodeTime() << std::endl;
    }
}
void runTask4(int episodes) {
    try
    {
        game->loadConfig(path + "/scenarios/task4.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    cv::namedWindow("Origin", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Result", CV_WINDOW_AUTOSIZE);

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            cv::Mat img = screenBuff;
            cv::Mat medi = cv::imread(medikit);
            cv::Mat result;
          
            double minval, maxval; cv::Point minLoc, maxLoc;
            int res_cols = img.cols - medi.cols + 1;
            int res_rows = img.rows - medi.rows + 1;
            result.create(res_cols, res_rows, CV_32FC1);

            cv::matchTemplate(img, medi, result, 4);
            cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            cv::Rect roi(260, 0, 120, result.rows - 50);
            result = result(roi);
            cv::minMaxLoc(result, &minval, &maxval, &minLoc, &maxLoc);

            circle(img, cv::Point(300 + maxLoc.x, maxLoc.y + 10), 8, cv::Scalar(0, 255, 255), -1);
          
            if (maxLoc.y < 390) {
                if (290 + maxLoc.x < 300) game->makeAction(action[0]);
                else if (290 + maxLoc.x > 340) game->makeAction(action[1]);
                else game->makeAction(action[3]);
            }
            else for (int k = 0; k < 6; k++) game->makeAction(action[1]);

            cv::imshow("Origin", img);
            cv::imshow("Result", result);

            cv::waitKey(sleepTime);

        }

        total += game->getEpisodeTime();
        std::cout << std::endl << game->getEpisodeTime() << std::endl;
    }
}
void runTask5(int episodes) {
    try
    {
        game->loadConfig(path + "/scenarios/task5.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    cv::namedWindow("Result", CV_WINDOW_AUTOSIZE);
   
    IplImage* data;
    IplImage* grey = cvCreateImage(cv::Size(640, 480), IPL_DEPTH_8U, 1);
    IplImage* result = cvCreateImage(cv::Size(640, 480), IPL_DEPTH_8U, 1);
    cv::Mat resultMat;
    int whiteX, act;

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            data = (&(IplImage)screenBuff);

            cvCvtColor(data, grey, CV_RGB2GRAY);
            cvCanny(grey, result, 200, 255, 3);
 
            resultMat = cv::cvarrToMat(result);

            whiteX = 320;
            for (int k =50; k < 590; k++) {
                if (resultMat.at<char>(240, k) < 0) {
                    whiteX = k;
                    break;
                }
            }

            act = 4;
            if (whiteX < 320) act = 1;
            else if (whiteX > 320) act = 0;
          
            game->makeAction(action[act]);

            line(resultMat, cvPoint(0, 240), cvPoint(639, 240), cvScalar(255), 2);
            line(resultMat, cvPoint(50, 0), cvPoint(50, 479), cvScalar(255), 2);
            line(resultMat, cvPoint(590, 0), cvPoint(590, 479), cvScalar(255), 2);
            line(resultMat, cvPoint(320, 0), cvPoint(320, 479), cvScalar(255), 2);

            cv::imshow("Result", resultMat);

            cv::waitKey(sleepTime);

        }
        total += game->getEpisodeTime();
        std::cout << std::endl << game->getEpisodeTime() << std::endl;
    }
}
void runTask7(int episodes) {
    try {
        game->loadConfig(path + "/scenarios/task7.cfg");
        game->init();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    cv::namedWindow("Result", CV_WINDOW_AUTOSIZE);

    IplImage* data;
    IplImage* grey = cvCreateImage(cv::Size(640, 480), IPL_DEPTH_8U, 1);
    IplImage* result = cvCreateImage(cv::Size(640, 480), IPL_DEPTH_8U, 1);
    cv::Mat resultMat;
    int whiteX, act;


    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            data = (&(IplImage)screenBuff);
            cvCvtColor(data, grey, CV_RGB2GRAY);
            cvCanny(grey, result, 200, 255, 3);

            resultMat = cv::cvarrToMat(result);

            whiteX = -1;
            for (int k = 310; k < 330; k++) {
                if (resultMat.at<char>(230, k) < 0) {
                    whiteX = k;
                    break;
                }
            }

            act = 1;
            if (whiteX != -1) act = 3;

            line(resultMat, cvPoint(0, 230), cvPoint(639, 230), cvScalar(255), 2);

            game->makeAction(action[act]);

            cv::imshow("Result", resultMat);

            cv::waitKey(sleepTime);

        }
        total += game->getEpisodeTime();
        std::cout << std::endl << game->getEpisodeTime() << std::endl;
    }

}
void runTask9(int episodes) {
    try
    {
        game->loadConfig(path + "/scenarios/task9.cfg");
        game->init();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    cv::namedWindow("Result", CV_WINDOW_AUTOSIZE);

    IplImage* data;
    IplImage* grey = cvCreateImage(cv::Size(640, 480), IPL_DEPTH_8U, 1);
    IplImage* result = cvCreateImage(cv::Size(640, 480), IPL_DEPTH_8U, 1);
    cv::Mat resultMat;

    for (auto i = 0; i < episodes; i++)
    {
        game->newEpisode();
        std::cout << "Episode #" << i + 1 << std::endl;

        int whiteXl = 0, whiteXr = 639;
        bool lch = true, rch = true;
        int triangle = 0;
        int rotNuml = 0, rotNumr = 0;

        while (!game->isEpisodeFinished())
        {
            const auto& gamestate = game->getState();

            std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

            data = (&(IplImage)screenBuff);

            cvCvtColor(data, grey, CV_RGB2GRAY);
            cvCanny(grey, result, 240, 255, 3);

            resultMat = cv::cvarrToMat(result);

            if (!triangle) {
                for (int k = 50; k < 270; k++) {
                    for (int k1 = 180; k1 < 240; k1++) {
                        if (resultMat.at<char>(k1, k) != 0) {
                            triangle++;
                            lch = false;
                            break;
                        }
                    }
                    if (!lch) break;
                }
                for (int k = 589; k > 370; k--) {
                    for (int k1 = 180; k1 < 240; k1++) {
                        if (resultMat.at<char>(k1, k) != 0) {
                            triangle++;
                            rch = false;
                            break;
                        }
                    }
                    if (!rch) break;
                }
            }

            whiteXl = 0, whiteXr = 639;
            if (!rch) {
                for (int k = 589; k > 320; k--) {
                    for (int k1 = 180; k1 < 240; k1++) {
                        if (resultMat.at<char>(k1, k) != 0) {
                            whiteXr = k;
                            std::wcout << k << "\n";
                            break;
                        }
                    }
                    if (whiteXr < 639) break;
                }
                if (whiteXr > 345) {
                    game->makeAction({ 0, 0, 0, 0, 0, 1, 0, 0 });
                    rotNuml++;
                }
                else {
                    game->makeAction({ 0, 0, 0, 0, 0, 0, 0, 1 });
                    rch = true;
                    triangle--;
                }
            } else 
            if (!lch) {
                for (int k = 50; k < 320; k++) {
                    for (int k1 = 180; k1 < 240; k1++) {
                        if (resultMat.at<char>(k1, k) != 0) {
                            whiteXl = k;
                            break;
                        }
                        if (whiteXl > 0) break;
                    }
                }
                if (whiteXl < 295) {
                    game->makeAction({ 0, 0, 0, 0, 1, 0, 0, 0 });
                }
                else {
                    game->makeAction({ 0, 0, 0, 0, 0, 0, 0, 1 });
                    lch = true;
                    triangle--;
                }

            } else game->makeAction({ 0, 0, 1, 0, 0, 0, 0, 0 }); 
            
            line(resultMat, cv::Point(0, 250), cv::Point(639, 250), cv::Scalar(255, 255, 255), 2);
            line(resultMat, cv::Point(589, 180), cv::Point(320, 240), cv::Scalar(255, 255, 255), 2);
            line(resultMat, cv::Point(50, 180), cv::Point(320, 240), cv::Scalar(255, 255, 255), 2);
            cv::imshow("Result", resultMat);

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

    runTask9(episodes);
    std::cout << "Total Reward (or time): " << float(total) / episodes;

    game->close();
}
