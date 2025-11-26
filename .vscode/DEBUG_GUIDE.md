# WSL C++ 调试指南

## 📋 环境要求

已安装：
- ✅ GDB 调试器
- ✅ C++ 编译器 (g++)
- ✅ CMake (3.23.0+)
- ✅ VS Code 扩展: C/C++ (Microsoft)

## 🚀 调试步骤

### 方法1: 使用 VS Code 图形界面调试

1. **打开源文件**
   - 打开要调试的文件（如 `PDA.cpp`）

2. **设置断点**
   - 在代码行号左侧点击，设置红点断点
   - 或按 `F9` 切换断点

3. **开始调试**
   - 按 `F5` 或点击左侧调试图标
   - 选择 "(gdb) 调试 PDA"
   - 程序会自动编译并运行到断点处

4. **调试控制**
   - `F5` - 继续运行
   - `F10` - 单步跳过（不进入函数）
   - `F11` - 单步进入（进入函数内部）
   - `Shift+F11` - 跳出当前函数
   - `Ctrl+Shift+F5` - 重启调试
   - `Shift+F5` - 停止调试

5. **查看变量**
   - 左侧面板会显示所有局部变量
   - 鼠标悬停在变量上可查看值
   - 在"监视"窗口添加表达式

### 方法2: 使用命令行 GDB 调试

```bash
# 1. 编译 Debug 版本
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cd build && make

# 2. 启动 GDB
cd ..
gdb ./bin/pda

# 3. GDB 常用命令
(gdb) break PDA.cpp:125          # 在第125行设置断点
(gdb) run anbn.pda aaabbb        # 运行程序带参数
(gdb) print curr_state           # 打印变量
(gdb) print curr_stack           # 打印栈
(gdb) next                       # 单步跳过
(gdb) step                       # 单步进入
(gdb) continue                   # 继续运行
(gdb) backtrace                  # 查看调用栈
(gdb) info locals                # 查看所有局部变量
(gdb) quit                       # 退出
```

## 🔧 修改调试参数

### 修改输入参数

编辑 `.vscode/launch.json`：

```json
"args": ["anbn.pda", "aaabbb"],  // 修改这里的参数
```

或使用 "(gdb) 调试 PDA - 自定义参数" 配置（args为空）

### 修改工作目录

```json
"cwd": "${workspaceFolder}",  // 当前工作目录
```

## 🐛 常见调试技巧

### 1. 查看容器内容

```cpp
// 在断点处，在"调试控制台"输入：
-exec print curr_stack
-exec print func
```

### 2. 条件断点

- 右键断点 → 编辑断点 → 添加条件
- 例如：`i == 5` (只在i等于5时暂停)

### 3. 监视表达式

在"监视"窗口添加：
- `curr_state`
- `curr_stack.size()`
- `str[i]`

### 4. 查看函数调用栈

调试时查看"调用堆栈"面板，了解函数调用顺序

## 📝 编译选项说明

### Debug 模式 (当前)
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
```
- 包含调试符号 (`-g`)
- 禁用优化 (`-O0`)
- 启用警告 (`-Wall`)
- **适合调试**

### Release 模式
```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build
```
- 最高优化 (`-O3`)
- 无调试符号
- **适合最终提交**

## 🎯 快速调试示例

### 场景：调试 PDA::run() 函数

1. 在 `PDA.cpp` 第122行设置断点（for循环）
2. 按 `F5` 启动调试
3. 程序暂停在断点
4. 查看变量：
   - `state` - 当前状态
   - `curr_stack` - 栈内容
   - `str` - 输入字符串
5. 按 `F10` 逐步执行
6. 观察变量变化

## 💡 提示

- 调试前确保代码已保存
- Debug 模式编译较慢，正常现象
- 提交作业前用 Release 模式编译
- 可以在调试控制台输入 GDB 命令

## 🔍 验证调试环境

运行以下命令检查：

```bash
gdb --version          # 检查 GDB 是否安装
cmake --version        # 检查 CMake 版本
g++ --version          # 检查编译器版本
```

祝调试顺利！🎉

