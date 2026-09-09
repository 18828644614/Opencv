# 矩阵与 cv::Mat 思维

`cv::Mat` 同时包含尺寸、类型、数据指针和引用计数。赋值通常是浅拷贝：

```cpp
cv::Mat view = image;          // 共享数据
cv::Mat copy = image.clone();  // 深拷贝
```

裁剪得到的 ROI 通常也是视图。修改 ROI 可能修改原图，这是高频的“结果莫名变化”来源。需要独立结果时显式 `clone()`。
