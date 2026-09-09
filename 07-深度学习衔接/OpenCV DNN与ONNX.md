# OpenCV DNN 与 ONNX

OpenCV DNN 可以加载部分 ONNX、TensorFlow、Caffe 等格式的模型。部署时重点验证算子支持、输入布局、颜色顺序、归一化和输出张量解释。

模型能成功加载不代表结果正确；应使用一张已知输入，与训练框架或官方示例对比输出。
