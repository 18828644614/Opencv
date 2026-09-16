# build.ps1 修改快速参考

## 文件说明
`build.ps1` 是PowerShell自动化编译脚本，执行：清理 → 配置 → 编译

## 5个关键修改点

### 修改点1：更换Visual Studio版本（第47行）

**当前代码：**
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64
```

**修改示例：**
```powershell
# 使用VS 2019
cmake .. -G "Visual Studio 16 2019" -A x64

# 使用VS 2017
cmake .. -G "Visual Studio 15 2017" -A x64
```

---

### 修改点2：更换架构（第47行）

**当前代码：**
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64
```

**修改示例：**
```powershell
# 编译32位版本
cmake .. -G "Visual Studio 17 2022" -A Win32
```

⚠️ **注意：** 如果改为32位，还需要修改OpenCV路径（x64改为x86）

---

### 修改点3：使用MinGW编译器（第47行）

**前提条件：** 必须先为MinGW重新编译OpenCV

**修改为：**
```powershell
# 使用MinGW
cmake .. -G "MinGW Makefiles"
```

---

### 修改点4：更换编译配置（第67行）

**当前代码：**
```powershell
cmake --build . --config Release
```

**修改示例：**
```powershell
# 编译Debug版本（用于调试）
cmake --build . --config Debug

# Release但保留调试信息
cmake --build . --config RelWithDebInfo

# 最小体积Release
cmake --build . --config MinSizeRel
```

⚠️ **注意：** Debug版本的exe在 `build\Debug\` 目录

---

### 修改点5：更新输出路径提示（第76行）

**当前代码：**
```powershell
Write-Host "`nBuild complete! Executable: build\Release\opencv_test.exe"
```

**修改场景：**

1. **如果编译Debug版本：**
```powershell
Write-Host "`nBuild complete! Executable: build\Debug\opencv_test.exe"
```

2. **如果改了可执行文件名：**
```powershell
Write-Host "`nBuild complete! Executable: build\Release\my_app.exe"
```

3. **如果想显示中文：**
```powershell
Write-Host "`n编译完成！可执行文件：build\Release\opencv_test.exe"
```

---

## 常见修改组合

### 组合1：编译Debug版本
```powershell
# 第67行
cmake --build . --config Debug

# 第76行
Write-Host "`nBuild complete! Executable: build\Debug\opencv_test.exe"
```

### 组合2：使用VS 2019编译32位
```powershell
# 第47行
cmake .. -G "Visual Studio 16 2019" -A Win32

# 第67行（可选，保持Release）
cmake --build . --config Release

# 第76行
Write-Host "`nBuild complete! Executable: build\Release\opencv_test.exe"
```

### 组合3：改可执行文件名
```powershell
# 先修改CMakeLists.txt第57行：
# add_executable(my_program opencv.cpp)

# 然后修改build.ps1第76行：
Write-Host "`nBuild complete! Executable: build\Release\my_program.exe"
```

---

## 不需要修改的部分

以下代码通常不需要修改：

```powershell
# 清理构建目录（标准流程）
if (Test-Path build) { Remove-Item -Recurse -Force build }
New-Item -ItemType Directory -Force -Path build | Out-Null

# 进入和返回目录（标准流程）
Set-Location build
Set-Location ..
```

---

## 完整修改示例

**场景：我想用VS 2019编译Debug版本，程序改名为image_processor**

1. **修改CMakeLists.txt：**
```cmake
add_executable(image_processor opencv.cpp)
target_link_libraries(image_processor ${OpenCV_LIBS})
```

2. **修改build.ps1第47行：**
```powershell
cmake .. -G "Visual Studio 16 2019" -A x64
```

3. **修改build.ps1第67行：**
```powershell
cmake --build . --config Debug
```

4. **修改build.ps1第76行：**
```powershell
Write-Host "`nBuild complete! Executable: build\Debug\image_processor.exe"
```

---

## 故障排除

### 问题：脚本无法运行
**解决：** 确保使用ASCII编码保存，不要用UTF-8 BOM

### 问题：找不到Visual Studio
**解决：** 修改生成器名称为你已安装的VS版本

### 问题：找不到OpenCV
**解决：** 检查CMakeLists.txt中的OpenCV_DIR路径

---

生成时间: 2026-09-11
