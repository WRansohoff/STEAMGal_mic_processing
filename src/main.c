#include "main.h"

/**
 * Main program.
 */
int main(void) {
  // Define starting values for global variables.
  uled_state = 0;
  buzzer_state = 0;
  buzzer_tone = 15000;
  buzzer_tone_hz = 15000;
  buzzer_pulses = 500;
  menu_state = TEST_MENU_LED_TOGGLE;
  last_top_row = TEST_MENU_LED_TOGGLE;
  draw_color = 0;
  last_adc_value = 0;
  // Reset the ADC buffer to 0s.
  adc_buf_pos = 0;
  uint16_t adc_iter = 0;
  for (adc_iter = 0; adc_iter < ADC_MIC_SAMPLES; ++adc_iter) {
    adc_buffer[adc_iter] = 0;
  }

  // Enable the GPIOA clock (buttons on pins A2-A7,
  // user LED on pin A12).
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  // Enable the GPIOB clock (I2C1 used on pins B6/B7,
  // buzzer on pin B0).
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  // Enable the I2C1 clock.
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  // Enable the TIM2 clock.
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  // Enable the SYSCFG clock for hardware interrupts.
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  // Enable the ADC1 clock for Analog/Digital Conversion.
  #ifdef VVC_F0
    // Enable ADC1 clock.
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  #elif VVC_F3
    // Enable clocks for the ADCs.
    RCC->AHBENR  |= RCC_AHBENR_ADC12EN;
  #endif

  // Setup GPIO pins A2, A3, A4, A5, A6, and A7 as inputs
  // with pullups, low-speed.
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_4, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);

  // Setup GPIO pin A12 as push-pull output, no pupdr,
  // 10MHz max speed.
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_MEDIUM);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_12, LL_GPIO_PULL_NO);

  // Setup GPIO pin B0 as push-pull output, no pupdr,
  // 10MHz max speed.
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_0, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_MEDIUM);
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_0, LL_GPIO_PULL_NO);

  #ifdef VVC_F0
    // Set GPIO pins B6/B7 as alternate function mode 1 for I2C1.
    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_1);
    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_7, LL_GPIO_AF_1);
  #elif VVC_F3
    // Set GPIO pins B6/B7 as alternate function mode 4 for I2C1.
    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_4);
    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_7, LL_GPIO_AF_4);
  #endif
  // Setup GPIO pins B6, B7 as open-drain alt. func. w/pullup.
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);

  /*
   * Board connectors:
   * A8/A9:        4-pin JST connector 1
   * A10/A11:      4-pin JST connector 2
   * A15/B3/B4/B5: 'GPIO2' 6-pin header; can be used for SPI1.
   * A0/A1/B0:     'GPIO2' 5-pin header.
   * B6/B7:        I2C1 provided on a 4-pin header.
   * Note: Re-assigning pins B6/B7 will disable the screen!
   * The I2C1 bus is provided for communicating with other
   * devices such as sensors, not for GPIO. I2C supports
   * multiple receiving devices on the same line, so long
   * as they have different addresses.
   * (The screen's address is 0x78)
   */
  // Setup pin A1 for ADC input.
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_1, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_1, LL_GPIO_PULL_NO);

  // Initialize the I2C peripheral and connected devices.
  // (1MHz @ 48MHz PLL)
  i2c_periph_init(I2C1_BASE, 0x50100103);
  // Initialize the SSD1306 OLED display.
  i2c_init_ssd1306(I2C1_BASE);

  // Initialize the ADC peripheral for listening on pin A1.
  // (F3xx: ADC1 Channel 2, F0xx: ADC[1] Channel 1)
  // For now, only use 12-bit resolution.
  // Don't use any low-power modes for now, but they look
  // interesting - TODO: investigate.
  #ifdef VVC_F0
    // Initialize the core ADC settings.
    adc_init_struct.Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV4;
    adc_init_struct.Resolution = LL_ADC_RESOLUTION_12B;
    adc_init_struct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    adc_init_struct.LowPowerMode = LL_ADC_LP_MODE_NONE;
    // (TODO: Check that 'SUCCESS' is returned)
    LL_ADC_Init(ADC1, &adc_init_struct);
    // Set the ADC group regular sequencer.
    LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_1);
    // Set the ADC channel sampling time.
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);
    // Enable the ADC.
    LL_ADC_Enable(ADC1);
  #elif  VVC_F3
    // Initialize the core ADC settings.
    // On the F303, use the PCLK synchronously.
    LL_ADC_SetCommonClock(ADC12_COMMON, LL_ADC_CLOCK_SYNC_PCLK_DIV1);
    adc_init_struct.Resolution = LL_ADC_RESOLUTION_12B;
    adc_init_struct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    adc_init_struct.LowPowerMode = LL_ADC_LP_MODE_NONE;
    // (TODO: Check that 'SUCCESS' is returned)
    LL_ADC_Init(ADC1, &adc_init_struct);
    // Set the ADC group regular sequencer.
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_2);
    // Set the ADC channel sampling time.
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_2, LL_ADC_SAMPLINGTIME_19CYCLES_5);
    // Enable the ADC.
    LL_ADC_Enable(ADC1);
  #endif

  // Setup hardware interrupts on the EXTI lines associated
  // with the 6 button inputs.
  // Pins A2, A3 use the EXTI2_3 interrupt.
  // Pins A4, A5, A6, and A7 use the EXTI4_15 interrupt.
  // Map EXTI lines to the GPIOA port.
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,
                          LL_SYSCFG_EXTI_LINE2);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,
                          LL_SYSCFG_EXTI_LINE3);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,
                          LL_SYSCFG_EXTI_LINE4);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,
                          LL_SYSCFG_EXTI_LINE5);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,
                          LL_SYSCFG_EXTI_LINE6);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,
                          LL_SYSCFG_EXTI_LINE7);
  exti_init_struct.Line_0_31 = (LL_EXTI_LINE_2 |
                                LL_EXTI_LINE_3 |
                                LL_EXTI_LINE_4 |
                                LL_EXTI_LINE_5 |
                                LL_EXTI_LINE_6 |
                                LL_EXTI_LINE_7);
  exti_init_struct.LineCommand = ENABLE;
  exti_init_struct.Mode = LL_EXTI_MODE_IT;
  exti_init_struct.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&exti_init_struct);

  // The HAL 'cortex' libraries basically just call these
  // core functions for NVIC stuff, anyways:
  #ifdef VVC_F0
    NVIC_SetPriority(EXTI2_3_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI2_3_IRQn);
    NVIC_SetPriority(EXTI4_15_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI4_15_IRQn);
  #elif VVC_F3
    // On Cortex-M4 cores, we need to set an NVIC priority
    // grouping and subpriorities as well as normal priorities:
    // 0x07: 0 Pri / 4 SubPri
    // 0x06: 1 Pri / 3 SubPri
    // 0x05: 2 Pri / 2 SubPri
    // 0x04: 3 Pri / 1 SubPri
    // 0x03: 4 Pri / 0 SubPri
    // Use 2 bits for 'priority' and 2 bits for 'subpriority'.
    NVIC_SetPriorityGrouping(0x05);
    uint32_t exti_pri_encoding = NVIC_EncodePriority(0x05, 0x03, 0x03);
    NVIC_SetPriority(EXTI2_TSC_IRQn, exti_pri_encoding);
    NVIC_EnableIRQ(EXTI2_TSC_IRQn);
    NVIC_SetPriority(EXTI3_IRQn, exti_pri_encoding);
    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_SetPriority(EXTI4_IRQn, exti_pri_encoding);
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_SetPriority(EXTI9_5_IRQn, exti_pri_encoding);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
  #endif

  // De-initialize the TIM2 timer peripheral, and then
  // re-initialize it for periodically reading from the ADC.
  // (Use TIM2 beacuse it is simple & available on most chips.)
  // TODO: Should I start breaking out functions for
  // peripheral startup?
  #ifdef VVC_F0
    // First, ensure the timer is off.
    LL_TIM_DeInit(TIM2);
    // (TODO)
  #elif  VVC_F3
    // First, ensure the timer is off.
    LL_TIM_DeInit(TIM2);
    // For now, set a prescaler value of 1024 = 0x400.
    // If the PLL is 48MHz, this should be 46.875KHz.
    // (TODO: up the clock to 72MHz and standardize)
    timer_init_struct.Prescaler = 0x0400;
    // Set the timer to count upwards.
    timer_init_struct.CounterMode = LL_TIM_COUNTERMODE_UP;
    // Set an auto-reload value of the timer 'period'.
    // So...I think that means that to tick every second,
    // we should set an auto-reload of...46875? = 0xB71B
    // (But hex is not human-readable.)
    //timer_init_struct.Autoreload = 46875;
    // Okay, with the interrupt working we don't want
    // every second to blink an LED. We want ~CD quality audio.
    // (This is way too fast to visualize on the OLED.
    //  But that's promising for future FFT'ing!)
    //timer_init_struct.Autoreload = 1;
    // (2048 seems like a good value to draw a time-domain graph)
    timer_init_struct.Autoreload = 2048;
    // Set clock division to trigger on every event.
    timer_init_struct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    // Set the repetition counter to 0; unused.
    timer_init_struct.RepetitionCounter = 0x00;
    // Initialize the peripheral.
    LL_TIM_Init(TIM2, &timer_init_struct);
    // Next, enable the 'Update' timer interrupt.
    LL_TIM_EnableIT_UPDATE(TIM2);
    // ...And do the same for the timer's NVIC channel.
    // (Use the same interrupt priorities as an EXTI line for now)
    NVIC_SetPriority(TIM2_IRQn, exti_pri_encoding);
    NVIC_EnableIRQ(TIM2_IRQn);
    // Then finally, enable the timer.
    LL_TIM_EnableCounter(TIM2);
  #endif

  while (1) {
    //draw_test_menu();
    draw_mic_readout();
    // Communicate the framebuffer to the OLED screen.
    i2c_display_framebuffer(I2C1_BASE, &oled_fb);

    // Set the onboard LED.
    if (uled_state) {
      GPIOA->ODR |= LL_GPIO_PIN_12;
    }
    else {
      GPIOA->ODR &= ~LL_GPIO_PIN_12;
    }

    // Play a tone on the buzzer if applicable.
    if (buzzer_state) {
      // This probably is not actually an accurate conversion
      // to Hertz. But it's a 48MHz clock so...
      buzzer_tone = 48000000 / buzzer_tone_hz;
      // Play for about 1/8-second. So:
      // X pulses * Y cycles = 6000000
      buzzer_pulses = 6000000 / buzzer_tone;
      pulse_out_pin(&GPIOB->ODR,
                    LL_GPIO_PIN_0,
                    buzzer_tone,
                    buzzer_pulses);
      buzzer_state = 0;
    }
  }
  return 0;
}
