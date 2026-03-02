/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : LPI2C
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 6.0.0
* Build Version : S32K3_RTD_6_0_0_D2506_ASR_REL_4_7_REV_0000_20250610
*
* Copyright 2020 - 2025 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may
* only be used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup LPI2C_DRIVER_CONFIGURATION Lpi2c Driver Configurations
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
#include "Lpi2c_Ip_MBDT_PBcfg.h"

#if (STD_ON == LPI2C_IP_DMA_FEATURE_AVAILABLE)
#include "Dma_Ip_Cfg.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPI2C_IP_MBDT_PBCFG_VENDOR_ID_C                     43
#define LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define LPI2C_IP_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define LPI2C_IP_MBDT_PBCFG_SW_MAJOR_VERSION_C              6
#define LPI2C_IP_MBDT_PBCFG_SW_MINOR_VERSION_C              0
#define LPI2C_IP_MBDT_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Lpi2c_Ip_MBDT_PBcfg.h header file are of the same vendor */
#if (LPI2C_IP_MBDT_PBCFG_VENDOR_ID_C != LPI2C_IP_MBDT_PBCFG_VENDOR_ID)
    #error "Lpi2c_Ip_MBDT_PBcfg.c and Lpi2c_Ip_MBDT_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Lpi2c_Ip_MBDT_PBcfg.h header file are of the same Autosar version */
#if ((LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C != LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C != LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (LPI2C_IP_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION_C != LPI2C_IP_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Lpi2c_Ip_MBDT_PBcfg.c and Lpi2c_Ip_MBDT_PBcfg.h are different"
#endif
/* Check if current file and Lpi2c_Ip_MBDT_PBcfg.h header file are of the same Software version */
#if ((LPI2C_IP_MBDT_PBCFG_SW_MAJOR_VERSION_C != LPI2C_IP_MBDT_PBCFG_SW_MAJOR_VERSION) || \
     (LPI2C_IP_MBDT_PBCFG_SW_MINOR_VERSION_C != LPI2C_IP_MBDT_PBCFG_SW_MINOR_VERSION) || \
     (LPI2C_IP_MBDT_PBCFG_SW_PATCH_VERSION_C != LPI2C_IP_MBDT_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lpi2c_Ip_MBDT_PBcfg.c and Lpi2c_Ip_MBDT_PBcfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (STD_ON == LPI2C_IP_DMA_FEATURE_AVAILABLE)
    /* Check if current file and Dma_Ip_Cfg header file are of the same Autosar version */
        #if ((LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DMA_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
             (LPI2C_IP_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C != DMA_IP_CFG_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of Lpi2c_Ip_MBDT_PBcfg.c and Dma_Ip_Cfg.h are different"
        #endif
    #endif /* LPI2C_IP_DMA_FEATURE_AVAILABLE */
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */


/*==================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

#define I2C_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "I2c_MemMap.h"


const Lpi2c_Ip_SlaveConfigType I2c_Lpi2cSlave_HwChannel0_Channel1_MBDT =
{
    /* .SlaveAddress */     50U,
    /* .Is10bitAddr */      (boolean)FALSE,
    /* .SlaveListening */   (boolean)FALSE,
    /* .OperatingMode */    LPI2C_STANDARD_MODE,
    /* .TransferType */     LPI2C_USING_INTERRUPTS,
    /* .GlitchFilterSDA */  0U,
    /* .GlitchFilterSCL */  0U,
    /* .ClockStretching */  0U,
    /* .DmaTxChannel */     0U,
    /* .DmaRxChannel */     0U,
    /* .SlaveCallback */    NULL_PTR,
    /* .CallbackParam */    1U,
    /* .SlaveStateIdx */    0U
};

#define I2C_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "I2c_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

