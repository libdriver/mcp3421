[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP3421

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp3421/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MCP3421 is a single channel low-noise, high accuracy ΔΣ A/D converter with differential inputs and up to 18 bits of resolution in a small SOT-23-6 package.The on-board precision 2.048V reference voltage enables an input range of ±2.048V differentially (Δ voltage = 4.096V). The device uses a two-wire I2C compatible serial interface and operates from a single 2.7V to 5.5V power supply.The MCP3421 device performs conversion at rates of 3.75, 15, 60, or 240 samples per second (SPS) depending on the user controllable configuration bit settings using the two-wire I2C serial interface. This device has an on-board programmable gain amplifier (PGA). The user can select the PGA gain of x1, x2, x4, or x8 before the analog-to-digital conversion takes place. This allows the MCP3421 device to convert a smaller input signal with high resolution. The device has two conversion modes: (a) Continuous mode and (b) One-Shot mode. In One-Shot mode, the device enters a low current standby mode automatically after one conversion. This reduces current consumption greatly during idle periods.The MCP3421 device can be used for various high accuracy analog-to-digital data conversion applications where design simplicity, low power, and small footprint are major considerations.

LibDriver MCP3421 is the full function driver of MCP3421 launched by LibDriver. LibDriver MCP3421 provides continuous mode ADC conversion, single mode ADC conversion and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MCP3421 source files.

/interface includes LibDriver MCP3421 IIC platform independent template.

/test includes LibDriver MCP3421 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MCP3421 sample code.

/doc includes LibDriver MCP3421 offline document.

/datasheet includes MCP3421 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

```C
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

### Document

Online documents: [https://www.libdriver.com/docs/mcp3421/index.html](https://www.libdriver.com/docs/mcp3421/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.