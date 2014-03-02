/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    templates/ext_lld.c
 * @brief   EXT Driver subsystem low level driver source template.
 *
 * @addtogroup EXT
 * @{
 */

#include "ch.h"
#include "hal.h"

#if HAL_USE_EXT || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#define shift_to_index(i, x) (((x) << i) << i)

#define get_channel(driver, channel) ((driver)->config->channels[(channel)])

#define get_cb(driver, channel) (get_channel(driver, channel).cb)

#define get_mode(driver, channel) (get_channel(driver, channel).mode)

#define is_autostart(driver, channel) (get_mode(driver, channel) & EXT_CH_MODE_AUTOSTART)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   EXT1 driver identifier.
 */
#if PLATFORM_EXT_USE_EXT1 || defined(__DOXYGEN__)
EXTDriver EXTD1;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

static volatile uint8_t* control_registers[] = {
#ifdef EICRA
    &EICRA,
#endif
#ifdef EICRB
    &EICRB
#endif
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

INLINE uint8_t convert_mode_bits(uint32_t mode, uint8_t bit1, uint8_t bit0) {
  switch (mode & EXT_CH_MODE_EDGES_MASK) {
    case EXT_CH_MODE_BOTH_EDGES:
      return _BV(bit0); // 1
    case EXT_CH_MODE_FALLING_EDGE:
      return _BV(bit1); // 2
    case EXT_CH_MODE_RISING_EDGE:
      return _BV(bit1) | _BV(bit0); // 3
  }
  return 0;
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#ifdef INT0
CH_IRQ_HANDLER(INT0_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 0)(&EXTD1, 0);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT1
CH_IRQ_HANDLER(INT1_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 1)(&EXTD1, 1);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT2
CH_IRQ_HANDLER(INT2_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 2)(&EXTD1, 2);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT3
CH_IRQ_HANDLER(INT3_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 3)(&EXTD1, 3);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT4
CH_IRQ_HANDLER(INT4_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 4)(&EXTD1, 4);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT5
CH_IRQ_HANDLER(INT5_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 5)(&EXTD1, 5);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT6
CH_IRQ_HANDLER(INT6_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 6)(&EXTD1, 6);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef INT7
CH_IRQ_HANDLER(INT7_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 7)(&EXTD1, 7);
  CH_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level EXT driver initialization.
 *
 * @notapi
 */
void ext_lld_init(void) {

#if PLATFORM_EXT_USE_EXT1
  /* Driver initialization.*/
  extObjectInit(&EXTD1);
#endif /* PLATFORM_EXT_USE_EXT1 */
}

/**
 * @brief   Configures and activates the EXT peripheral.
 *
 * @param[in] extp      pointer to the @p EXTDriver object
 *
 * @notapi
 */
void ext_lld_start(EXTDriver *extp) {
  if (extp->state == EXT_STOP) {
    /* Enables the peripheral.*/
#if PLATFORM_EXT_USE_EXT1
    if (&EXTD1 == extp) {
      uint8_t i = 0;
      for (i = 0; i < EXT_MAX_CHANNELS; i++) {
        if (is_autostart(extp, i)) { ext_lld_channel_enable(extp, i); }
      }
    }
#endif /* PLATFORM_EXT_USE_EXT1 */
  }
  /* Configures the peripheral.*/

}

/**
 * @brief   Deactivates the EXT peripheral.
 *
 * @param[in] extp      pointer to the @p EXTDriver object
 *
 * @notapi
 */
void ext_lld_stop(EXTDriver *extp) {

  if (extp->state == EXT_ACTIVE) {
    /* Resets the peripheral.*/

    /* Disables the peripheral.*/
#if PLATFORM_EXT_USE_EXT1
    if (&EXTD1 == extp) {
#ifdef EICRA
      EICRA = 0;
#endif
#ifdef EICRB
      EICRB = 0;
#endif
      EIMSK = 0;
    }
#endif /* PLATFORM_EXT_USE_EXT1 */
  }
}

/**
 * @brief   Enables an EXT channel.
 *
 * @param[in] extp      pointer to the @p EXTDriver object
 * @param[in] channel   channel to be enabled
 *
 * @notapi
 */
void ext_lld_channel_enable(EXTDriver *extp, expchannel_t channel) {
#if PLATFORM_EXT_USE_EXT1
    if (&EXTD1 == extp) {
      if (get_cb(extp, channel) != NULL) {
        uint8_t configBit0 = (channel % 4);
        *control_registers[channel / 4] &= ~(_BV(configBit0) | _BV(configBit0 + 1));
        *control_registers[channel / 4]  |= convert_mode_bits(get_mode(extp, channel), configBit0 + 1, configBit0);
        EIMSK |= _BV(channel);
      }
    }
#endif /* PLATFORM_EXT_USE_EXT1 */
}

/**
 * @brief   Disables an EXT channel.
 *
 * @param[in] extp      pointer to the @p EXTDriver object
 * @param[in] channel   channel to be disabled
 *
 * @notapi
 */
void ext_lld_channel_disable(EXTDriver *extp, expchannel_t channel) {
#if PLATFORM_EXT_USE_EXT1
    if (&EXTD1 == extp) {
      if (get_cb(extp, channel) != NULL) {
        EIMSK &= ~(_BV(channel));
      }
    }
#endif /* PLATFORM_EXT_USE_EXT1 */
}

#endif /* HAL_USE_EXT */

/** @} */
