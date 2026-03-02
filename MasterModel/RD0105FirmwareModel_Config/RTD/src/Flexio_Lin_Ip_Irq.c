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

/**
*   @file
*   @addtogroup FLEXIO_IP
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Flexio_Lin_Ip.h"
#include "Flexio_Lin_Ip_Irq.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_LIN_IP_IRQ_VENDOR_ID_C                      43
#define FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define FLEXIO_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define FLEXIO_LIN_IP_IRQ_SW_MAJOR_VERSION_C               6
#define FLEXIO_LIN_IP_IRQ_SW_MINOR_VERSION_C               0
#define FLEXIO_LIN_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Flexio_Lin_Ip.h */
#if (FLEXIO_LIN_IP_IRQ_VENDOR_ID_C != FLEXIO_LIN_IP_VENDOR_ID)
    #error "Flexio_Lin_Ip_Irq.c and Flexio_Lin_Ip.h have different vendor ids"
#endif
#if ((FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_LIN_IP_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_LIN_IP_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FLEXIO_LIN_IP_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Lin_Ip_Irq.c and Flexio_Lin_Ip.h are different"
#endif
#if ((FLEXIO_LIN_IP_IRQ_SW_MAJOR_VERSION_C != FLEXIO_LIN_IP_SW_MAJOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_SW_MINOR_VERSION_C != FLEXIO_LIN_IP_SW_MINOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_SW_PATCH_VERSION_C != FLEXIO_LIN_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Lin_Ip_Irq.c and Flexio_Lin_Ip.h are different"
#endif
/* Checks against Flexio_Lin_Ip_Irq.h */
#if (FLEXIO_LIN_IP_IRQ_VENDOR_ID_C != FLEXIO_LIN_IP_IRQ_VENDOR_ID)
    #error "Flexio_Lin_Ip_Irq.c and Flexio_Lin_Ip_Irq.h have different vendor ids"
#endif
#if ((FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FLEXIO_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Lin_Ip_Irq.c and Flexio_Lin_Ip_Irq.h are different"
#endif
#if ((FLEXIO_LIN_IP_IRQ_SW_MAJOR_VERSION_C != FLEXIO_LIN_IP_IRQ_SW_MAJOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_SW_MINOR_VERSION_C != FLEXIO_LIN_IP_IRQ_SW_MINOR_VERSION) || \
     (FLEXIO_LIN_IP_IRQ_SW_PATCH_VERSION_C != FLEXIO_LIN_IP_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Lin_Ip_Irq.c and Flexio_Lin_Ip_Irq.h are different"
#endif
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef FLEXIO_LIN_IP_FLEXIO_USED
#if (FLEXIO_LIN_IP_FLEXIO_USED == STD_ON)
#define LIN_43_LPUART_FLEXIO_START_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"


#if (FLEXIO_LIN_IP_HAS_DMA_ENABLED == STD_ON)
#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 0U)
/* Implementation of Flexio0 Rx callback function for Dma interrupt. */
void Flexio_0_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(0);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 1U)
/* Implementation of Flexio1 Rx callback function for Dma interrupt. */
void Flexio_1_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(1);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 2U)
/* Implementation of Flexio2 Rx callback function for Dma interrupt. */
void Flexio_2_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(2);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 3U)
/* Implementation of Flexio3 Rx callback function for Dma interrupt. */
void Flexio_3_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(3);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 4U)
/* Implementation of Flexio4 Rx callback function for Dma interrupt. */
void Flexio_4_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(4);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 5U)
/* Implementation of Flexio5 Rx callback function for Dma interrupt. */
void Flexio_5_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(5);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 6U)
/* Implementation of Flexio6 Rx callback function for Dma interrupt. */
void Flexio_6_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(6);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 7U)
/* Implementation of Flexio7 Rx callback function for Dma interrupt. */
void Flexio_7_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(7);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 8U)
/* Implementation of Flexio8 Rx callback function for Dma interrupt. */
void Flexio_8_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(8);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 9U)
/* Implementation of Flexio9 Rx callback function for Dma interrupt. */
void Flexio_9_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(9);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 10U)
/* Implementation of Flexio10 Rx callback function for Dma interrupt. */
void Flexio_10_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(10);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 11U)
/* Implementation of Flexio11 Rx callback function for Dma interrupt. */
void Flexio_11_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(11);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 12U)
/* Implementation of Flexio12 Rx callback function for Dma interrupt. */
void Flexio_12_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(12);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 13U)
/* Implementation of Flexio13 Rx callback function for Dma interrupt. */
void Flexio_13_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(13);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 14U)
/* Implementation of Flexio14 Rx callback function for Dma interrupt. */
void Flexio_14_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(14);
}
#endif

#if (FLEXIO_LIN_IP_NUMBER_OF_FLEXIO_SHIFTERS > 15U)
/* Implementation of Flexio15 Rx callback function for Dma interrupt. */
void Flexio_15_Lin_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Lin_Ip_CompleteReceiveUsingDma(15);
}
#endif
#endif /*(FLEXIO_LIN_IP_HAS_DMA_ENABLED == STD_ON)*/

#define LIN_43_LPUART_FLEXIO_STOP_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

#endif /* (FLEXIO_LIN_IP_FLEXIO_USED == STD_ON) */
#endif /* #ifdef FLEXIO_LIN_IP_FLEXIO_USED */

#ifdef __cplusplus
}
#endif

/** @} */
