/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_mcp3421.h
 * @brief     driver mcp3421 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-05-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/05/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_MCP3421_H
#define DRIVER_MCP3421_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup mcp3421_driver mcp3421 driver function
 * @brief    mcp3421 driver modules
 * @{
 */

/**
 * @addtogroup mcp3421_base_driver
 * @{
 */

/**
 * @brief mcp3421 bit enumeration definition
 */
typedef enum
{
    MCP3421_BIT_12 = 0x00,        /**< 240 sps 12 bits */
    MCP3421_BIT_14 = 0x01,        /**< 60 sps 14 bits */
    MCP3421_BIT_16 = 0x02,        /**< 15 sps 16 bits */
    MCP3421_BIT_18 = 0x03,        /**< 3.75 sps 18 bits */
} mcp3421_bit_t;

/**
 * @brief mcp3421 pga enumeration definition
 */
typedef enum
{
    MCP3421_PGA_1 = 0x00,        /**< pga 1 */
    MCP3421_PGA_2 = 0x01,        /**< pga 2 */
    MCP3421_PGA_4 = 0x02,        /**< pga 4 */
    MCP3421_PGA_8 = 0x03,        /**< pga 8 */
} mcp3421_pga_t;

/**
 * @brief mcp3421 handle structure definition
 */
typedef struct mcp3421_handle_s
{
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t config;                                                            /**< config */
    uint8_t inited;                                                            /**< inited flag */
} mcp3421_handle_t;

/**
 * @brief mcp3421 information structure definition
 */
typedef struct mcp3421_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} mcp3421_info_t;

/**
 * @}
 */

/**
 * @defgroup mcp3421_link_driver mcp3421 link driver function
 * @brief    mcp3421 link driver modules
 * @ingroup  mcp3421_driver
 * @{
 */

/**
 * @brief     initialize mcp3421_handle_t structure
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] STRUCTURE is mcp3421_handle_t
 * @note      none
 */
#define DRIVER_MCP3421_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_MCP3421_LINK_IIC_INIT(HANDLE, FUC)            (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_MCP3421_LINK_IIC_DEINIT(HANDLE, FUC)          (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_MCP3421_LINK_IIC_READ_COMMAND(HANDLE, FUC)    (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_MCP3421_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)   (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_MCP3421_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an mcp3421 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_MCP3421_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup mcp3421_base_driver mcp3421 base driver function
 * @brief    mcp3421 base driver modules
 * @ingroup  mcp3421_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an mcp3421 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mcp3421_info(mcp3421_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an mcp3421 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t mcp3421_init(mcp3421_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an mcp3421 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t mcp3421_deinit(mcp3421_handle_t *handle);

/**
 * @brief      read data from the chip once
 * @param[in]  *handle points to an mcp3421 handle structure
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 read timeout
 * @note       none
 */
uint8_t mcp3421_single_read(mcp3421_handle_t *handle, int32_t *raw, double *v);

/**
 * @brief     start the chip reading
 * @param[in] *handle points to an mcp3421 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp3421_start_continuous_read(mcp3421_handle_t *handle);

/**
 * @brief     stop the chip reading
 * @param[in] *handle points to an mcp3421 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp3421_stop_continuous_read(mcp3421_handle_t *handle);

/**
 * @brief      read data from the chip continuously
 * @param[in]  *handle points to an mcp3421 handle structure
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       this function can be used only after run mcp3421_start_continuous_read
 *             and can be stopped by mcp3421_stop_continuous_read
 */
uint8_t mcp3421_continuous_read(mcp3421_handle_t *handle, int32_t *raw, double *v);

/**
 * @brief     set the adc bit
 * @param[in] *handle points to an mcp3421 handle structure
 * @param[in] adc_bit is the set adc bit
 * @return    status code
 *            - 0 success
 *            - 1 set adc bit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp3421_set_adc_bit(mcp3421_handle_t *handle, mcp3421_bit_t adc_bit);

/**
 * @brief      get the adc bit
 * @param[in]  *handle points to an mcp3421 handle structure
 * @param[out] *adc_bit points to an adc bit buffer
 * @return     status code
 *             - 0 success
 *             - 1 get adc bit failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp3421_get_adc_bit(mcp3421_handle_t *handle, mcp3421_bit_t *adc_bit);

/**
 * @brief     set the adc pga
 * @param[in] *handle points to an mcp3421 handle structure
 * @param[in] pga is the set pga
 * @return    status code
 *            - 0 success
 *            - 1 set pga failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp3421_set_pga(mcp3421_handle_t *handle, mcp3421_pga_t pga);

/**
 * @brief      get the adc pga
 * @param[in]  *handle points to an mcp3421 handle structure
 * @param[out] *pga points to a pga buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pga failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp3421_get_pga(mcp3421_handle_t *handle, mcp3421_pga_t *pga);

/**
 * @}
 */

/**
 * @defgroup mcp3421_extend_driver mcp3421 extend driver function
 * @brief    mcp3421 extend driver modules
 * @ingroup  mcp3421_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an mcp3421 handle structure
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp3421_set_reg(mcp3421_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an mcp3421 handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp3421_get_reg(mcp3421_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
