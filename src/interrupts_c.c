#include "interrupts_c.h"

// C-language hardware interrupt method definitions.
/*
 * Each EXTI line between 0-15 can map to a GPIO pin.
 * The EXTI line number is the same as the pin number, and
 * each pin number can only have its interrupt active on
 * ONE (1) of its GPIO banks. So for example, you can have
 * an interrupt on pin A0 (EXTI line 0) and pin B1 (EXTI line 1)
 * at the same time, but not on pins A1 (EXTI line 1)
 * and B1 (EXTI line 1), since they share the same interrupt line.
 */
// Common definitions for each line, independent of
// available NVIC interrupts on any specific chip.
void EXTI0_line_interrupt(void) {
}

void EXTI1_line_interrupt(void) {
}

void EXTI2_line_interrupt(void) {
  // 'Left' button.
  if (menu_state == TEST_MENU_SOUND_BUZZER) {
    menu_state = TEST_MENU_LED_TOGGLE;
  }
  else if (menu_state == TEST_MENU_BUZZER_TONE) {
    buzzer_tone_hz -= 500;
    if (buzzer_tone_hz <= 0) {
      buzzer_tone_hz = 500;
    }
  }
}

void EXTI3_line_interrupt(void) {
  // 'Up' button.
  if (menu_state == TEST_MENU_BUZZER_TONE) {
    menu_state = last_top_row;
  }
}

void EXTI4_line_interrupt(void) {
  // 'Down' button.
  if (menu_state == TEST_MENU_LED_TOGGLE ||
      menu_state == TEST_MENU_SOUND_BUZZER) {
    last_top_row = menu_state;
    menu_state = TEST_MENU_BUZZER_TONE;
  }
}

void EXTI5_line_interrupt(void) {
  // 'Right' button.
  if (menu_state == TEST_MENU_LED_TOGGLE) {
    menu_state = TEST_MENU_SOUND_BUZZER;
  }
  else if (menu_state == TEST_MENU_BUZZER_TONE) {
    buzzer_tone_hz += 500;
    if (buzzer_tone_hz >= 25000) {
      buzzer_tone_hz = 25000;
    }
  }
}

void EXTI6_line_interrupt(void) {
  // 'B' button.
  // Currently, do nothing.
}

void EXTI7_line_interrupt(void) {
  // 'A' button.
  // Action depends on menu state.
  if (menu_state == TEST_MENU_LED_TOGGLE) {
    uled_state = !uled_state;
  }
  else if (menu_state == TEST_MENU_SOUND_BUZZER) {
    buzzer_state = 1;
  }
}

void EXTI8_line_interrupt(void) {
}

void EXTI9_line_interrupt(void) {
}

void EXTI10_line_interrupt(void) {
}

void EXTI11_line_interrupt(void) {
}

void EXTI12_line_interrupt(void) {
}

void EXTI13_line_interrupt(void) {
}

void EXTI14_line_interrupt(void) {
}

void EXTI15_line_interrupt(void) {
}

#ifdef VVC_F0
// STM32F0xx EXTI lines.
/*
 * EXTI0_1: Handle interrupt lines 0 and 1.
 */
void EXTI0_1_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_0)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
  EXTI0_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_1)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
  EXTI1_line_interrupt();
}
return;
}

/*
 * EXTI2_3: Handle interrupt lines 2 and 3.
 */
void EXTI2_3_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_2)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
  EXTI2_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_3)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
  EXTI3_line_interrupt();
}
return;
}

/*
 * EXTI4_15: Handle interrupt lines between [4:15], inclusive.
 */
void EXTI4_15_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_4)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
  EXTI4_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_5)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
  EXTI5_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_6)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
  EXTI6_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_7)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
  EXTI7_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_8)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);
  EXTI8_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_9)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_9);
  EXTI9_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_10)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
  EXTI10_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_11)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
  EXTI11_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_12)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
  EXTI12_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_13)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
  EXTI13_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_14)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
  EXTI14_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_15)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
  EXTI15_line_interrupt();
}
return;
}


#elif VVC_F3
// STM32F3xx(?) EXTI lines.
void EXTI2_touchsense_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_2)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
  EXTI2_line_interrupt();
}
return;
}

void EXTI3_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_3)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
  EXTI3_line_interrupt();
}
return;
}

void EXTI4_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_4)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
  EXTI4_line_interrupt();
}
return;
}

void EXTI5_9_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_5)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
  EXTI5_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_6)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
  EXTI6_line_interrupt();
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_7)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
  EXTI7_line_interrupt();
}
return;
}

#endif
