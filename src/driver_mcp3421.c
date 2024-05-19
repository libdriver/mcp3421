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
 * @file      driver_mcp3421.c
 * @brief     driver mcp3421 source file
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

#include "driver_mcp3421.h"
#include <math.h>

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Microchip MCP3421"        /**< chip name */
#define MANUFACTURER_NAME         "Microchip"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                       /**< chip max supply voltage */
#define MAX_CURRENT               10.0f                      /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                     /**< chip max operating temperature */
#define DRIVER_VERSION            1000                       /**< driver version */

/**
 * @brief iic address definition
 */
#define MCP3421_ADDRESS        (0xD0)        /**< iic address */

/**
 * @brief      read bytes
 * @param[in]  *handle points to an mcp3421 handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_mcp3421_iic_read(mcp3421_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_read_cmd(MCP3421_ADDRESS, (uint8_t *)buf, len) == 0)        /* read data */
    {
        return 0;                                                               /* success return 0 */
    }
    else
    {
        return 1;                                                               /* return error */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an mcp3421 handle structure
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_mcp3421_iic_write(mcp3421_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_write_cmd(MCP3421_ADDRESS, (uint8_t *)buf, len) == 0)       /* write data */
    {
        return 0;                                                               /* success return 0 */
    }
    else
    {
        return 1;                                                               /* return error */
    }
}

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
uint8_t mcp3421_init(mcp3421_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                    /* check iic_init */
    {
        handle->debug_print("mcp3421: iic_init is null.\n");         /* iic_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                  /* check iic_deinit */
    {
        handle->debug_print("mcp3421: iic_deinit is null.\n");       /* iic_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                /* check iic_read_cmd */
    {
        handle->debug_print("mcp3421: iic_read_cmd is null.\n");     /* iic_read_cmd is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_write_cmd == NULL)                               /* check iic_write_cmd */
    {
        handle->debug_print("mcp3421: iic_write_cmd is null.\n");    /* iic_write_cmd is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("mcp3421: delay_ms is null.\n");         /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_init() != 0)                                     /* iic init */
    {
        handle->debug_print("mcp3421: iic init failed.\n");          /* iic init failed */
        
        return 1;                                                    /* return error */
    }
    handle->inited = 1;                                              /* flag inited */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t mcp3421_deinit(mcp3421_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                              /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");             /* read config failed */
        
        return 4;                                                          /* return error */
    }
    buf[3] &= ~(1 << 4);                                                   /* clear mode */
    res = a_mcp3421_iic_write(handle, &buf[3], 1);                         /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: write config failed.\n");            /* write config failed */
        
        return 4;                                                          /* return error */
    }
    res = handle->iic_deinit();                                            /* close iic */
    if (res != 0)                                                          /* check the result */
    {
        handle->debug_print("mcp3421: iic deinit failed.\n");              /* iic deinit failed */
        
        return 1;                                                          /* return error */
    }
    handle->inited = 0;                                                    /* flag close */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mcp3421_set_adc_bit(mcp3421_handle_t *handle, mcp3421_bit_t adc_bit)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                          /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    buf[3] &= ~(0x03 << 2);                                            /* clear settings */
    buf[3] |= adc_bit << 2;                                            /* set adc bit */
    res = a_mcp3421_iic_write(handle, &buf[3], 1);                     /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("mcp3421: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t mcp3421_get_adc_bit(mcp3421_handle_t *handle, mcp3421_bit_t *adc_bit)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                          /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    *adc_bit = (mcp3421_bit_t)((buf[3] >> 2) & 0x03);                  /* get adc bit */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t mcp3421_set_pga(mcp3421_handle_t *handle, mcp3421_pga_t pga)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                          /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    buf[3] &= ~(0x03 << 0);                                            /* clear settings */
    buf[3] |= pga << 0;                                                /* set pga */
    res = a_mcp3421_iic_write(handle, &buf[3], 1);                     /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("mcp3421: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t mcp3421_get_pga(mcp3421_handle_t *handle, mcp3421_pga_t *pga)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                          /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    *pga = (mcp3421_pga_t)((buf[3] >> 0) & 0x03);                      /* get pga */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t mcp3421_single_read(mcp3421_handle_t *handle, int32_t *raw, double *v)
{
    uint8_t res;
    uint8_t adc_bit;
    uint8_t pga;
    uint8_t buf[4];
    uint32_t timeout = 500;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                              /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");             /* read config failed */
        
        return 1;                                                          /* return error */
    }
    buf[3] &= ~(1 << 4);                                                   /* shot mode */
    buf[3] |= 1 << 7;                                                      /* set start bit */
    res = a_mcp3421_iic_write(handle, &buf[3], 1);                         /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: write config failed.\n");            /* write config failed */
        
        return 1;                                                          /* return error */
    }
    adc_bit = buf[3];                                                      /* get adc bit */
    pga = buf[3] & 0x3;                                                    /* get pga */
    while (timeout != 0)                                                   /* loop */
    {
        handle->delay_ms(10);                                              /* delay 10ms */
        timeout--;                                                         /* timeout */
        if (((adc_bit >> 2) & 0x3) == 3)                                   /* 18bit */
        {
            res = a_mcp3421_iic_read(handle, buf, 4);                      /* read config */
            if (res != 0)                                                  /* check error */
            {
                handle->debug_print("mcp3421: read config failed.\n");     /* read config failed */
                
                return 1;                                                  /* return error */
            }
            if (((buf[3] >> 7) & 0x1) == 0)                                /* check updated bit */
            {
                break;                                                     /* break */
            }
        }
        else
        {
            res = a_mcp3421_iic_read(handle, buf, 3);                      /* read config */
            if (res != 0)                                                  /* check error */
            {
                handle->debug_print("mcp3421: read config failed.\n");     /* read config failed */
                
                return 1;                                                  /* return error */
            }
            if (((buf[2] >> 7) & 0x01) == 0)                               /* check updated bit */
            {
                break;                                                     /* break */
            }
        }
    }
    if (timeout == 0)                                                      /* check timeout */
    {
        handle->debug_print("mcp3421: read timeout.\n");                   /* read timeout */
        
        return 4;                                                          /* return error */
    }
    if (((adc_bit >> 2) & 0x3) == 3)                                       /* 18bit */
    {
        if (((buf[0] >> 1) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)(buf[0] & 0x3) << 16) |
                   ((uint32_t)buf[1] << 8) |
                   ((uint32_t)buf[2] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFC << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)(buf[0] & 0x3) << 16) |
                   ((uint32_t)buf[1] << 8) |
                   ((uint32_t)buf[2] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 17) * pow(2, pga));          /* convert */
    }
    else if (((adc_bit >> 2) & 0x3) == 2)                                  /* 16bit */
    {
        if (((buf[0] >> 7) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFF << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 15) * pow(2, pga));          /* convert */
    }
    else if (((adc_bit >> 2) & 0x3) == 1)                                  /* 14bit */
    {
        if (((buf[0] >> 6) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFF << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 13) * pow(2, pga));          /* convert */
    }
    else                                                                   /* 12bit */
    {
        if (((buf[0] >> 5) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFF << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 11) * pow(2, pga));          /* convert */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mcp3421_continuous_read(mcp3421_handle_t *handle, int32_t *raw, double *v)
{
    uint8_t res;
    uint8_t adc_bit;
    uint8_t pga;
    uint8_t buf[4];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    adc_bit = handle->config;                                              /* get adc bit */
    pga = handle->config & 0x3;                                            /* get pga */
    if (((adc_bit >> 2) & 0x3) == 3)                                       /* 18bit */
    {
        res = a_mcp3421_iic_read(handle, buf, 4);                          /* read config */
        if (res != 0)                                                      /* check error */
        {
            handle->debug_print("mcp3421: read config failed.\n");         /* read config failed */
            
            return 1;                                                      /* return error */
        }
    }
    else
    {
        res = a_mcp3421_iic_read(handle, buf, 3);                          /* read config */
        if (res != 0)                                                      /* check error */
        {
            handle->debug_print("mcp3421: read config failed.\n");         /* read config failed */
            
            return 1;                                                      /* return error */
        }
    }

    if (((adc_bit >> 2) & 0x3) == 3)                                       /* 18bit */
    {
        if (((buf[0] >> 1) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)(buf[0] & 0x3) << 16) |
                   ((uint32_t)buf[1] << 8) |
                   ((uint32_t)buf[2] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFC << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)(buf[0] & 0x3) << 16) |
                   ((uint32_t)buf[1] << 8) |
                   ((uint32_t)buf[2] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 17) * pow(2, pga));          /* convert */
    }
    else if (((adc_bit >> 2) & 0x3) == 2)                                  /* 16bit */
    {
        if (((buf[0] >> 7) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFF << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 15) * pow(2, pga));          /* convert */
    }
    else if (((adc_bit >> 2) & 0x3) == 1)                                  /* 14bit */
    {
        if (((buf[0] >> 6) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFF << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 13) * pow(2, pga));          /* convert */
    }
    else                                                                   /* 12bit */
    {
        if (((buf[0] >> 5) & 0x01) != 0)                                   /* check msb */
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0) |
                   ((uint32_t)0xFF << 24) |
                   ((uint32_t)0xFF << 16));                                /* set raw */
        }
        else
        {
            *raw = (int32_t)(((uint32_t)buf[0] << 8) |
                   ((uint32_t)buf[1] << 0));                               /* set raw */
        }
        *v = (double)(*raw) * 2.048 / (pow(2, 11) * pow(2, pga));          /* convert */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mcp3421_start_continuous_read(mcp3421_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                              /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");             /* read config failed */
        
        return 1;                                                          /* return error */
    }
    buf[3] &= ~(1 << 4);                                                   /* clear mode */
    buf[3] |= 1 << 4;                                                      /* continuous mode */
    res = a_mcp3421_iic_write(handle, &buf[3], 1);                         /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: write config failed.\n");            /* write config failed */
        
        return 1;                                                          /* return error */
    }
    handle->config = buf[3];                                               /* save config */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mcp3421_stop_continuous_read(mcp3421_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mcp3421_iic_read(handle, buf, 4);                              /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: read config failed.\n");             /* read config failed */
        
        return 1;                                                          /* return error */
    }
    buf[3] &= ~(1 << 4);                                                   /* clear mode */
    res = a_mcp3421_iic_write(handle, &buf[3], 1);                         /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("mcp3421: write config failed.\n");            /* write config failed */
        
        return 1;                                                          /* return error */
    }
    handle->config = buf[3];                                               /* save config */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mcp3421_set_reg(mcp3421_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_mcp3421_iic_write(handle, buf, len);       /* write reg */
}

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
uint8_t mcp3421_get_reg(mcp3421_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    return a_mcp3421_iic_read(handle, buf, len);       /* read reg */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an mcp3421 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mcp3421_info(mcp3421_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(mcp3421_info_t));                        /* initialize mcp3421 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
