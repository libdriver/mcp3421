### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MCP3421

#### 3.1 Command Instruction

1. Show mcp3421 chip and driver information.

    ```shell
    mcp3421 (-i | --information)  
    ```

2. Show mcp3421 help.

    ```shell
    mcp3421 (-h | --help)        
    ```

3. Show mcp3421 pin connections of the current board.

    ```shell
    mcp3421 (-p | --port)        
    ```

4. Run mcp3421 register test.

    ```shell
    mcp3421 (-t reg | --test=reg)  
    ```

5. Run mcp3421 read test, num means test times.

    ```shell
    mcp3421 (-t read | --test=read) [--times=<num>]  
    ```

8. Run mcp3421 read function, num means read times.

    ```shell
    mcp3421 (-e read | --example=read) [--times=<num>]  
    ```

7. Run mcp3421 shot function, num means read times.

    ```shell
    mcp3421 (-e shot | --example=shot) [--times=<num>]    
    ```

#### 3.2 Command Example

```shell
mcp3421 -i

mcp3421: chip is Microchip MCP3421.
mcp3421: manufacturer is Microchip.
mcp3421: interface is IIC.
mcp3421: driver version is 1.0.
mcp3421: min supply voltage is 2.7V.
mcp3421: max supply voltage is 5.5V.
mcp3421: max current is 10.00mA.
mcp3421: max temperature is 125.0C.
mcp3421: min temperature is -40.0C.
```

```shell
mcp3421 -p

mcp3421: SCL connected to GPIOB PIN8.
mcp3421: SDA connected to GPIOB PIN9.
```

```shell
mcp3421 -t reg

mcp3421: chip is Microchip MCP3421.
mcp3421: manufacturer is Microchip.
mcp3421: interface is IIC.
mcp3421: driver version is 1.0.
mcp3421: min supply voltage is 2.7V.
mcp3421: max supply voltage is 5.5V.
mcp3421: max current is 10.00mA.
mcp3421: max temperature is 125.0C.
mcp3421: min temperature is -40.0C.
mcp3421: start register test.
mcp3421: mcp3421_set_adc_bit/mcp3421_get_adc_bit test.
mcp3421: set adc 12 bit.
mcp3421: check adc bit ok.
mcp3421: set adc 14 bit.
mcp3421: check adc bit ok.
mcp3421: set adc 16 bit.
mcp3421: check adc bit ok.
mcp3421: set adc 18 bit.
mcp3421: check adc bit ok.
mcp3421: mcp3421_set_pga/mcp3421_get_pga test.
mcp3421: set pga 1.
mcp3421: check pga ok.
mcp3421: set pga 2.
mcp3421: check pga ok.
mcp3421: set pga 4.
mcp3421: check pga ok.
mcp3421: set pga 8.
mcp3421: check pga ok.
mcp3421: finish register test.
```

```shell
mcp3421 -t read --times=3

mcp3421: chip is Microchip MCP3421.
mcp3421: manufacturer is Microchip.
mcp3421: interface is IIC.
mcp3421: driver version is 1.0.
mcp3421: min supply voltage is 2.7V.
mcp3421: max supply voltage is 5.5V.
mcp3421: max current is 10.00mA.
mcp3421: max temperature is 125.0C.
mcp3421: min temperature is -40.0C.
mcp3421: start read test.
mcp3421: set adc 12bits.
mcp3421: adc is 0.493000V.
mcp3421: adc is 0.493000V.
mcp3421: adc is 0.493000V.
mcp3421: set adc 14bits.
mcp3421: adc is 0.493000V.
mcp3421: adc is 0.493000V.
mcp3421: adc is 0.493000V.
mcp3421: set adc 16bits.
mcp3421: adc is 0.428500V.
mcp3421: adc is 0.493125V.
mcp3421: adc is 0.493188V.
mcp3421: set adc 18bits.
mcp3421: adc is 0.493109V.
mcp3421: adc is 0.493109V.
mcp3421: adc is 0.493141V.
mcp3421: set pga 2.
mcp3421: adc is 0.473695V.
mcp3421: adc is 0.493430V.
mcp3421: adc is 0.493414V.
mcp3421: set pga 4.
mcp3421: adc is 0.493027V.
mcp3421: adc is 0.473168V.
mcp3421: adc is 0.492918V.
mcp3421: continuous read test.
mcp3421: adc is 0.493172V.
mcp3421: adc is 0.478375V.
mcp3421: adc is 0.473297V.
mcp3421: finish read test.
```

```shell
mcp3421 -e read --times=3 

mcp3421: 1/3.
mcp3421: adc is 0.4930V.
mcp3421: 2/3.
mcp3421: adc is 0.4732V.
mcp3421: 3/3.
mcp3421: adc is 0.4732V.
```

```shell
mcp3421 -e shot --times=3 

mcp3421: 1/3.
mcp3421: adc is 0.4929V.
mcp3421: 2/3.
mcp3421: adc is 0.4733V.
mcp3421: 3/3.
mcp3421: adc is 0.4929V.
```

```shell
mcp3421 -h

Usage:
  mcp3421 (-i | --information)
  mcp3421 (-h | --help)
  mcp3421 (-p | --port)
  mcp3421 (-t reg | --test=reg)
  mcp3421 (-t read | --test=read) [--times=<num>]
  mcp3421 (-e read | --example=read) [--times=<num>]
  mcp3421 (-e shot | --example shot) [--times=<num>]

Options:
  -e <read | shot>, --example=<read | shot>
                                    Run the driver example.
  -h, --help                        Show the help.
  -i, --information                 Show the chip information.
  -p, --port                        Display the pins used by this device to connect the chip.
  -t <reg | read>, --test=<reg | read>.
                                    Run the driver test.
      --times=<num>                 Set the running times.([default: 3])
```
