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
 * @file      driver_mcp3421_basic.c
 * @brief     driver mcp3421 basic source file
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

#include "driver_mcp3421_basic.h"

static mcp3421_handle_t gs_handle;        /**< mcp3421 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t mcp3421_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_MCP3421_LINK_INIT(&gs_handle, mcp3421_handle_t); 
    DRIVER_MCP3421_LINK_IIC_INIT(&gs_handle, mcp3421_interface_iic_init);
    DRIVER_MCP3421_LINK_IIC_DEINIT(&gs_handle, mcp3421_interface_iic_deinit);
    DRIVER_MCP3421_LINK_IIC_READ_COMMAND(&gs_handle, mcp3421_interface_iic_read_cmd);
    DRIVER_MCP3421_LINK_IIC_WRITE_COMMAND(&gs_handle, mcp3421_interface_iic_write_cmd);
    DRIVER_MCP3421_LINK_DELAY_MS(&gs_handle, mcp3421_interface_delay_ms);
    DRIVER_MCP3421_LINK_DEBUG_PRINT(&gs_handle, mcp3421_interface_debug_print);
    
    /* mcp3421 init */
    res = mcp3421_init(&gs_handle);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: init failed.\n");
        
        return 1;
    }
    
    /* set default pag */
    res = mcp3421_set_pga(&gs_handle, MCP3421_BASIC_DEFAULT_PGA);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc bit */
    res = mcp3421_set_adc_bit(&gs_handle, MCP3421_BASIC_DEFAULT_BIT);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start continuous read */
    res = mcp3421_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: start continues read mode failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }

    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *s points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t mcp3421_basic_read(double *s)
{
    int32_t raw;
  
    /* read data */
    if (mcp3421_continuous_read(&gs_handle, (int32_t *)&raw, s) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mcp3421_basic_deinit(void)
{
    uint8_t res;
    
    /* stop continuous read */
    res = mcp3421_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* deinit mcp3421 */
    res = mcp3421_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
