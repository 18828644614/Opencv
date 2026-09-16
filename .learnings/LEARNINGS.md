## [LRN-20260909-001] correction

**Logged**: 2026-09-09T23:55:00+08:00
**Priority**: medium
**Status**: resolved
**Area**: docs

### 摘要（Summary）
讲解 `cv::split` 时，必须明确说明 C++ 下标从 0 开始，以及 `std::vector<cv::Mat>` 是多个单通道矩阵的容器，而不是一张“多图片”图像。

### 详情（Details）
用户反馈原文档只给出了 `channels[0]`、`channels[1]`、`channels[2]` 的代码注释，没有解释分离结果的对象结构，容易让初学者误以为下标从 1 开始，或误解 `vector<Mat>` 的含义。正确规则是：BGR 分离后 `channels.size() == 3`，有效下标为 `0~2`；BGRA 分离后 `channels.size() == 4`，有效下标为 `0~3`，不存在 `channels[4]`。每个元素都是一张与原图同宽高、但只有一个通道的 `cv::Mat`。

### 建议行动（Suggested Action）
在图像基础文档中同时给出对象类型、尺寸、通道数、下标范围和 BGR/BGRA 对照表，并提醒访问越界风险。

### 元数据（Metadata）
- Source: user_feedback
- Related Files: 02-图像基础/像素、通道与位深.md
- Tags: opencv, cv::split, cv::merge, vector, channels

### 解决情况（Resolution）
- **Resolved**: 2026-09-09T23:55:00+08:00
- **Commit/PR**: N/A
- **Notes**: 已在目标 Markdown 中补充逐步解释、BGR/BGRA 下标表、类型和尺寸示例，以及 `channels[4]` 越界说明。

---
