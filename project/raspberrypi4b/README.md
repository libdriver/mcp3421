### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(mcp3421 REQUIRED)
```

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
./mcp3421 -i

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
./mcp3421 -p

mcp3421: SCL connected to GPIO3(BCM).
mcp3421: SDA connected to GPIO2(BCM).
```

```shell
./mcp3421 -t reg

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
./mcp3421 -t read --times=3

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
mcp3421: adc is 0.489000V.
mcp3421: adc is 0.492000V.
mcp3421: adc is 0.492000V.
mcp3421: set adc 14bits.
mcp3421: adc is 0.491500V.
mcp3421: adc is 0.374000V.
mcp3421: adc is 0.491750V.
mcp3421: set adc 16bits.
mcp3421: adc is 0.491750V.
mcp3421: adc is 0.491687V.
mcp3421: adc is 0.491687V.
mcp3421: set adc 18bits.
mcp3421: adc is 0.491750V.
mcp3421: adc is 0.491781V.
mcp3421: adc is 0.489891V.
mcp3421: set pga 2.
mcp3421: adc is 0.491711V.
mcp3421: adc is 0.492016V.
mcp3421: adc is 0.492102V.
mcp3421: set pga 4.
mcp3421: adc is 0.471996V.
mcp3421: adc is 0.491719V.
mcp3421: adc is 0.491687V.
mcp3421: continuous read test.
mcp3421: adc is 0.491734V.
mcp3421: adc is 0.491797V.
mcp3421: adc is 0.491750V.
mcp3421: finish read test.
```

```shell
./mcp3421 -e read --times=3

mcp3421: 1/3.
mcp3421: adc is 0.4918V.
mcp3421: 2/3.
mcp3421: adc is 0.4721V.
mcp3421: 3/3.
mcp3421: adc is 0.4721V.
```

```shell
./mcp3421 -e shot --times=3 

mcp3421: 1/3.
mcp3421: adc is 0.4918V.
mcp3421: 2/3.
mcp3421: adc is 0.4918V.
mcp3421: 3/3.
mcp3421: adc is 0.4918V.
```

```shell
./mcp3421 -h

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
