/***********************************************************************************************************************
 * Copyright [2015-2017] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : hal_entry.c
* Description  : This is a very simple example application that blinks all LEDs on a board.
***********************************************************************************************************************/

#include "hal_data.h"
const bsp_delay_units_t bsp_delay_units = BSP_DELAY_UNITS_MILLISECONDS;
uint32_t flag1=0;
uint32_t flag2=0;

/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the software delay function provided by the BSP.
 * Only references two other modules including the BSP, IOPORT.
 *
 **********************************************************************************************************************/
void hal_entry(void) {


    // Interrupts
    g_external_irq10.p_api->open(g_external_irq10.p_ctrl,g_external_irq10.p_cfg);
    g_external_irq11.p_api->open(g_external_irq11.p_ctrl,g_external_irq11.p_cfg);

    // Esatdo inicial en 0
    g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1
    g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_HIGH);  //l2
    g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_HIGH);  //l3

    while(1)
    {
        //Secuancia_normal (encendido el verde)
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_HIGH);  //l2 (rojo)
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_HIGH);  //l3 (amarillo)
        flag1=0;
        flag2=0;
    }
}

// PEATON
void button_callback_SW4(external_irq_callback_args_t *p_args)
{
   flag1=1;  // El peaton presiono el boton
      if(flag2==0)
      {
           // PARPADEA EL VERDE
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
           R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)


           // ENCIENDE AMARILLO
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_LOW);  //l3 (amarillo)
           R_BSP_SoftwareDelay(1500, bsp_delay_units);
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_HIGH);  //l3 (amarillo)/

           // ENCIENDE ROJO --> El peaton tiene 4 segundos para pasar.
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_LOW);  //l2 (rojo)
           R_BSP_SoftwareDelay(4000, bsp_delay_units);

           // PLUS (Avisar que ya encnederá nuevamente a verde, por lo que enciende el amariillo)
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_LOW);  //l3 (amarillo)
           R_BSP_SoftwareDelay(1000, bsp_delay_units);  // Avisa que encenerá el verde

           // APAGA Amarillo y Rojo, para continuar la secuencia normal
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_HIGH);  //l2 (rojo)
           g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_HIGH);  //l3 (amarillo)

      }
}

// AUTOMOVIL
void button_callback_SW5(external_irq_callback_args_t *p_args)
{
    flag2=1;  // Paso un automovil

          if(flag1==0)
          {
              // PARPADEA EL VERDE
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);  //l1 (verde)
              R_BSP_SoftwareDelay(200, bsp_delay_units);/* Delay */
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);  //l1 (verde)


              // ENCIENDE AMARILLO
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_LOW);  //l3 (amarillo)
              R_BSP_SoftwareDelay(1500, bsp_delay_units);
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_HIGH);  //l3 (amarillo)/

              // ENCIENDE ROJO --> El auto tiene 2 segundos para pasar.
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_LOW);  //l2 (rojo)
              R_BSP_SoftwareDelay(2000, bsp_delay_units);

              // PLUS (Avisar que ya encnederá nuevamente a verde, por lo que enciende el amariillo)
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_LOW);  //l3 (amarillo)
              R_BSP_SoftwareDelay(1000, bsp_delay_units);  // Avisa que encenerá el verde

              // APAGA Amarillo y Rojo, para continuar la secuencia normal
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_HIGH);  //l2 (rojo)
              g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_HIGH);  //l3 (amarillo)


          }

}

