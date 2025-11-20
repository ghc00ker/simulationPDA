# 样例框架说明

本框架为 2025年 秋季《形式语言与自动机》课程的样例框架。助教们将使用该框架对同学们的程序进行测试，请确保你的工程可以使用该框架编译。

## 测试环境参考

本框架依赖于 cmake 进行编译，需安装 3.23.0 或以上版本 cmake 方可使用。其它：

- 请使用 Linux
- 测试环境里 g++ 版本为 13.3.0

## 使用方法

本框架使用方法：

1. 将所有 `.h` 及 `.cpp` 文件置于 `/pda-project`文件夹下，或者将该框架的 `CMakeLists.txt` 复制至你的工程根目录
2. 在工程根目录处，使用指令 `cmake -B build`
3. 在工程根目录处，使用指令 `cd ./build; make`

对于任务一，我们的测试框架将使用上述两条指令对工程进行编译。执行完毕后，在工程根目录下应当出现 `/bin` 文件夹，其中含有可执行文件 `pda`，测试框架将对该可执行文件进行测试。

对于任务二，请将括号匹配PDA文件 `case.pda` 直接放置于项目根目录

**注意事项**：
提交时，你的工程根目录下应当有一个 `CMakeLists.txt` 文件用于指导 cmake 进行编译，且通过这种方式能够在 `/bin` 文件夹下生成可执行文件 `pda`。请注意提交时不要附带相关 cmake cache 信息 (如 `/build`)，确保 cmake 能够重新生成Makefile。

- 可以修改 `CMakeLists.txt`，只要确保我们能够按照上述命令测试
  - 请不要修改 `cmake_minimum_required(VERSION 3.23.0)`

## 在线编译测试

我们会在 11 月 25 日左右开放测试接口，到时会在群里通知具体方法，请稍作等待。

## 打包与提交

将文件打包为如下结构：

```plain
学号_姓名_FLA25proj2.zip
    |- CMakeLists.txt
    |- README.md
    |- case.pda
    |- pda-project
        |- main.cpp
        |- ...
```

而非：

```plain
学号_姓名_FLA25proj2.zip
    |- 学号_姓名_FLA25proj2
        |- CMakeLists.txt
        |- README.md
        |- case.pda
        |- pda-project
            |- main.cpp
            |- ...
```

提交到 https://box.nju.edu.cn/u/d/f6e635c6f64f45f897c5/
