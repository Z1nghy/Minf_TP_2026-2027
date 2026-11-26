/*--------------------------------------------------------*/
// GestPWM.h
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM pour TP1 MINF
//	Auteur 		: 	C. HUBER
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
//  Modification :
//   17.11.2026 SCA : MàJ et test avec MPLAB X 6.15,
//    xc32 2.50 et Harmony 2.06
//
/*--------------------------------------------------------*/

#ifndef GestPWM_H
#define GestPWM_H

#include <stdint.h>

typedef struct {
    uint8_t absSpeed;    // vitesse 0 à 99
    uint8_t absAngle;    // Angle  0 à 180
    int8_t SpeedSetting; // consigne vitesse -99 à +99
    int8_t AngleSetting; // consigne angle  -90 à +90
} S_pwmSettings;

extern S_pwmSettings PWMData;      // pour les settings


/*--------------------------------------------------------*/
// Définition des fonctions prototypes
/*--------------------------------------------------------*/

void GPWM_Initialize(S_pwmSettings *pData);

// Ces 4 fonctions ont pour paramètre un pointeur sur la structure S_pwmSettings.
void GPWM_GetSettings(S_pwmSettings *pData);	// Obtention vitesse et angle
void GPWM_DispSettings(S_pwmSettings *pData);	// Affichage
void GPWM_ExecPWM(S_pwmSettings *pData);		// Execution PWM et gestion moteur.
void GPWM_ExecPWMSoft(S_pwmSettings *pData);	// Execution PWM software.

#endif
