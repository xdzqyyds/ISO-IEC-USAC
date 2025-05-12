---

# 🎛️ USAC 编码器 / 解码器 使用说明文档

---

## 🛠️ 环境配置

### 🐧 Linux / 🍎 macOS

* ✅ 依赖项：

  * `GNU Make`
  * `GCC >= 4.4.5`

### 🪟 Windows

* ✅ 依赖项：

  * `Visual Studio 2012`
  * `Windows SDK`
  * 设置环境变量 `VS110COMNTOOLS`

---

## 🧱 Windows 编译指南

### ✅ 编译步骤：

1. 进入 `scripts` 目录：

   ```cmd
   cd scripts
   ```

2. 执行编译脚本：

   ```cmd
   compile.bat x64
   ```

3. 编译成功后，`executables_*` 目录下应生成以下可执行文件：

   * `usacEnc.exe`（编码器）
   * `usacDec.exe`（解码器）
   * `wavCutterCmdl.exe`（WAV 裁剪工具）
   * `drcToolEncoder.exe`（DRC 编码器）
   * `drcToolDecoder.exe`（DRC 解码器）
   * `ssnrcd.exe`（音频相似度比较工具）

---

## ⚙️ 高级编译选项

### 🐧 Linux / 🍎 macOS

```bash
./compile.sh Clean        # 清理构建产物  
./compile.sh Release      # 发布模式构建  
./compile.sh c89          # 使用 C89 标准构建  
./compile.sh co           # 检出依赖库（如 libisomediafile）  
./compile.sh co GIT       # 使用 GIT 方式检出依赖  
```

### 🪟 Windows

```cmd
compile.bat x64           # 构建 64 位版本  
compile.bat Release       # 构建发布版本  
compile.bat VS2008        # 使用 VS2008 编译  
compile.bat co            # 检出依赖库  
compile.bat co GIT        # 使用 GIT 检出依赖  
```

---

## 🎧 编码器说明（`usacEnc.exe`）

### 🎧 编码器参数说明

- 对于立体声输入和比特率<64kbps的情况，MPEG Surround立体声编码会自动激活。
- 对于立体声输入和比特率>=64kbps的情况，会激活离散立体声编码。

### 📌 示例：

```bash
usacEnc -if input.wav -of encoded.mp4 -br 96000 -sbrRatioIndex 3 -nodrc -vv
```

> 输入文件为 `input.wav`，输出 `encoded.mp4`，使用 `96 kbps` 比特率，`2:1 SBR 1024`，禁用 `DRC`，此时只依赖 `usacEnc.exe` 这一个可执行文件

### 🔣 参数类型说明：

* `<s>`：字符串
* `<i>`：整数
* `<ui>`：无符号整数
* `<f>`：浮点数

### 🔧 基本参数：

| 参数        | 类型 | 说明             |
| --------- | -- | -------------- |
| `-h`      |    | 显示帮助信息         |
| `-xh`     |    | 显示扩展帮助信息       |
| `-if <s>` | 必选 | 输入 WAV 文件路径    |
| `-of <s>` | 必选 | 输出 MP4 文件路径    |
| `-br <i>` | 必选 | 比特率设置（单位：kbps） |

### 🧩 可选参数：

| 参数                   | 说明                            |
| -------------------- | ----------------------------- |
| `-numChannelOut <i>` | 输出声道数（0 = 与输入相同）              |
| `-fSampleOut <i>`    | 输出采样率（0 = 与输入相同）              |
| `-drcConfigFile <s>` | DRC 配置 XML 文件路径               |
| `-drcGainFile <s>`   | DRC 增益数据文件路径                  |
| `-bw <i>`            | 设置音频带宽（单位：Hz）                 |
| `-streamID <ui>`     | 设置流标识符                        |
| `-drc`               | 启用 DRC 编码                     |
| `-cfg <s>`           | 使用二进制配置文件                     |
| `-usac_switched`     | 启用 USAC 切换编码（默认）              |
| `-usac_fd`           | 启用 USAC 频域编码                  |
| `-usac_td`           | 启用 USAC 时域编码                  |
| `-noSbr`             | 禁用 SBR 工具                     |
| `-sbrRatioIndex <i>` | 设置 SBR 比率索引（0\~3）             |
| `-mps_res`           | 启用 MPEG Surround 残差（需开启 SBR）  |
| `-hSBR`              | 启用 SBR 的谐波拼接                  |
| `-ms <0,1,2>`        | 中-侧立体声掩码方式（默认：1）              |
| `-wshape`            | 使用 WS\_DOLBY 窗函数替代默认的 WS\_FHG |
| `-deblvl <0,1>`      | 设置调试等级（默认：0）                  |
| `-v` / `-vv`         | 启用详细输出（1级 / 2级）               |
| `-nogc`              | 禁用垃圾回收机制                      |

---

## 🔊 解码器说明（`usacDec.exe`）

### 📌 示例：

```bash
usacDec -if encoded.mp4 -of output.wav -bitdepth 16 -nodrc -cpo 0 -v
```

> 解码 `encoded.mp4` 到 `output.wav`，设置输出为 `16` 位 `PCM`，禁用 `DRC`，完整输出，此时依赖 `usacDec.exe、wavCutterCmdl.exe` 这两个可执行文件，`drcToolDecoder.exe` 需存在，但内容可为空

### 🔣 参数类型说明：

* `<s>`：字符串
* `<i>`：整数
* `<f>`：浮点数

### 🔧 基本参数：

| 参数        | 类型 | 说明          |
| --------- | -- | ----------- |
| `-if <s>` | 必选 | 输入 MP4 文件路径 |
| `-of <s>` | 必选 | 输出 WAV 文件路径 |

### 🧩 可选参数：

| 参数                          | 说明                     |
| --------------------------- | ---------------------- |
| `-bitdepth <i>`             | 解码输出位深（例如：16 或 24）     |
| `-use24bitChain`            | 启用 24 位内部处理链（默认开启）     |
| `-drcInterface <s>`         | 指定 DRC 接口文件路径          |
| `-targetLoudnessLevel <f>`  | 设置目标响度（单位：LKFS）        |
| `-drcEffectTypeRequest <i>` | 请求特定类型的 DRC 效果（十六进制格式） |
| `-nodrc`                    | 禁用 DRC 功能              |
| `-nogc`                     | 禁用垃圾回收机制               |
| `-cpo <i>`                  | 一致性输出模式（0 = 完整输出）      |
| `-deblvl <0,1>`             | 设置调试等级（默认：0）           |
| `-v` / `-vv`                | 启用详细输出（1级 / 2级）        |

---

## 🧪 测试工具：音频对比

### 🧭 指令：

```bash
ssnrcd input.wav output.wav
```

> 比较原始音频与解码音频之间的差异，评估保真度和压缩效果。

---
