/*--------------------------------------------------------*/
// GestPWM.c
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM pour TP1 MINF
//	Auteur 		: 	C. HUBER
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
//  Modification :
//   17.11.2026 SCA : M‡J et test avec MPLAB X 6.15,
//    xc32 2.50 et Harmony 2.06
//
/*--------------------------------------------------------*/

#include "GestPWM.h"

S_pwmSettings PWMData;      // pour les settings

void GPWM_Initialize(S_pwmSettings *pData)
{
   // Init les data

   // Init Ètat du pont en H

   // lance les timers et OC

}

// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)
{
    // Lecture du convertisseur AD et moyennes glissantes

    // Conversions

}


// Affichage des informations en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{

}

// Execution PWM et gestion moteur ‡ partir des info. dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{

}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{

}
