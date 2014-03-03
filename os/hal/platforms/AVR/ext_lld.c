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

#define CHANNELS_PER_VECTOR 8

#ifdef PCMSK2
#define N_VECTORS 3
#elif defined (PCMSK1)
#define N_VECTORS 2
#elif defined (PCMSK0)
#define N_VECTORS 1
#endif

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

typedef struct {
  volatile uint8_t *port;
  volatile uint8_t *pin;
  volatile uint8_t *ddr;
  uint8_t pad;
} pin_spec;

static pin_spec pc_int_pins[] = {
    {&PORTB, &PINB, &DDRB, 0}, // PCINT0
    {&PORTB, &PINB, &DDRB, 1}, // PCINT1
    {&PORTB, &PINB, &DDRB, 2}, // PCINT2
    {&PORTB, &PINB, &DDRB, 3}, // PCINT3
    {&PORTB, &PINB, &DDRB, 4}, // PCINT4
    {&PORTB, &PINB, &DDRB, 5}, // PCINT5
    {&PORTB, &PINB, &DDRB, 6}, // PCINT6
    {&PORTB, &PINB, &DDRB, 7}, // PCINT7
#if defined(__AVR_ATmega1280__)
    {&PORTE, &PINE, &DDRE, 0}, // PCINT8
    {&PORTJ, &PINJ, &DDRJ, 0}, // PCINT9
    {&PORTJ, &PINJ, &DDRJ, 1}, // PCINT10
    {&PORTJ, &PINJ, &DDRJ, 2}, // PCINT11
    {&PORTJ, &PINJ, &DDRJ, 3}, // PCINT12
    {&PORTJ, &PINJ, &DDRJ, 4}, // PCINT13
    {&PORTJ, &PINJ, &DDRJ, 5}, // PCINT14
    {&PORTJ, &PINJ, &DDRJ, 6}, // PCINT15
    {&PORTK, &PINK, &DDRK, 0}, // PCINT16
    {&PORTK, &PINK, &DDRK, 1}, // PCINT17
    {&PORTK, &PINK, &DDRK, 2}, // PCINT18
    {&PORTK, &PINK, &DDRK, 3}, // PCINT19
    {&PORTK, &PINK, &DDRK, 4}, // PCINT20
    {&PORTK, &PINK, &DDRK, 5}, // PCINT21
    {&PORTK, &PINK, &DDRK, 6}, // PCINT22
    {&PORTK, &PINK, &DDRK, 7}, // PCINT23
#else
#error "Not a supported MCU"
#endif
};


/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static uint8_t get_current_values(uint8_t interrupt) {
  if (interrupt == 0) {
    return PINB;
#if defined (__AVR_ATmega1280__)
  } else if (interrupt == 2) {
    return PINK;
#endif
  } else {
    uint8_t value = 0, channel = 0, int_offset = (interrupt * CHANNELS_PER_VECTOR);
    for (channel = 0; channel < CHANNELS_PER_VECTOR; channel++) {
      if (*pc_int_pins[int_offset + channel].pin & _BV(pc_int_pins[int_offset + channel].pad)) {
        value |= _BV(channel);
      }
    }
    return value;
  }
}

static uint8_t handle_interrupt(uint8_t int_vector, uint8_t previous_vals) {
  uint8_t cur_vals = get_current_values(int_vector);
  uint8_t changed = (cur_vals ^ previous_vals) & *mask_registers[int_vector];
  uint8_t channel = 0, channel_offset = int_vector * CHANNELS_PER_VECTOR;
  for (channel = 0; channel < CHANNELS_PER_VECTOR; channel++) {
    if (changed & _BV(channel)) {
      get_cb(&EXTD1, channel + channel_offset)(&EXTD1, channel + channel_offset);
    }
  }
  return cur_vals;
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#ifdef PCINT0_vect
static volatile uint8_t pin_vals_0 = 0;
CH_IRQ_HANDLER(PCINT0_vect) {
  CH_IRQ_PROLOGUE();
  pin_vals_0 = handle_interrupt(0, pin_vals_0);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT1_vect
volatile static uint8_t pin_vals_1 = 0;
CH_IRQ_HANDLER(PCINT1_vect) {
  CH_IRQ_PROLOGUE();
  pin_vals_1 = handle_interrupt(1, pin_vals_1);
  CH_IRQ_EPILOGUE();
}
#endif

#ifdef PCINT2_vect
volatile static uint8_t pin_vals_2 = 0;
CH_IRQ_HANDLER(PCINT2_vect) {
  CH_IRQ_PROLOGUE();
  pin_vals_2 = handle_interrupt(2, pin_vals_2);
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
      uint8_t i;

      PCICR = (1 << N_VECTORS) - 1;
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
      uint8_t i;

      PCICR = 0;
      for (i = 0; i < N_VECTORS; i++) {
        *mask_registers[i] = 0;
      }
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
        *pc_int_pins[channel].ddr &= ~_BV(pc_int_pins[channel].pad);
        *pc_int_pins[channel].port &= ~_BV(pc_int_pins[channel].pad);
        // TODO: Read out the pin into the pin_vals_X variable
        *mask_registers[channel / 8] |= _BV(channel % CHANNELS_PER_VECTOR);
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
      *mask_registers[channel / 8] &= ~(_BV(channel % CHANNELS_PER_VECTOR));
    }
#endif /* PLATFORM_EXT_USE_EXT1 */
}

#endif /* HAL_USE_EXT */

/** @} */
