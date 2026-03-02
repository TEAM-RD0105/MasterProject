/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPUART_FLEXIO
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 6.0.0
*   Build Version        : S32K3_RTD_6_0_0_D2506_ASR_REL_4_7_REV_0000_20250610
*
*   Copyright 2020 - 2025 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef FLEXIO_LIN_IP_IRQ_H
#define FLEXIO_LIN_IP_IRQ_H

/**
*   @file Flexio_Lin_Ip_Irq.h
*   @implements Flexio_Lin_Ip_Irq.h_Artifact
*
*   @addtogroup FLEXIO_IP
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Mcal.h"
#include "Flexio_Lin_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_LIN_IP_IRQ_VENDOR_ID                      43
#define FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION       4
#define FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION       7
#define FLEXIO_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION    0
#define FLEXIO_LIN_IP_IRQ_SW_MAJOR_VERSION               6
#define FLEXIO_LIN_IP_IRQ_SW_MINOR_VERSION               0
#define FLEXIO_LIN_IP_IRQ_SW_PATCH_VERSION               0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcal.h header file are of the same Autosar version */
#if ((FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION != FLEXIO_LIN_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
        (FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION != FLEXIO_LIN_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
        (FLEXIO_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION != FLEXIO_LIN_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Flexio_Lin_Ip_Irq.h and Flexio_Lin_Ip_Cfg.h are different"
#endif
/* Check if current file and Flexio_Lin_Ip_Cfg header file are of the same Software version */
#if ((FLEXIO_LIN_IP_IRQ_SW_MAJOR_VERSION != FLEXIO_LIN_IP_CFG_SW_MAJOR_VERSION) || \
    (FLEXIO_LIN_IP_IRQ_SW_MINOR_VERSION != FLEXIO_LIN_IP_CFG_SW_MINOR_VERSION) || \
    (FLEXIO_LIN_IP_IRQ_SW_PATCH_VERSION != FLEXIO_LIN_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Lin_Ip_Irq.h and Flexio_Lin_Ip_Cfg.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and Mcal.h header file are of the same Autosar version */
    #if ((FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Flexio_Lin_Ip_Irq.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_START_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"
void Flexio_Lin_Ip_IrqHandler(uint8 ShifterIndex, uint8 ShifterMaskFlag, uint8 ShifterErrorMaskFlag);
#if (FLEXIO_LIN_IP_HAS_DMA_ENABLED == STD_ON)

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 0U)
void Flexio_0_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 1U)
void Flexio_1_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 2U)
void Flexio_2_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 3U)
void Flexio_3_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 4U)
void Flexio_4_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 5U)
void Flexio_5_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 6U)
void Flexio_6_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 7U)
void Flexio_7_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 8U)
void Flexio_8_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 9U)
void Flexio_9_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 10U)
void Flexio_10_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 11U)
void Flexio_11_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 12U)
void Flexio_12_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 13U)
void Flexio_13_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 14U)
void Flexio_14_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 15U)
void Flexio_15_Lin_Ip_DmaRxCompleteCallback(void);
#endif

#endif /* (FLEXIO_LIN_IP_HAS_DMA_ENABLED == STD_ON) */

#define LIN_43_LPUART_FLEXIO_STOP_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FLEXIO_LIN_IP_IRQ_H */
