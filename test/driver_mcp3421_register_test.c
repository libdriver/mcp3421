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
 * @file      driver_mcp3421_register_test.c
 * @brief     driver mcp3421 register test source file
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
 
#include "driver_mcp3421_register_test.h"

static mcp3421_handle_t gs_handle;        /**< mcp3421 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t mcp3421_register_test(void)
{
    uint8_t res;
    mcp3421_bit_t adc_bit;
    mcp3421_pga_t pga;
    mcp3421_info_t info;

    /* link interface function */
    DRIVER_MCP3421_LINK_INIT(&gs_handle, mcp3421_handle_t); 
    DRIVER_MCP3421_LINK_IIC_INIT(&gs_handle, mcp3421_interface_iic_init);
    DRIVER_MCP3421_LINK_IIC_DEINIT(&gs_handle, mcp3421_interface_iic_deinit);
    DRIVER_MCP3421_LINK_IIC_READ_COMMAND(&gs_handle, mcp3421_interface_iic_read_cmd);
    DRIVER_MCP3421_LINK_IIC_WRITE_COMMAND(&gs_handle, mcp3421_interface_iic_write_cmd);
    DRIVER_MCP3421_LINK_DELAY_MS(&gs_handle, mcp3421_interface_delay_ms);
    DRIVER_MCP3421_LINK_DEBUG_PRINT(&gs_handle, mcp3421_interface_debug_print);
    
    /* get information */
    res = mcp3421_info(&info);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        mcp3421_interface_debug_print("mcp3421: chip is %s.\n", info.chip_name);
        mcp3421_interface_debug_print("mcp3421: manufacturer is %s.\n", info.manufacturer_name);
        mcp3421_interface_debug_print("mcp3421: interface is %s.\n", info.interface);
        mcp3421_interface_debug_print("mcp3421: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mcp3421_interface_debug_print("mcp3421: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mcp3421_interface_debug_print("mcp3421: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mcp3421_interface_debug_print("mcp3421: max current is %0.2fmA.\n", info.max_current_ma);
        mcp3421_interface_debug_print("mcp3421: max temperature is %0.1fC.\n", info.temperature_max);
        mcp3421_interface_debug_print("mcp3421: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    mcp3421_interface_debug_print("mcp3421: start register test.\n");
    
    /* mcp3421 init */
    res = mcp3421_init(&gs_handle);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: init failed.\n");
        
        return 1;
    }
    
    /* mcp3421_set_adc_bit/mcp3421_get_adc_bit test */
    mcp3421_interface_debug_print("mcp3421: mcp3421_set_adc_bit/mcp3421_get_adc_bit test.\n");
    
    /* set adc bit */
    res = mcp3421_set_adc_bit(&gs_handle, MCP3421_BIT_12);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set adc 12 bit.\n");
    res = mcp3421_get_adc_bit(&gs_handle, &adc_bit);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check adc bit %s.\n", adc_bit == MCP3421_BIT_12 ? "ok" : "error");
    
    /* set adc bit */
    res = mcp3421_set_adc_bit(&gs_handle, MCP3421_BIT_14);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set adc 14 bit.\n");
    res = mcp3421_get_adc_bit(&gs_handle, &adc_bit);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check adc bit %s.\n", adc_bit == MCP3421_BIT_14 ? "ok" : "error");
    
    /* set adc bit */
    res = mcp3421_set_adc_bit(&gs_handle, MCP3421_BIT_16);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set adc 16 bit.\n");
    res = mcp3421_get_adc_bit(&gs_handle, &adc_bit);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check adc bit %s.\n", adc_bit == MCP3421_BIT_16 ? "ok" : "error");
    
    /* set adc bit */
    res = mcp3421_set_adc_bit(&gs_handle, MCP3421_BIT_18);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set adc 18 bit.\n");
    res = mcp3421_get_adc_bit(&gs_handle, &adc_bit);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get adc bit failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check adc bit %s.\n", adc_bit == MCP3421_BIT_18 ? "ok" : "error");
    
    /* mcp3421_set_pga/mcp3421_get_pga test */
    mcp3421_interface_debug_print("mcp3421: mcp3421_set_pga/mcp3421_get_pga test.\n");
    
    /* set pag 1 */
    res = mcp3421_set_pga(&gs_handle, MCP3421_PGA_1);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set pga 1.\n");
    res = mcp3421_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check pga %s.\n", pga == MCP3421_PGA_1 ? "ok" : "error");
    
    /* set pag 2 */
    res = mcp3421_set_pga(&gs_handle, MCP3421_PGA_2);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set pga 2.\n");
    res = mcp3421_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check pga %s.\n", pga == MCP3421_PGA_2 ? "ok" : "error");
    
    /* set pag 4 */
    res = mcp3421_set_pga(&gs_handle, MCP3421_PGA_4);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set pga 4.\n");
    res = mcp3421_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check pga %s.\n", pga == MCP3421_PGA_4 ? "ok" : "error");
    
    /* set pag 8 */
    res = mcp3421_set_pga(&gs_handle, MCP3421_PGA_8);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: set pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: set pga 8.\n");
    res = mcp3421_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: get pga failed.\n");
        (void)mcp3421_deinit(&gs_handle);
        
        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: check pga %s.\n", pga == MCP3421_PGA_8 ? "ok" : "error");
    
    /* finish register */
    mcp3421_interface_debug_print("mcp3421: finish register test.\n");
    (void)mcp3421_deinit(&gs_handle);
    
    return 0;
}
