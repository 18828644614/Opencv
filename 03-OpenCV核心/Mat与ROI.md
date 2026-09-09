# Mat 与 ROI

```cpp
cv::Rect box(10, 10, 100, 80);
cv::Mat roi = image(box);
cv::rectangle(image, box, cv::Scalar(0, 255, 0), 2);
```

矩形必须位于图像范围内，否则会抛出异常。处理外部检测框时，先用 `&` 与图像边界求交，或手动裁剪坐标。
