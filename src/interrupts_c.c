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

#ifdef VVC_F0
// STM32F0xx EXTI lines.
/*
 * EXTI0_1: Handle interrupt lines 0 and 1.
 */
void EXTI0_1_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_0)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_1)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
}
return;
}

/*
 * EXTI2_3: Handle interrupt lines 2 and 3.
 */
void EXTI2_3_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_2)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
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
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_3)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
  // 'Up' button.
  if (menu_state == TEST_MENU_BUZZER_TONE) {
    menu_state = last_top_row;
  }
}
return;
}

/*
 * EXTI4_15: Handle interrupt lines between [4:15], inclusive.
 */
void EXTI4_15_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_4)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
  // 'Down' button.
  if (menu_state == TEST_MENU_LED_TOGGLE ||
      menu_state == TEST_MENU_SOUND_BUZZER) {
    last_top_row = menu_state;
    menu_state = TEST_MENU_BUZZER_TONE;
  }
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_5)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
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
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_6)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
  // 'B' button.
  // Currently, do nothing.
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_7)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
  // 'A' button.
  // Action depends on menu state.
  if (menu_state == TEST_MENU_LED_TOGGLE) {
    uled_state = !uled_state;
  }
  else if (menu_state == TEST_MENU_SOUND_BUZZER) {
    buzzer_state = 1;
  }
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_8)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_9)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_9);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_10)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_11)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_12)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_13)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_14)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_15)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
}
return;
}


#elif VVC_F3
// STM32F3xx(?) EXTI lines.
// TODO: Move common code between F0/F3 to their own methods.
// But for testing...
void EXTI2_touchsense_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_2)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
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
return;
}

void EXTI3_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_3)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
  // 'Up' button.
  if (menu_state == TEST_MENU_BUZZER_TONE) {
    menu_state = last_top_row;
  }
}
return;
}

void EXTI4_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_4)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
  // 'Down' button.
  if (menu_state == TEST_MENU_LED_TOGGLE ||
      menu_state == TEST_MENU_SOUND_BUZZER) {
    last_top_row = menu_state;
    menu_state = TEST_MENU_BUZZER_TONE;
  }
}
return;
}

void EXTI5_9_IRQ_handler(void) {
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_5)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
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
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_6)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
  // 'B' button.
  // Currently, do nothing.
}
if (LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_7)) {
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
  // 'A' button.
  // Action depends on menu state.
  if (menu_state == TEST_MENU_LED_TOGGLE) {
    uled_state = !uled_state;
  }
  else if (menu_state == TEST_MENU_SOUND_BUZZER) {
    buzzer_state = 1;
  }
}
return;
}

#endif
