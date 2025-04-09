# MiniOS

## 简介

MiniOS 是一个基于 RISC-V 架构的简易实时操作系统。

## Quick Start

1. 安装依赖

请确保安装好 riscv-roolchain (编译需要) 和 openocd (烧写和Debug需要)，并添加到系统路径

2. 编译 miniOS

执行以下命令后可以见到 `build` 目录下生成 `miniOS.bin` 可执行文件。
```bash
mkdir build && cd build
cmake ..
make
```

3. 烧写到CH32V307

```bash
cd build
make flash
```
## Features List
- 支持动态内存管理
- 支持上下文切换和多任务
- 支持异常与中断处理
- 支持用户态隔离

### Application (TBC)

- minishell
- flybird
- miniplayer
- minislide

## 参考文档

- [CH32FV2x_V3xRM.PDF](doc/CH32FV2x_V3xRM.PDF)
- [CH32V307DS0.PDF](doc/CH32V307DS0.PDF)

已知问题
当进入while后使用中断会直接halt