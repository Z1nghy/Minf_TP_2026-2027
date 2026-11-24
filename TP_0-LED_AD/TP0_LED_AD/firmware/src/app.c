/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"
#include "bsp.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

// Definitions du tableau de LED



// definitions pour le switch case du chenillard
#define CHENILLARD0 0
#define CHENILLARD1 1
#define CHENILLARD2 2
#define CHENILLARD3 3
#define CHENILLARD4 4
#define CHENILLARD5 5
#define CHENILLARD6 6
#define CHENILLARD7 7

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    // initialisation du LCD
    lcd_init();
    // initialisation de l'ADC
    BSP_InitADC10();

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    static bool Chenillard_Bool = false;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            // allume le backlight
            lcd_bl_on();
            // affiche sur la premiere ligne "TP0 LED AD <2026>"
            printf_lcd("TP0 LED AD <2026>");
            // va à la deuxiemme ligne premier case
            lcd_gotoxy(1,2);
            // affiche sur la deuxiemme ligne "Diego Alec Savary"
            printf_lcd("Diego Alec Savary");
            
            // Variable servant a savoir si c'est la premiere fois 
            appData.ST_New = 1;
            appData.ST_Old = 0;
            
            // allumer les LED's
            LEDs_ON_OFF();       
            
            // demarer le timer 1
            DRV_TMR0_Start();
            
            // update le state à WAIT
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }
        case APP_STATE_WAIT:
        {
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            if (appData.ST_New != appData.ST_Old)
            {
                appData.ST_Old = appData.ST_New;
                LEDs_ON_OFF();
            }
            
             appData.adcRes = BSP_ReadAllADC();
             lcd_gotoxy(1,3);
             printf_lcd("CH0 %4d / CH1 %4d",appData.adcRes.Chan0,appData.adcRes.Chan1);
             
             
             
             if (Chenillard_Bool == true)
             {
                 Chenillard_Bool = false;
                 Chenillard();
             }
             else
             {
                 Chenillard_Bool = true;
             }
             
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
void APP_TMR0_Callback(void)
{
    APP_UpdateState(APP_STATE_SERVICE_TASKS);
}

void APP_UpdateState(APP_STATES newState)
{
    appData.state = newState;
}
 
void LEDs_ON_OFF(void)
{
    // tableau de LED 
    static const uint8_t tbLED[8] = {BSP_LED_0,BSP_LED_1,BSP_LED_2,BSP_LED_3,
                            BSP_LED_4,BSP_LED_5,BSP_LED_6,BSP_LED_7};
    // variable d'iteration
    static int8_t i;
    // allume toute les LED's si c'est la premiee utilisation
    if (appData.ST_New != appData.ST_Old)
    {
        for (i = 0; i < 7; i++) 
        {    
            // allume la LED de la case concernée
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, tbLED[i]); 
        }
        // allume la LED 7
        PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_B, tbLED[7]);
    }
    else // eteint toute les LED's si c'est la premiee utilisation 
    {
        for (i = 0; i < 7; i++) 
        {    
            // eteint la LED de la case concernée
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, tbLED[i]); 
        }
        // eteint la LED 7
        PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_B, tbLED[7]);
    }
     
 }

void Chenillard(void)
{
    // initialisation de mes variable servant a controller le chenillard
    static uint8_t ChenillardAscendant = 1,ChenillardDescendant = 0, State_Chenillard = 0;
    
    // switch case du chenillard avec State_Chenillard comme parametre d'entrée
    switch(State_Chenillard)
    {
        case CHENILLARD0:
            // allumer la LED 0
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_0);
            // eteindre la LED 1
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_1);
            break;
            
        case CHENILLARD1:
            // allumer la LED 1
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_1);
            // eteindre la LED 0 pour le mode ascendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_0);
            // eteindre la LED 2 pour le mode descendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_2);
            break;
            
        case CHENILLARD2:
            // allumer la LED 2
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_2);
            // eteindre la LED 1 pour le mode ascendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_1);
            // eteindre la LED 3 pour le mode descendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_3);
            break;
            
        case CHENILLARD3:
            // allumer la LED 3
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_3);
            // eteindre la LED 2 pour le mode ascendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_2);
            // eteindre la LED 4 pour le mode descendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_4);
            break;
            
        case CHENILLARD4:
            // allumer la LED 4
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_4);
            // eteindre la LED 3 pour le mode ascendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_3);
            // eteindre la LED 5 pour le mode descendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_5);
            break;
            
        case CHENILLARD5:
            // allumer la LED 5
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_5);
            // eteindre la LED 4 pour le mode ascendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_4);
            // eteindre la LED 6 pour le mode descendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_6);
            break;
            
        case CHENILLARD6:
            // allumer la LED 6
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_6);
            // eteindre la LED 5 pour le mode ascendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_5);
            // eteindre la LED 7 pour le mode descendant
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_B, BSP_LED_7);
            break;
            
        case CHENILLARD7:
            // allumer la LED 7
            PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_B, BSP_LED_7);
            // eteindre la LED 6
            PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_A, BSP_LED_6);
            break;
    }

    // regarde si c'est le mode ascendant qui est actif
    if(ChenillardAscendant == 1)
    {
        // incrementer le state du chenillard
        State_Chenillard ++;
    }
    // regarde si c'est le mode descendant qui est actif
    else if (ChenillardDescendant == 1)
    {
        // decrementer le state du chenillard
        State_Chenillard --;
    }
    
    if ((ChenillardAscendant == 1) && (State_Chenillard >= 7))
    {
        ChenillardAscendant = 0;
        ChenillardDescendant = 1;
    }
    else if ((ChenillardDescendant == 1) && (State_Chenillard <= 0))
    {
        ChenillardAscendant = 1;
        ChenillardDescendant = 0;
    }
    
}


/*******************************************************************************
 End of File
 */
