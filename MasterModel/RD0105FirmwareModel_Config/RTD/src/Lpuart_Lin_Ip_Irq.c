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
*   @file   Lpuart_Lin_Ip_Irq.c
*   @implements Lpuart_Lin_Ip_Irq.c_Artifact
*
*   @addtogroup LPUART_LIN_IP
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
#include "Lpuart_Lin_Ip.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_LIN_IP_IRQ_VENDOR_ID_C                      43
#define LPUART_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define LPUART_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define LPUART_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define LPUART_LIN_IP_IRQ_SW_MAJOR_VERSION_C               6
#define LPUART_LIN_IP_IRQ_SW_MINOR_VERSION_C               0
#define LPUART_LIN_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Lpuart_Lin_Ip header file are of the same Autosar version */
#if (LPUART_LIN_IP_IRQ_VENDOR_ID_C != LPUART_LIN_IP_VENDOR_ID)
    #error "Lpuart_Lin_Ip_Irq.c and Lpuart_Lin_Ip.h have different vendor ids"
#endif
#if ((LPUART_LIN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != LPUART_LIN_IP_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_LIN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != LPUART_LIN_IP_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_LIN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != LPUART_LIN_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Lpuart_Lin_Ip_Irq.c and Lpuart_Lin_Ip.h are different"
#endif
/* Check if current file and Lpuart_Lin_Ip header file are of the same Software version */
#if ((LPUART_LIN_IP_IRQ_SW_MAJOR_VERSION_C != LPUART_LIN_IP_SW_MAJOR_VERSION) || \
     (LPUART_LIN_IP_IRQ_SW_MINOR_VERSION_C != LPUART_LIN_IP_SW_MINOR_VERSION) || \
     (LPUART_LIN_IP_IRQ_SW_PATCH_VERSION_C != LPUART_LIN_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lpuart_Lin_Ip_Irq.c and Lpuart_Lin_Ip.h are different"
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
#define LIN_43_LPUART_FLEXIO_START_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

#if (LPUART_INSTANCE_COUNT > 0U)
#ifdef LPUART_IP_0
ISR(LPUART0_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART0_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_0 */
#endif /* if (LPUART_INSTANCE_COUNT > 0U) */

#if (LPUART_INSTANCE_COUNT > 1U)
#ifdef LPUART_IP_1
ISR(LPUART1_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART1_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_1 */
#endif /* if (LPUART_INSTANCE_COUNT > 1U) */

#if (LPUART_INSTANCE_COUNT > 2U)
#ifdef LPUART_IP_2
ISR(LPUART2_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART2_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_2 */
#endif /* if (LPUART_INSTANCE_COUNT > 2U) */

#if (LPUART_INSTANCE_COUNT > 3U)
#ifdef LPUART_IP_3
ISR(LPUART3_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART3_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_3 */
#endif /* if (LPUART_INSTANCE_COUNT > 3U) */

#if (LPUART_INSTANCE_COUNT > 4U)
#ifdef LPUART_IP_4
ISR(LPUART4_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART4_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_4 */

#endif /* if (LPUART_INSTANCE_COUNT > 4U) */

#if (LPUART_INSTANCE_COUNT > 5U)
#ifdef LPUART_IP_5
ISR(LPUART5_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART5_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_5 */
#endif /* if (LPUART_INSTANCE_COUNT > 5U) */

#if (LPUART_INSTANCE_COUNT > 6U)
#ifdef LPUART_IP_6
ISR(LPUART6_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART6_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_6 */
#endif /* if (LPUART_INSTANCE_COUNT > 6U) */

#if (LPUART_INSTANCE_COUNT > 7U)
#ifdef LPUART_IP_7
ISR(LPUART7_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART7_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_7 */
#endif /* if (LPUART_INSTANCE_COUNT > 7U) */

#if (LPUART_INSTANCE_COUNT > 8U)
#ifdef LPUART_IP_8
ISR(LPUART8_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART8_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_8 */
#endif /* if (LPUART_INSTANCE_COUNT > 8U) */

#if (LPUART_INSTANCE_COUNT > 9U)
#ifdef LPUART_IP_9
ISR(LPUART9_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART9_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_9 */
#endif /* if (LPUART_INSTANCE_COUNT > 9U) */


#if (LPUART_INSTANCE_COUNT > 10U)
#ifdef LPUART_IP_10
ISR(LPUART10_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART10_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_10 */
#endif /* if (LPUART_INSTANCE_COUNT > 10U) */


#if (LPUART_INSTANCE_COUNT > 11U)
#ifdef LPUART_IP_11
ISR(LPUART11_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART11_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_11 */
#endif /* if (LPUART_INSTANCE_COUNT > 11U) */


#if (LPUART_INSTANCE_COUNT > 12U)
#ifdef LPUART_IP_12
ISR(LPUART12_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART12_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_12 */
#endif /* if (LPUART_INSTANCE_COUNT > 12U) */


#if (LPUART_INSTANCE_COUNT > 13U)
#ifdef LPUART_IP_13
ISR(LPUART13_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART13_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_13 */
#endif /* if (LPUART_INSTANCE_COUNT > 13U) */


#if (LPUART_INSTANCE_COUNT > 14U)
#ifdef LPUART_IP_14
ISR(LPUART14_LIN_IP_RxTx_IRQHandler);


#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART14_LIN_IP_ERR_IRQHandler);

#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_14 */
#endif /* if (LPUART_INSTANCE_COUNT > 14U) */


#if (LPUART_INSTANCE_COUNT > 15U)
#ifdef LPUART_IP_15
ISR(LPUART15_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART15_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_15 */
#endif /* if (LPUART_INSTANCE_COUNT > 15U) */


#if (LPUART_INSTANCE_COUNT > 16U)
#ifdef LPUART_IP_16
ISR(LPUART16_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART16_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_16 */
#endif /* if (LPUART_INSTANCE_COUNT > 16U) */


#if (LPUART_INSTANCE_COUNT > 17U)
#ifdef LPUART_IP_17
ISR(LPUART17_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART17_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_17 */
#endif /* if (LPUART_INSTANCE_COUNT > 17U) */


#if (LPUART_INSTANCE_COUNT > 18U)
#ifdef LPUART_IP_18
ISR(LPUART18_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART18_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_18 */
#endif /* if (LPUART_INSTANCE_COUNT > 18U) */


#if (LPUART_INSTANCE_COUNT > 19U)
#ifdef LPUART_IP_19
ISR(LPUART19_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART19_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_19 */
#endif /* if (LPUART_INSTANCE_COUNT > 19U) */


#if (LPUART_INSTANCE_COUNT > 20U)
#ifdef LPUART_IP_20
ISR(LPUART20_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART20_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_20 */
#endif /* if (LPUART_INSTANCE_COUNT > 20U) */

#if (LPUART_INSTANCE_COUNT > 21U)
#ifdef LPUART_IP_21
ISR(LPUART21_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART21_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_21 */
#endif /* if (LPUART_INSTANCE_COUNT > 21U) */

#if (LPUART_INSTANCE_COUNT > 22U)
#ifdef LPE_LPUART_IP_0
ISR(LPE_LPUART0_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART22_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPE_LPUART_IP_0 */
#endif /* if (LPUART_INSTANCE_COUNT > 22U) */


#if (LPUART_INSTANCE_COUNT > 23U)
#ifdef LPE_LPUART_IP_1
ISR(LPE_LPUART1_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART23_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPE_LPUART_IP_1 */
#endif /* if (LPUART_INSTANCE_COUNT > 23U) */


#if (LPUART_INSTANCE_COUNT > 24U)
#ifdef LPE_LPUART_IP_2
ISR(LPE_LPUART2_LIN_IP_RxTx_IRQHandler);

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART24_LIN_IP_ERR_IRQHandler);
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPE_LPUART_IP_2 */
#endif /* if (LPUART_INSTANCE_COUNT > 24U) */

#if (LPUART_LIN_IP_HAS_DMA_ENABLED == STD_ON)
#if (LPUART_INSTANCE_COUNT > 0U)
#ifdef LPUART_IP_0
/* Implementation of Lpuart0 Rx callback function for Dma interrupt. */
void Lpuart_0_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
#ifdef LPUART_IP_1
/* Implementation of Lpuart1 Rx callback function for Dma interrupt. */
void Lpuart_1_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
#ifdef LPUART_IP_2
/* Implementation of Lpuart2 Rx callback function for Dma interrupt. */
void Lpuart_2_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 3U)
#ifdef LPUART_IP_3
/* Implementation of Lpuart3 Rx callback function for Dma interrupt. */
void Lpuart_3_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 4U)
#ifdef LPUART_IP_4
/* Implementation of Lpuart4 Rx callback function for Dma interrupt. */
void Lpuart_4_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 5U)
#ifdef LPUART_IP_5
/* Implementation of Lpuart5 Rx callback function for Dma interrupt. */
void Lpuart_5_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 6U)
#ifdef LPUART_IP_6
/* Implementation of Lpuart6 Rx callback function for Dma interrupt. */
void Lpuart_6_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 7U)
#ifdef LPUART_IP_7
/* Implementation of Lpuart7 Rx callback function for Dma interrupt. */
void Lpuart_7_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 8U)
#ifdef LPUART_IP_8
/* Implementation of Lpuart8 Rx callback function for Dma interrupt. */
void Lpuart_8_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 9U)
#ifdef LPUART_IP_9
/* Implementation of Lpuart9 Rx callback function for Dma interrupt. */
void Lpuart_9_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 10U)
#ifdef LPUART_IP_10
/* Implementation of Lpuart10 Rx callback function for Dma interrupt. */
void Lpuart_10_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 11U)
#ifdef LPUART_IP_11
/* Implementation of Lpuart11 Rx callback function for Dma interrupt. */
void Lpuart_11_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 12U)
#ifdef LPUART_IP_12
/* Implementation of Lpuart12 Rx callback function for Dma interrupt. */
void Lpuart_12_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 13U)
#ifdef LPUART_IP_13
/* Implementation of Lpuart13 Rx callback function for Dma interrupt. */
void Lpuart_13_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 14U)
#ifdef LPUART_IP_14
/* Implementation of Lpuart14 Rx callback function for Dma interrupt. */
void Lpuart_14_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 15U)
#ifdef LPUART_IP_15
/* Implementation of Lpuart15 Rx callback function for Dma interrupt. */
void Lpuart_15_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 16U)
#ifdef LPUART_IP_16
/* Implementation of Lpuart16 Rx callback function for Dma interrupt. */
void Lpuart_16_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 17U)
#ifdef LPUART_IP_17
/* Implementation of Lpuart17 Rx callback function for Dma interrupt. */
void Lpuart_17_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 18U)
#ifdef LPUART_IP_18
/* Implementation of Lpuart18 Rx callback function for Dma interrupt. */
void Lpuart_18_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif
#if (LPUART_INSTANCE_COUNT > 19U)
#ifdef LPUART_IP_19
/* Implementation of Lpuart18 Rx callback function for Dma interrupt. */
void Lpuart_19_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif
#if (LPUART_INSTANCE_COUNT > 20U)
#ifdef LPUART_IP_20
/* Implementation of Lpuart20 Rx callback function for Dma interrupt. */
void Lpuart_20_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 21U)
#ifdef LPUART_IP_21
/* Implementation of Lpuart21 Rx callback function for Dma interrupt. */
void Lpuart_21_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 22U)
#ifdef LPE_LPUART_IP_0
/* Implementation of Lpe_Lpuart0 Rx callback function for Dma interrupt. */
void Lpe_Lpuart0_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 23U)
#ifdef LPE_LPUART_IP_1
/* Implementation of Lpe_Lpuart1 Rx callback function for Dma interrupt. */
void Lpe_Lpuart1_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 24U)
#ifdef LPE_LPUART_IP_2
/* Implementation of Lpe_Lpuart2 Rx callback function for Dma interrupt. */
void Lpe_Lpuart2_Lin_Ip_DmaRxCompleteCallback(void);
#endif
#endif
#endif

#define LIN_43_LPUART_FLEXIO_STOP_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_START_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

#if (LPUART_INSTANCE_COUNT > 0U)
#ifdef LPUART_IP_0
/* Implementation of LPUART0 TX and RX interrupt handler for LIN driver */
ISR(LPUART0_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(0U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART0 error interrupt handler for LIN driver */
ISR(LPUART0_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(0U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_0 */
#endif /* if (LPUART_INSTANCE_COUNT > 0U) */

#if (LPUART_INSTANCE_COUNT > 1U)
#ifdef LPUART_IP_1
/* Implementation of LPUART1 TX and RX interrupt handler for LIN driver */
ISR(LPUART1_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(1U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART1 error interrupt handler for LIN driver */
ISR(LPUART1_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(1U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_1 */
#endif /* if (LPUART_INSTANCE_COUNT > 1U) */

#if (LPUART_INSTANCE_COUNT > 2U)
#ifdef LPUART_IP_2
/* Implementation of LPUART2 TX and RX interrupt handler for LIN driver */
ISR(LPUART2_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(2U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART2 error interrupt handler for LIN driver */
ISR(LPUART2_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(2U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_2 */
#endif /* if (LPUART_INSTANCE_COUNT > 2U) */

#if (LPUART_INSTANCE_COUNT > 3U)
#ifdef LPUART_IP_3
/* Implementation of LPUART3 TX and RX interrupt handler for LIN driver */
ISR(LPUART3_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(3U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART3 error interrupt handler for LIN driver */
ISR(LPUART3_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(3U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_3 */
#endif /* if (LPUART_INSTANCE_COUNT > 3U) */

#if (LPUART_INSTANCE_COUNT > 4U)
#ifdef LPUART_IP_4
/* Implementation of LPUART4 TX and RX interrupt handler for LIN driver */
ISR(LPUART4_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(4U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART4 error interrupt handler for LIN driver */
ISR(LPUART4_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(4U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_4 */


#endif /* if (LPUART_INSTANCE_COUNT > 4U) */

#if (LPUART_INSTANCE_COUNT > 5U)
#ifdef LPUART_IP_5
/* Implementation of LPUART5 TX and RX interrupt handler for LIN driver */
ISR(LPUART5_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(5U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART5 error interrupt handler for LIN driver */
ISR(LPUART5_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(5U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_5 */
#endif /* if (LPUART_INSTANCE_COUNT > 5U) */

#if (LPUART_INSTANCE_COUNT > 6U)
#ifdef LPUART_IP_6
/* Implementation of LPUART6 TX and RX interrupt handler for LIN driver */
ISR(LPUART6_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(6U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART6 error interrupt handler for LIN driver */
ISR(LPUART6_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(6U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_6 */
#endif /* if (LPUART_INSTANCE_COUNT > 6U) */

#if (LPUART_INSTANCE_COUNT > 7U)
#ifdef LPUART_IP_7
/* Implementation of LPUART7 TX and RX interrupt handler for LIN driver */
ISR(LPUART7_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(7U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART7 error interrupt handler for LIN driver */
ISR(LPUART7_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(7U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_7 */
#endif /* if (LPUART_INSTANCE_COUNT > 7U) */

#if (LPUART_INSTANCE_COUNT > 8U)
#ifdef LPUART_IP_8
/* Implementation of LPUART8 TX and RX interrupt handler for LIN driver */
ISR(LPUART8_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(8U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART8 error interrupt handler for LIN driver */
ISR(LPUART8_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(8U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_8 */
#endif /* if (LPUART_INSTANCE_COUNT > 8U) */

#if (LPUART_INSTANCE_COUNT > 9U)
#ifdef LPUART_IP_9
/* Implementation of LPUART9 TX and RX interrupt handler for LIN driver */
ISR(LPUART9_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(9U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART9 error interrupt handler for LIN driver */
ISR(LPUART9_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(9U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_9 */
#endif /* if (LPUART_INSTANCE_COUNT > 9U) */


#if (LPUART_INSTANCE_COUNT > 10U)
#ifdef LPUART_IP_10
/* Implementation of LPUART10 TX and RX interrupt handler for LIN driver */
ISR(LPUART10_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(10U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART10 error interrupt handler for LIN driver */
ISR(LPUART10_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(10U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_10 */
#endif /* if (LPUART_INSTANCE_COUNT > 10U) */


#if (LPUART_INSTANCE_COUNT > 11U)
#ifdef LPUART_IP_11
/* Implementation of LPUART11 TX and RX interrupt handler for LIN driver */
ISR(LPUART11_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(11U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART11 error interrupt handler for LIN driver */
ISR(LPUART11_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(11U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_11 */
#endif /* if (LPUART_INSTANCE_COUNT > 11U) */


#if (LPUART_INSTANCE_COUNT > 12U)
#ifdef LPUART_IP_12
/* Implementation of LPUART12 TX and RX interrupt handler for LIN driver */
ISR(LPUART12_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(12U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART12 error interrupt handler for LIN driver */
ISR(LPUART12_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(12U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_12 */
#endif /* if (LPUART_INSTANCE_COUNT > 12U) */


#if (LPUART_INSTANCE_COUNT > 13U)
#ifdef LPUART_IP_13
/* Implementation of LPUART13 TX and RX interrupt handler for LIN driver */
ISR(LPUART13_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(13U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART13 error interrupt handler for LIN driver */
ISR(LPUART13_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(13U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_13 */
#endif /* if (LPUART_INSTANCE_COUNT > 13U) */


#if (LPUART_INSTANCE_COUNT > 14U)
#ifdef LPUART_IP_14
/* Implementation of LPUART14 TX and RX interrupt handler for LIN driver */
ISR(LPUART14_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(14U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART14 error interrupt handler for LIN driver */
ISR(LPUART14_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(14U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_14 */
#endif /* if (LPUART_INSTANCE_COUNT > 14U) */


#if (LPUART_INSTANCE_COUNT > 15U)
#ifdef LPUART_IP_15
/* Implementation of LPUART15 TX and RX interrupt handler for LIN driver */
ISR(LPUART15_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(15U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
/* Implementation of LPUART15 error interrupt handler for LIN driver */
ISR(LPUART15_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(15U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_15 */
#endif /* if (LPUART_INSTANCE_COUNT > 15U) */

#if (LPUART_INSTANCE_COUNT > 16U)
#ifdef LPUART_IP_16
ISR(LPUART16_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(16U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART16_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(16U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_16 */
#endif /* if (LPUART_INSTANCE_COUNT > 16U) */


#if (LPUART_INSTANCE_COUNT > 17U)
#ifdef LPUART_IP_17
ISR(LPUART17_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(17U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART17_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(17U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_17 */
#endif /* if (LPUART_INSTANCE_COUNT > 17U) */


#if (LPUART_INSTANCE_COUNT > 18U)
#ifdef LPUART_IP_18
ISR(LPUART18_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(18U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART18_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(18U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_18 */
#endif /* if (LPUART_INSTANCE_COUNT > 18U) */


#if (LPUART_INSTANCE_COUNT > 19U)
#ifdef LPUART_IP_19
ISR(LPUART19_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(19U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART19_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(18U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_19 */
#endif /* if (LPUART_INSTANCE_COUNT > 19U) */



#if (LPUART_INSTANCE_COUNT > 20U)
#ifdef LPUART_IP_20
ISR(LPUART20_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(20U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART20_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(20U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_20 */
#endif /* if (LPUART_INSTANCE_COUNT > 20U) */

#if (LPUART_INSTANCE_COUNT > 21U)
#ifdef LPUART_IP_21
ISR(LPUART21_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(21U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART21_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(21U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_21 */
#endif /* if (LPUART_INSTANCE_COUNT > 21) */

#if (LPUART_INSTANCE_COUNT > 22U)
#ifdef LPE_LPUART_IP_0
ISR(LPE_LPUART0_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(22U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART22_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(22U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPUART_IP_22 */
#endif /* if (LPUART_INSTANCE_COUNT > 22U) */

#if (LPUART_INSTANCE_COUNT > 23U)
#ifdef LPE_LPUART_IP_1
ISR(LPE_LPUART1_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(23U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART23_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(23U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPE_LPUART_IP_1 */
#endif /* if (LPUART_INSTANCE_COUNT > 23U) */


#if (LPUART_INSTANCE_COUNT > 24U)
#ifdef LPE_LPUART_IP_2
ISR(LPE_LPUART2_LIN_IP_RxTx_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(24U);
    EXIT_INTERRUPT();
}

#ifdef LPUART_LIN_IP_ERR_IRQS
ISR(LPUART24_LIN_IP_ERR_IRQHandler)
{
    Lpuart_Lin_Ip_IRQHandler(24U);
    EXIT_INTERRUPT();
}
#endif /* LPUART_LIN_IP_ERR_IRQS */
#endif /* LPE_LPUART_IP_2 */
#endif /* if (LPUART_INSTANCE_COUNT > 24U) */
#if (LPUART_LIN_IP_HAS_DMA_ENABLED == STD_ON)
#if (LPUART_INSTANCE_COUNT > 0U)
#ifdef LPUART_IP_0
/* Implementation of Lpuart0 Rx callback function for Dma interrupt. */
void Lpuart_0_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(0);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
#ifdef LPUART_IP_1
/* Implementation of Lpuart1 Rx callback function for Dma interrupt. */
void Lpuart_1_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(1);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
#ifdef LPUART_IP_2
/* Implementation of Lpuart2 Rx callback function for Dma interrupt. */
void Lpuart_2_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(2);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 3U)
#ifdef LPUART_IP_3
/* Implementation of Lpuart3 Rx callback function for Dma interrupt. */
void Lpuart_3_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(3);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 4U)
#ifdef LPUART_IP_4
/* Implementation of Lpuart4 Rx callback function for Dma interrupt. */
void Lpuart_4_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(4);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 5U)
#ifdef LPUART_IP_5
/* Implementation of Lpuart5 Rx callback function for Dma interrupt. */
void Lpuart_5_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(5);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 6U)
#ifdef LPUART_IP_6
/* Implementation of Lpuart6 Rx callback function for Dma interrupt. */
void Lpuart_6_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(6);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 7U)
#ifdef LPUART_IP_7
/* Implementation of Lpuart7 Rx callback function for Dma interrupt. */
void Lpuart_7_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(7);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 8U)
#ifdef LPUART_IP_8
/* Implementation of Lpuart8 Rx callback function for Dma interrupt. */
void Lpuart_8_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(8);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 9U)
#ifdef LPUART_IP_9
/* Implementation of Lpuart9 Rx callback function for Dma interrupt. */
void Lpuart_9_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(9);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 10U)
#ifdef LPUART_IP_10
/* Implementation of Lpuart10 Rx callback function for Dma interrupt. */
void Lpuart_10_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(10);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 11U)
#ifdef LPUART_IP_11
/* Implementation of Lpuart11 Rx callback function for Dma interrupt. */
void Lpuart_11_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(11);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 12U)
#ifdef LPUART_IP_12
/* Implementation of Lpuart12 Rx callback function for Dma interrupt. */
void Lpuart_12_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(12);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 13U)
#ifdef LPUART_IP_13
/* Implementation of Lpuart13 Rx callback function for Dma interrupt. */
void Lpuart_13_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(13);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 14U)
#ifdef LPUART_IP_14
/* Implementation of Lpuart14 Rx callback function for Dma interrupt. */
void Lpuart_14_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(14);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 15U)
#ifdef LPUART_IP_15
/* Implementation of Lpuart15 Rx callback function for Dma interrupt. */
void Lpuart_15_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(15);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 16U)
#ifdef LPUART_IP_16
/* Implementation of Lpuart16 Rx callback function for Dma interrupt. */
void Lpuart_16_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(16);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 17U)
#ifdef LPUART_IP_17
/* Implementation of Lpuart17 Rx callback function for Dma interrupt. */
void Lpuart_17_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(16);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 18U)
#ifdef LPUART_IP_18
/* Implementation of Lpuart18 Rx callback function for Dma interrupt. */
void Lpuart_18_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(16);
}
#endif
#endif
#if (LPUART_INSTANCE_COUNT > 19U)
#ifdef LPUART_IP_19
/* Implementation of Lpuart18 Rx callback function for Dma interrupt. */
void Lpuart_19_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(19);
}
#endif
#endif
#if (LPUART_INSTANCE_COUNT > 20U)
#ifdef LPUART_IP_20
/* Implementation of Lpuart20 Rx callback function for Dma interrupt. */
void Lpuart_20_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(20);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 21U)
#ifdef LPUART_IP_21
/* Implementation of Lpuart21 Rx callback function for Dma interrupt. */
void Lpuart_21_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(21);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 22U)
#ifdef LPE_LPUART_IP_0
/* Implementation of Lpe_Lpuart0 Rx callback function for Dma interrupt. */
void Lpe_Lpuart0_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(22);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 23U)
#ifdef LPE_LPUART_IP_1
/* Implementation of Lpe_Lpuart1 Rx callback function for Dma interrupt. */
void Lpe_Lpuart1_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(23);
}
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 24U)
#ifdef LPE_LPUART_IP_2
/* Implementation of Lpe_Lpuart2 Rx callback function for Dma interrupt. */
void Lpe_Lpuart2_Lin_Ip_DmaRxCompleteCallback(void)
{
    Lpuart_Lin_Ip_CompleteReceiveUsingDma(24);
}
#endif
#endif

#endif
#define LIN_43_LPUART_FLEXIO_STOP_SEC_CODE
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
