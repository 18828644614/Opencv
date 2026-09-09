# OpenCV 项目目录设计

```text
project/
├─ CMakeLists.txt
├─ include/          # 对外头文件
├─ src/              # 算法与应用实现
├─ apps/             # 可执行程序入口
├─ tests/            # 测试
├─ assets/           # 小型示例数据
├─ configs/          # 阈值和模型配置
└─ README.md
```

不要把图片路径、阈值和摄像头编号硬编码在算法函数里；使用配置对象或命令行参数传入。
