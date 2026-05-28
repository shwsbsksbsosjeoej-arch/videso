# videso 自动板机（黄色目标识别触发）

## 核心技术

- DXGI Desktop Duplication 高速截图
- OpenCV 实时图像处理
- HSV 颜色检测
- 多线程架构
- ImGui 调试界面
- SendInput 输入模拟
- CMake 工程
- VS2022 编译支持

## 识别流程

1. DXGI 实时截图
2. BGR 转 HSV
3. inRange 颜色筛选
4. GaussianBlur 高斯模糊
5. 形态学去噪
6. findContours 轮廓检测
7. 获取目标中心点
8. ImGui 显示检测框与调试信息

## 功能

- 实现黄色目标检测
- 实时 HSV 参数调节
- 可视化 Mask/调试信息
- 区域与面积过滤
- SendInput 键盘/鼠标模拟
- 支持热键绑定、侧键检测、连发/单发模式
- 完整窗口功能、可保存配置、透明与托盘模式
- 多线程处理、日志、异常保护

## 编译方法

1. 安装 OpenCV（推荐 OpenCV 4.x）
2. 下载 ImGui 到 external/imgui 目录
3. 安装 VS2022 + CMake
4. 配置 CMake，编译解决方案

## 仅供学习图像处理、自动化输入相关技术、现代 C++ 软件架构使用。
