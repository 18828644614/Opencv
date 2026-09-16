## [ERR-20260910-001] invalid_tool_poll

**Logged**: 2026-09-10T00:00:00+08:00
**Priority**: low
**Status**: resolved
**Area**: infra

### 摘要（Summary）
一次对不存在的 exec cell ID 的轮询调用失败，但没有影响用户代码或任务结果。

### 原始错误（Error）
```
Script error:
exec cell noop not found
Script error:
exec cell noop2 not found
```

### 上下文（Context）
- 为了并行执行检查，误用了不存在的占位 cell ID `noop` 和 `noop2`。
- 后续已改为直接执行必要的只读检查。

### 建议修复（Suggested Fix）
仅对实际返回“Script running with cell ID ...”的 exec 调用使用 `wait`；普通已完成调用无需轮询。

### 元数据（Metadata）
- Reproducible: yes
- Related Files: src/program1/opencv.cpp
- See Also: 

### 解决情况（Resolution）
- **Resolved**: 2026-09-10T00:00:00+08:00
- **Commit/PR**: 
- **Notes**: 已完成代码注释和后续检查，任务不受影响。

---

## [ERR-20260911-001] powershell_regex_quote

**Logged**: 2026-09-11T00:20:00+08:00
**Priority**: low
**Status**: resolved
**Area**: docs

### 摘要（Summary）
校验 Markdown 时，PowerShell 双引号字符串中的正则表达式包含未转义的双引号，导致命令解析失败。

### 原始错误（Error）
```
ParserError: An empty pipe element is not allowed.
```

### 上下文（Context）
- 使用 `rg -n` 检查包含 `R\"(` 的 C++ 原始字符串字面量。
- 后续改用 PowerShell 的 `Select-String` 完成同一检查。

### 建议修复（Suggested Fix）
在 PowerShell 中检查含双引号的正则时，优先使用单引号包裹模式，或使用 `Select-String` 避免多层转义。

### 元数据（Metadata）
- Reproducible: yes
- Related Files: 02-图像基础/矩阵与cvMat思维.md

---

## [ERR-20260916-001] cmake_build_program2

**Logged**: 2026-09-16T23:00:33+08:00
**Priority**: medium
**Status**: resolved
**Area**: config

### 摘要（Summary）
`program2` 的 CMake 配置和 OpenCV 查找均已成功，但源码因变量拼写错误导致 MSVC 编译失败。

### 原始错误（Error）
```text
D:\learn\Opencv\src\program2\opencv.cpp(21,14): error C2065: “blueOnly”: 未声明的标识符 [D:\learn\Opencv\src\program2\build\program2.vcxproj]
D:\learn\Opencv\src\program2\opencv.cpp(25,64): error C2065: “blueOnly”: 未声明的标识符 [D:\learn\Opencv\src\program2\build\program2.vcxproj]
D:\learn\Opencv\src\program2\opencv.cpp(25,14): error C2737: “ok3”: 必须初始化 const 对象 [D:\learn\Opencv\src\program2\build\program2.vcxproj]
D:\learn\Opencv\src\program2\opencv.cpp(54,25): error C2065: “blueOnly”: 未声明的标识符 [D:\learn\Opencv\src\program2\build\program2.vcxproj]
```

### 上下文（Context）
- 已使用 Visual Studio 17 2022、x64 生成器配置 `program2`。
- CMake 已找到 OpenCV 4.12.0，运行库为 `vc16`。
- 第 14 行声明了 `buleOnly`，第 21、25、54 行使用了 `blueOnly`。

### 建议修复（Suggested Fix）
统一变量拼写为 `blueOnly`，然后重新执行 `cmake --build build --config Release`。

### 元数据（Metadata）
- Reproducible: yes
- Related Files: src/program2/opencv.cpp; src/program2/CMakeLists.txt
- See Also:

### 解决情况（Resolution）
- **Resolved**: 2026-09-16T23:00:33+08:00
- **Commit/PR**:
- **Notes**: 已将第 14 行的 `buleOnly` 修正为 `blueOnly`，并成功生成和运行 Release 程序。

---

## [ERR-20260916-002] msbuild_duplicate_path

**Logged**: 2026-09-16T23:02:00+08:00
**Priority**: medium
**Status**: resolved
**Area**: infra

### 摘要（Summary）
MSBuild 启动 `CL.exe` 时因进程环境同时包含大小写不同的 `Path` 和 `PATH` 而失败。

### 原始错误（Error）
```text
error MSB6001: “CL.exe”的命令行开关无效。System.ArgumentException: 已添加项。字典中的关键字:“Path”所添加的关键字:“PATH”
```

### 上下文（Context）
- `cmake` 配置成功，源码拼写错误修复后，构建阶段才暴露该环境问题。
- 当前环境实际存在 `PATH` 和 `Path` 两个变量，值基本相同但大小写不同。

### 建议修复（Suggested Fix）
在启动 CMake/MSBuild 前构造只包含一个大小写统一的 `PATH` 环境变量；用户终端中也应避免重复配置 `Path` 和 `PATH`。

### 元数据（Metadata）
- Reproducible: yes
- Related Files: src/program2/CMakeLists.txt
- See Also:

### 解决情况（Resolution）
- **Resolved**: 2026-09-16T23:02:00+08:00
- **Commit/PR**:
- **Notes**: 使用去重后的环境变量启动 CMake，已成功构建 `program2.exe`。

---

## [ERR-20260916-003] powershell_diagnostic_parse

**Logged**: 2026-09-16T23:02:00+08:00
**Priority**: low
**Status**: resolved
**Area**: infra

### 摘要（Summary）
读取重复环境变量的 PowerShell 诊断命令因 `foreach` 语句后的管道写法错误而解析失败。

### 原始错误（Error）
```text
ParserError: An empty pipe element is not allowed.
```

### 上下文（Context）
- 首次诊断 `Path` 和 `PATH` 时直接将管道连接在 `foreach` 语句后。
- 改为先将 `foreach` 结果保存到变量，再执行 `Format-List` 后检查成功。

### 建议修复（Suggested Fix）
PowerShell 中需要管道处理 `foreach` 结果时，先使用变量或数组子表达式接收结果。

### 元数据（Metadata）
- Reproducible: yes
- Related Files: src/program2/build/CMakeCache.txt
- See Also:

### 解决情况（Resolution）
- **Resolved**: 2026-09-16T23:02:00+08:00
- **Commit/PR**:
- **Notes**: 已改用无管道解析歧义的诊断命令完成环境检查。

---
