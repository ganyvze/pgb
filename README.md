# Plain Game Box

Plain Game Box 是一个基于 C++ 和 Windows 控制台的小游戏合集，提供多种经典益智、反应和文字游戏。游戏支持彩色控制台显示、成绩记录、随机种子以及历史文件管理。

## 游戏列表

1. **Minesweeper - Classic**
   - 经典扫雷
   - 自定义棋盘大小
   - 使用 `x.y` 打开格子，使用 `x/y` 标记或取消标记

2. **Minesweeper - Diamond Finder**
   - 特殊扫雷玩法
   - 在雷区中寻找钻石
   - 3×3 井字棋
   - 支持简单、普通和困难三种 AI 难度
   - 可选择使用 `X` 或 `O`

4. **Trap Maze**
   - 随机生成迷宫
   - 需要避开陷阱并从起点 `S` 抵达终点 `E`
   - 支持简单、普通和困难三种难度

5. **2048**
   - 4×4 数字合成游戏
   - 支持 `WASD`、`IJKL` 两组方向键
   - 统计输入速度、完成度和错误数量

7. **Sliding Puzzle**
   - 数字滑块拼图
   - 支持自定义拼图大小
   - 支持简单、普通和困难三种难度

8. **Plussing Game**
   - 从起点移动到终点
   - 使经过格子的数字总和等于目标值

## 运行环境

- Windows
- 支持 C++11 - C++17 的编译器
- Windows Console API
- `conio.h`
- `Windows.h`

推荐使用 Visual Studio 2019 或更高版本，或 MinGW-w64 GCC。

## 编译

### 使用 Visual Studio Developer Command Prompt

编译主游戏：

```bat
cl /std:c++17 /EHsc /utf-8 PlainGameBox.cpp /Fe:PlainGameBox.exe
```

编译历史文件工具：

```bat
cl /std:c++17 /EHsc /utf-8 FilePusher.cpp /Fe:FilePusher.exe
```

### 使用 MinGW-w64

编译主游戏：

```bash
g++ -std=c++17 -O2 PlainGameBox.cpp -o PlainGameBox.exe
```

编译历史文件工具：

```bash
g++ -std=c++17 -O2 FilePusher.cpp -o FilePusher.exe
```

## 启动

编译完成后运行：

```bat
PlainGameBox.exe
```

主菜单中可以选择游戏、查看历史成绩、修改设置或退出程序。

## 通用操作

- 在菜单中输入对应编号选择游戏
- 输入 `/hub` 返回上一级菜单
- 部分游戏中按 `Tab` 打开退出确认
- 游戏方向控制通常支持：
  - `W` 或 `I`：向上
  - `S` 或 `K`：向下
  - `A` 或 `J`：向左
  - `D` 或 `L`：向右

## 成绩记录

游戏结束后，成绩会自动保存到当前历史文件中。

默认历史文件：

```text
GameHistory.bin
```

主菜单中的 **Check history score** 可以：

- 查看所有游戏成绩
- 为记录添加标签
- 删除单条记录
- 删除一段记录
- 删除全部记录
- 重新加载历史文件
- 对记录进行排序
- 交换两条记录

历史文件使用二进制格式保存，请不要直接使用文本编辑器修改。

## 合并历史文件

主菜单进入 **设置**，选择 **合并其他历史文件**，然后输入需要合并的 `.bin` 文件名，例如：

```text
backup.bin
```

程序会将其中的记录追加到当前正在使用的历史文件中。

## 设置

游戏内置以下设置：

- **Eye protection mode**
  - 关闭颜色变化
  - 兼容旧版 Windows 控制台

- **Set random seed**
  - 设置固定随机种子
  - 便于复现相同的地图或题目
  - 输入 `0` 可恢复使用当前时间作为随机种子

- **Testing mode**
  - 开启后不会保存游戏历史

- **Quick output**
   - 关闭打字机输出效果，直接输出文字

- **Use other history file names**
  - 使用自定义的 `.bin` 历史文件

- **Merge other history files**
   - 将另一个 `.bin` 历史文件中的记录追加到当前历史文件

## 项目结构

```text
PlainGameBox.cpp    主程序入口
FilePusher.cpp      独立的历史文件合并工具（兼容入口）
game.hpp            主菜单、设置和历史记录功能
heads.hpp           公共头文件和类型定义
tools.hpp           输入、随机数、颜色和控制台工具
Minesweeper.hpp     扫雷
tic_tac_toe.hpp     井字棋
Maze.hpp            陷阱迷宫
_2048.hpp           2048
TypingGame.hpp      打字游戏
SlidingPuzzle.hpp   滑块拼图
PlussingGame.hpp    加法路径游戏
```

## 注意事项

- 本项目依赖 Windows 控制台 API，暂不保证可直接运行于 Linux 或 macOS。
- 请在支持 Windows 控制台输入的终端中运行。
- 游戏运行目录需要具有创建和修改 `GameHistory.bin` 的权限。
- 如果历史文件损坏，建议备份后删除该文件，再重新运行游戏。
