#include <opencv2/opencv.hpp>  // OpenCV 的常用功能：Mat、imread、imshow 等
#include <iostream>            // std::cout、std::cerr
#include <string>              // std::string
#include <vector>              // std::vector

int main() {
    // 图片文件的路径。
    // R"(...)" 是 C++ 的“原始字符串”，里面的反斜杠不需要写成 "\\"。
    const std::string path = R"(D:\learn\Opencv\src\image.jpg)";

    // 读取图片：
    // - path：图片路径
    // - cv::IMREAD_COLOR：按彩色图片读取（通常得到 3 个通道，顺序为 B、G、R）
    // 读取成功后，image 中会保存图片的像素数据、宽度、高度等信息。
    cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);

    // 如果读取失败，imread 会返回一个“空的 Mat”。
    // 常见原因：路径写错、文件不存在、文件格式不支持或没有访问权限。
    if (image.empty()) {
        std::cerr << "无法读取图片：" << path << '\n';
        return 1;  // 返回非 0 值，表示程序异常结束
    }

    // 输出图片的基本信息：
    // cols      ：列数，也就是图片宽度（width）
    // rows      ：行数，也就是图片高度（height）
    // channels  ：通道数；彩色图片通常为 3，灰度图片通常为 1
    // depth     ：每个通道中单个像素值的数据类型。
    //             常见的 CV_8U（8 位无符号整数）返回值为 0，像素范围是 0~255。
    std::cout << "width=" << image.cols
              << ", height=" << image.rows
              << ", channels=" << image.channels()
              << ", depth=" << image.depth() << '\n';

    // 计算图片中心点坐标。
    // 注意：OpenCV 使用 (行 y, 列 x) 访问像素，而不是通常数学坐标中的 (x, y)。
    const int x = image.cols / 2;
    const int y = image.rows / 2;

    // 读取中心点像素。
    // cv::Vec3b 表示“包含 3 个 unsigned char（无符号 8 位整数）的向量”，
    // 正好适合彩色 CV_8UC3 图片。
    // image.at<T>(y, x) 的参数顺序是：先行 y，再列 x。
    const cv::Vec3b p = image.at<cv::Vec3b>(y, x);

    // OpenCV 默认使用 BGR 通道顺序，而不是 RGB：
    // p[0] = Blue（蓝色）
    // p[1] = Green（绿色）
    // p[2] = Red（红色）
    // static_cast<int> 用来把 unsigned char 转成数字输出，否则可能被当作字符显示。
    std::cout << "center BGR = ("
              << static_cast<int>(p[0]) << ", "
              << static_cast<int>(p[1]) << ", "
              << static_cast<int>(p[2]) << ")\n";

    // 用 vector 保存拆分后的通道图片。
    // split 后：channels[0] 是蓝色通道，channels[1] 是绿色通道，channels[2] 是红色通道。
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // 分别保存三个通道。
    // 每个通道都是一张单通道灰度图：像素越亮，说明该颜色分量越强。
    cv::imwrite(R"(D:\learn\Opencv\src\program1\blue.png)", channels[0]);
    cv::imwrite(R"(D:\learn\Opencv\src\program1\green.png)", channels[1]);
    cv::imwrite(R"(D:\learn\Opencv\src\program1\red.png)", channels[2]);

    // 显示原始彩色图片。
    // 第一个参数是窗口标题，第二个参数是要显示的 Mat。
    cv::imshow("BGR image", image);

    // 等待键盘输入；参数为 0 表示一直等待，直到用户按下任意键。
    // 如果没有这句，窗口可能一闪而过，程序也会立即结束。
    cv::waitKey(0);

    return 0;  // 返回 0，表示程序正常结束
}
