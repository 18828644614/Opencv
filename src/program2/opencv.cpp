#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  const std::string inputPath = R"(D:\learn\Opencv\src\image2.png)";
  const std::string outputDir = R"(D:\learn\Opencv\src\program2\output)";

  cv::Mat bgr = cv::imread(inputPath, cv::IMREAD_COLOR);
  if (bgr.empty()) {
    std::cerr << "Can't read image: " << inputPath << '\n';
    return 1;
  }

  cv::Mat gray, hsv, blueMask, blueOnly, red1Mask, red1Only, red2Mask, red2Only,redMask;
  cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);
  cv::cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);

  const cv::Scalar lower(90, 80, 50);
  const cv::Scalar upper(130, 255, 255);
  cv::inRange(hsv, lower, upper, blueMask);
  bgr.copyTo(blueOnly, blueMask);

  const bool ok1 = cv::imwrite(outputDir + R"(\gray.png)", gray);
  const bool ok2 = cv::imwrite(outputDir + R"(\blueMask.png)", blueMask);
  const bool ok3 = cv::imwrite(outputDir + R"(\BlueOnly.png)", blueOnly);

  const cv::Scalar lower_red1(0, 80, 50);
  const cv::Scalar upper_red1(10, 255, 255);

  const cv::Scalar lower_red2(170, 80, 50);
  const cv::Scalar upper_red2(179, 255, 255);

  cv::inRange(hsv, lower_red1, upper_red1, red1Mask);
  bgr.copyTo(red1Only,red1Mask);

  cv::inRange(hsv,lower_red2,upper_red2,red2Mask);
  bgr.copyTo(red2Only,red2Mask);

  cv::bitwise_or(red1Only,red2Only,redMask);

  const bool ok4 = cv::imwrite(outputDir + R"(\red1Mask.png)", red1Mask);
  const bool ok5 = cv::imwrite(outputDir + R"(\red2Mask.png)", red2Mask);
  const bool ok6 = cv::imwrite(outputDir + R"(\red1Only.png)", red1Only);
  const bool ok7 = cv::imwrite(outputDir + R"(\red2Only.png)", red2Only);
  const bool ok8 = cv::imwrite(outputDir + R"(\redMask.png)", redMask);

  if(!ok1 ||!ok2 ||!ok3 ||!ok4 ||!ok5 ||!ok6 ||!ok7 ||!ok8){
    std::cerr<<"结果保存失败\n";
    return 1;
  }
  cv::imshow("BGR",bgr);
  cv::imshow("GRAY",gray);
  cv::imshow("BLUEMASK",blueMask);
  cv::imshow("BLUEONLY",blueOnly);
  cv::imshow("RED1MASK",red1Mask);
  cv::imshow("RED1ONLY",red1Only);
  cv::imshow("RED2MASK",red2Mask);
  cv::imshow("RED2ONLY",red2Only);
  cv::imshow("REDMASK",redMask);

  cv::waitKey(0);

  return 0;
}
