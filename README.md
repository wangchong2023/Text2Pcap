# Text2Pcap - 16进制报文转换工具

Text2Pcap 是一款基于 Qt 开发的跨平台报文解析工具，旨在帮助网络开发人员和运维工程师将原本不可读的 16 进制报文数据快速转换为标准的 `.pcap` 或 `.pcapng` 格式文件，方便使用 Wireshark 等工具进行深入分析。

## 主要功能

- **多格式支持**：支持解析纯 16 进制流 (Hex Stream) 和 Hex Dump 格式的文本数据。
- **智能填充**：支持不同层级的报文头自动填充，包括：
  - 链路层 (Link Layer)
  - IPv4 层 (IPv4 Layer)
  - IPv6 层 (IPv6 Layer)
  - TCP/UDP 层 (TCP/UDP Layer)
  - 自定义参数（如链路类型、协议号、源/目的端口等）
- **导出灵活**：支持导出为 `.pcap` 和 `.pcapng` 两种主流格式。
- **集成调试**：可配置关联本地 Wireshark 路径，转换后直接调用 Wireshark 打开文件。
- **便捷操作**：支持一键清空、复制报文内容的剪贴板操作。
- **跨平台**：支持 Windows、macOS 和 Linux (需自行编译)。

## 构建环境

本项目使用 Qt 框架开发，构建前请确保已安装以下环境：

- **Qt 6.x** (推荐 Qt 6.5 LTS 或更高，当前使用 Qt 6.10.2)
- **C++ 编译器** (MSVC, GCC, Clang 等)
- **qmake** 构建工具

**依赖项**：

- 项目依赖 `ThirdPart/SingleApplication` 模块（已包含在源码中），用于实现单实例运行。

## 编译与安装

1. **克隆仓库**：

   ```bash
   git clone <repository-url>
   cd Text2Pcap
   ```

2. **使用 Qt Creator 构建**：
   - 打开 `Text2Pcap/Text2Pcap.pro` 文件。
   - 配置构建套件 (Kit)。
   - 点击构建 (Build) 按钮。

3. **使用命令行构建**：

   ```bash
   cd Text2Pcap
   mkdir build
   cd build
   qmake ../Text2Pcap.pro
   make  # Windows 下使用 nmake 或 jom
   ```

## 使用说明

1. **配置路径**：
   - 首次运行建议在设置中配置 Wireshark 可执行文件路径以及生成的 pcap 文件存储路径。

2. **输入报文**：
   - 在主界面的文本框中粘贴 16 进制报文内容。
   - 选择输入内容的格式（Hex Stream 或 Hex Dump）。

3. **设置填充选项** (可选)：
   - 如果是完整报文，选择 "No Pad" (不填充)。
   - 如果是部分报文（如仅有应用层数据），可选择填充到 TCP/UDP 层、IPv4 层或链路层，并填写相应的端口号或协议号。

4. **解析与导出**：
   - 选择输出格式 (.pcap/.pcapng)。
   - 点击解析按钮，程序将生成文件并提示成功，若配置了 Wireshark 路径将尝试自动打开。

## 许可证

本项目采用 MIT 许可证。详情请参阅 [LICENSE](LICENSE) 文件。
