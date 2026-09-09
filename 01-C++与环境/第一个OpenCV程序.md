# 第一个 OpenCV 程序

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    const cv::Mat image = cv::imread("assets/input.jpg");
    if (image.empty()) {
        std::cerr << "无法读取图片\n";
        return 1;
    }
    cv::imshow("image", image);
    cv::waitKey(0);
    return 0;
}
```

第一条调试原则：任何图像处理前都检查 `image.empty()`，并确认当前工作目录和图片路径。
