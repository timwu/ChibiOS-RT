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

static volatile uint8_t* mask_registers[] = {
#ifdef PCMSK0
    &PCMSK0,
#endif
#ifdef PCMSK1
    &PCMSK1,
#endif
#ifdef PCMSK2
    &PCMSK1
#endif
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#ifdef PCINT0
CH_IRQ_HANDLER(PCINT0_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 0)(&EXTD1, 0);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT1
CH_IRQ_HANDLER(PCINT1_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 1)(&EXTD1, 1);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT2
CH_IRQ_HANDLER(PCINT2_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 2)(&EXTD1, 2);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT3
CH_IRQ_HANDLER(PCINT3_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 3)(&EXTD1, 3);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT4
CH_IRQ_HANDLER(PCINT4_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 4)(&EXTD1, 4);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT5
CH_IRQ_HANDLER(PCINT5_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 5)(&EXTD1, 5);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT6
CH_IRQ_HANDLER(PCINT6_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 6)(&EXTD1, 6);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT7
CH_IRQ_HANDLER(PCINT7_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 7)(&EXTD1, 7);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT8
CH_IRQ_HANDLER(PCINT8_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 8)(&EXTD1, 8);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT9
CH_IRQ_HANDLER(PCINT9_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 9)(&EXTD1, 9);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT10
CH_IRQ_HANDLER(PCINT10_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 10)(&EXTD1, 10);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT11
CH_IRQ_HANDLER(PCINT11_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 11)(&EXTD1, 11);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT12
CH_IRQ_HANDLER(PCINT12_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 12)(&EXTD1, 12);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT13
CH_IRQ_HANDLER(PCINT13_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 13)(&EXTD1, 13);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT14
CH_IRQ_HANDLER(PCINT14_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 14)(&EXTD1, 14);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT15
CH_IRQ_HANDLER(PCINT15_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 15)(&EXTD1, 15);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT16
CH_IRQ_HANDLER(PCINT16_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 16)(&EXTD1, 16);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT17
CH_IRQ_HANDLER(PCINT17_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 17)(&EXTD1, 17);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT18
CH_IRQ_HANDLER(PCINT18_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 18)(&EXTD1, 18);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT19
CH_IRQ_HANDLER(PCINT19_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 19)(&EXTD1, 19);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT20
CH_IRQ_HANDLER(PCINT20_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 20)(&EXTD1, 20);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT21
CH_IRQ_HANDLER(PCINT21_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 21)(&EXTD1, 21);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT22
CH_IRQ_HANDLER(PCINT22_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 22)(&EXTD1, 22);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT23
CH_IRQ_HANDLER(PCINT23_vect) {
  CH_IRQ_PROLOGUE();
  get_cb(&EXTD1, 23)(&EXTD1, 23);
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
      // TODO: Fix to be automatic
      PCICR = _BV(PCIE0) | _BV(PCIE1) | _BV(PCIE2);
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
      PCICR = 0;
#ifdef PCMSK0
      PCMSK0 = 0;
#endif
#ifdef PCMSK1
      PCMSK1 = 0;
#endif
#ifdef PCMSK2
      PCMSK2 = 0;
#endif
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
      if (get_cb(extp, channel) != NULL && get_mode(extp, channel)) {
        *mask_registers[channel / 8] |= _BV(channel % 8);
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
      *mask_registers[channel / 8] &= ~(_BV(channel % 8));
    }
#endif /* PLATFORM_EXT_USE_EXT1 */
}

#endif /* HAL_USE_EXT */

/** @} */
