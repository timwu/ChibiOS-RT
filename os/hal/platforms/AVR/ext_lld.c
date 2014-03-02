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
  uint8_t modeTemp = 0;
  if (extp->state == EXT_STOP) {
    /* Enables the peripheral.*/
#if PLATFORM_EXT_USE_EXT1
    if (&EXTD1 == extp) {
#ifdef INT0
      EICRA &= ~(_BV(ISC01) | _BV(ISC00));
      EICRA |= convert_mode_bits(get_mode(extp, 0), ISC01, ISC00);
      if (is_autostart(extp, 0)) { ext_lld_channel_enable(extp, 0); }
#endif
#ifdef INT1
      EICRA &= ~(_BV(ISC11) | _BV(ISC10));
      EICRA |= convert_mode_bits(get_mode(extp, 1), ISC11, ISC10);
      if (is_autostart(extp, 1)) { ext_lld_channel_enable(extp, 1); }
#endif
#ifdef INT2
      EICRA &= ~(_BV(ISC21) | _BV(ISC20));
      EICRA |= convert_mode_bits(get_mode(extp, 2), ISC21, ISC20);
      if (is_autostart(extp, 2)) { ext_lld_channel_enable(extp, 2); }
#endif
#ifdef INT3
      EICRA &= ~(_BV(ISC31) | _BV(ISC30));
      EICRA |= convert_mode_bits(get_mode(extp, 3), ISC31, ISC30);
      if (is_autostart(extp, 3)) { ext_lld_channel_enable(extp, 3); }
#endif
#ifdef INT4
      EICRB &= ~(_BV(ISC41) | _BV(ISC40));
      EICRB |= convert_mode_bits(get_mode(extp, 4), ISC41, ISC40);
      if (is_autostart(extp, 4)) { ext_lld_channel_enable(extp, 4); }
#endif
#ifdef INT5
      EICRB &= ~(_BV(ISC51) | _BV(ISC50));
      EICRB |= convert_mode_bits(get_mode(extp, 5), ISC51, ISC50);
      if (is_autostart(extp, 5)) { ext_lld_channel_enable(extp, 5); }
#endif
#ifdef INT6
      EICRB &= ~(_BV(ISC61) | _BV(ISC60));
      EICRB |= convert_mode_bits(get_mode(extp, 6), ISC61, ISC60);
      if (is_autostart(extp, 6)) { ext_lld_channel_enable(extp, 6); }
#endif
#ifdef INT7
      EICRB &= ~(_BV(ISC71) | _BV(ISC70));
      EICRB |= convert_mode_bits(get_mode(extp, 7), ISC71, ISC70);
      if (is_autostart(extp, 7)) { ext_lld_channel_enable(extp, 7); }
#endif
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
