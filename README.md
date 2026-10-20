# DeviceDesk_AutoManage

设备桌面自动化管理系统（DeviceDesk AutoManage）。

> 当前处于**早期骨架阶段**：已搭建 Qt6 + CMake 工程结构，并实现了「客户端 ↔ 模拟器」的 TCP 通信最小闭环，作为后续设备通信模块的验证基础。

## 当前进度

- [x] Qt6（Core / Network / Widgets）+ CMake 工程骨架
- [x] `device_desk_client`：基于 Qt Widgets 的图形客户端，通过 TCP 连接模拟器
- [x] `device_simulator`：基于 `QTcpServer` 的本地设备模拟器
- [x] 客户端 ↔ 模拟器 TCP 通信（`127.0.0.1:9000`）
- [x] VS Code + CMake Tools 一键配置 / 构建
- [x] 源码模块化：`src/CMakeLists.txt` 统一管理子模块（`communication` 接口库）
- [ ] 设备通信协议封装（`src/communication`，已定义 `message_header` 结构体）
- [ ] 核心业务逻辑（`src/core`）
- [ ] 数据库持久化（`src/database`）
- [ ] UI 界面完善（`src/ui`）
- [ ] 自动化测试（`tests`）

## 技术栈

| 项目 | 版本 / 说明 |
|------|-------------|
| 语言 | C++20 |
| GUI | Qt 6（Widgets） |
| 网络 | Qt Network（TCP） |
| 构建 | CMake ≥ 3.21 + CMake Presets |
| 编译器 | MSVC 2022（Visual Studio 17 2022） |

## 目录结构

```
DeviceDesk_AutoManage/
├── apps/
│   ├── client/          # 图形客户端（Qt Widgets）
│   └── simulator/       # 设备模拟器（TCP 服务端）
├── src/
│   ├── CMakeLists.txt   # 统一管理各子模块 target
│   ├── communication/   # 通信层（进行中：message_header）
│   ├── core/            # 核心业务（待实现）
│   ├── database/        # 数据持久化（待实现）
│   └── ui/              # UI 组件（待实现）
├── resources/
│   ├── icons/           # 图标资源
│   └── qss/             # Qt 样式表
├── configs/             # 配置文件
├── docs/                # 文档
├── tests/               # 测试
├── CMakeLists.txt
└── CMakePresets.json
```

## 环境要求

- **Qt 6**（本仓库预设默认指向 `D:/QT/6.12.0/msvc2022_64`）
- **Visual Studio 2022**（含「使用 C++ 的桌面开发」工作负载）
- **CMake ≥ 3.21**
- **VS Code**（推荐），扩展：`C/C++`、`CMake Tools`

## 构建

### 1. 修改 Qt 路径

[`CMakePresets.json`](CMakePresets.json) 中 `CMAKE_PREFIX_PATH` 默认指向 `D:/QT/6.12.0/msvc2022_64`，请改为你本机的 Qt 安装路径。

> 建议不要把本地路径提交到仓库：可新建 `CMakeUserPresets.json`（已被 `.gitignore` 忽略）来覆盖该变量。

### 2. 配置

VS Code 中已通过 `.vscode/settings.json` 默认选中 `windows-msvc-debug` 预设；命令行可用：

```bash
cmake --preset windows-msvc-debug
```

可选预设：

| 预设 | 说明 |
|------|------|
| `windows-msvc-debug` | Debug 构建 |
| `windows-msvc-release` | Release 构建 |

### 3. 编译

```bash
cmake --build build/windows-msvc-debug --config Debug
```

或在 VS Code 中使用 **CMake: 构建**（`F7`）。

## 运行

> **顺序很重要**：先启动模拟器，再启动客户端。

1. 启动模拟器：
   ```
   build/windows-msvc-debug/apps/simulator/Debug/device_simulator.exe
   ```
2. 启动客户端：
   ```
   build/windows-msvc-debug/apps/client/Debug/device_desk_client.exe
   ```

客户端连接成功后，窗口显示 `DeviceSimulator connected`；模拟器控制台输出：

```
Device simulator listening on 127.0.0.1:9000
Client connected: QHostAddress("127.0.0.1") ...
Received: "HELLO\n"
```

## 通信协议（当前验证版）

- 地址 / 端口：`127.0.0.1:9000`（TCP）
- 客户端连接后发送：`HELLO\n`
- 模拟器收到数据后回复：`SIMULATOR_OK\n`

> 这是用于验证通信链路的最小实现，正式的设备通信协议将在 `src/communication` 中定义。

当前 `src/communication` 已建立 `communication` 接口库（链接 `Qt6::Core`），并定义了消息头结构体 `message_header`（`magic` / `version` / `message_type` / `body_length`），用于后续统一报文格式。

## 运行 Debug 版的依赖说明

Debug 版可执行文件需要 Qt 调试版 DLL 和 MSVC 调试运行时（文件名带 `d` 的 DLL）。双击运行时若提示缺少 DLL，可用 Qt 自带的部署工具补齐：

```bash
windeployqt --debug --no-translations build/windows-msvc-debug/apps/client/Debug/device_desk_client.exe
```

## License

（待定）

---

> 文档最后更新时间：2026-10-21 00:34:28（UTC+8）