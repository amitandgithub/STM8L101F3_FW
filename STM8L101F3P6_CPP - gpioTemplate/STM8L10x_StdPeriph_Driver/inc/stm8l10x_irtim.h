/**
  ******************************************************************************
  * @file    stm8l10x_irtim.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    01-June-2012
  * @brief   This file contains all functions prototype and macros for the IRTIM
  *          peripheral.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L10x_IRTIM_H
#define __STM8L10x_IRTIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup IRTIM_Exported_Functions
  * @{
  */

void IRTIM_DeInit(void);
void IRTIM_Cmd(FunctionalState NewState);
FunctionalState IRTIM_GetStatus(void);
void IRTIM_HighSinkODCmd(FunctionalState Newstate);
FunctionalState IRTIM_GetHighSinkODStatus(void);


/**
  * @}
  */
#endif /* __STM8L10x_IRTIM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
