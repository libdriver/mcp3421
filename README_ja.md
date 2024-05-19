[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP3421

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp3421/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MCP3421 は、小型 SOT-23-6 パッケージに差動入力と最大 18 ビットの分解能を備えた、シングル チャネルの低ノイズ、高精度 ΔΣ A/D コンバータです。オンボードの高精度 2.048V 基準電圧により、入力範囲が可能になります。 差動で±2.048V (Δ電圧 = 4.096V)。 このデバイスは 2 線 I2C 互換シリアル インターフェイスを使用し、2.7 ～ 5.5 V の単一電源で動作します。MCP3421 デバイスは、ユーザーに応じて 3.75、15、60、または 240 サンプル/秒 (SPS) のレートで変換を実行します。 2 線式 I2C シリアル インターフェイスを使用して制御可能なコンフィギュレーション ビット設定。 このデバイスには、オンボードのプログラマブル ゲイン アンプ (PGA) が搭載されています。 ユーザーは、アナログ - デジタル変換が行われる前に、PGA ゲインを x1、x2、x4、または x8 から選択できます。 これにより、MCP3421 デバイスはより小さな入力信号を高解像度で変換できます。 このデバイスには、(a) 連続モードと (b) ワンショット モードの 2 つの変換モードがあります。 ワンショット モードでは、デバイスは 1 回の変換後に自動的に低電流スタンバイ モードに入ります。 これにより、アイドル期間中の消費電流が大幅に削減されます。MCP3421 デバイスは、設計のシンプルさ、低消費電力、設置面積の小ささが主要な考慮事項となる、さまざまな高精度アナログ - デジタル データ変換アプリケーションに使用できます。

LibDriver MCP3421 は、LibDriver によって起動される MCP3421 の全機能ドライバーです。 LibDriver MCP3421 は、連続モード ADC 変換、シングル モード ADC 変換、その他の機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MCP3421のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MCP3421用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MCP3421ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MCP3421プログラミング例が含まれています。

/ docディレクトリには、LibDriver MCP3421オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MCP3421データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_mcp3421_basic.h"

uint8_t res;
uint32_t i;
double s;

/* basic init */
res = mcp3421_basic_init();
if (res != 0)
{
    mcp3421_interface_debug_print("mcp3421: basic init failed.\n");

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* read the data */
    res = mcp3421_basic_read((double *)&s);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: basic read failed.\n");
        (void)mcp3421_basic_deinit();

        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: %d/%d.\n", i + 1, 3);
    mcp3421_interface_debug_print("mcp3421: adc is %0.4fV.\n", s);
    mcp3421_interface_delay_ms(1000);
    
    ...
}

...
    
(void)mcp3421_basic_deinit();

return 0;
```

#### example shot

```c
#include "driver_mcp3421_shot.h"

uint8_t res;
uint32_t i;
double s;

/* shot init */
res = mcp3421_shot_init();
if (res != 0)
{
    mcp3421_interface_debug_print("mcp3421: basic init failed.\n");

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* read the data */
    res = mcp3421_shot_read((double *)&s);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: basic read failed.\n");
        (void)mcp3421_shot_deinit();

        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: %d/%d.\n", i + 1, 3);
    mcp3421_interface_debug_print("mcp3421: adc is %0.4fV.\n", s);
    mcp3421_interface_delay_ms(1000);
    
    ...
}

...
    
(void)mcp3421_shot_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/mcp3421/index.html](https://www.libdriver.com/docs/mcp3421/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。