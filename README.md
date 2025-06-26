# 📘 Stm32f103vct6_course

This repository provides a collection of **bare-metal firmware examples** for the STM32F103VCT6 microcontroller, focusing on **direct register-level programming** (no HAL, no CMSIS, no SPL). It's structured as a hands-on course to help understand how STM32 peripherals work internally.

---

## 🧩 Covered Topics

- ✅ GPIO Input/Output via `GPIOx->CRL/CRH/ODR/IDR`
- ✅ UART initialization and communication via `USARTx` registers
- ✅ EXTI (external interrupt) using `AFIO`, `EXTI`, and `NVIC`
- ✅ Timer and PWM configuration with `TIMx` registers
- ✅ ADC conversion with direct setup
- ✅ Delay using SysTick (`SysTick->LOAD/VAL/CTRL`)
- ✅ NVIC setup and interrupt priorities

All code avoids abstraction layers and accesses hardware registers directly.

---

## ⚙️ Toolchain

- 💻 **IDE**: STM32CubeIDE or Keil uVision (can be used for debugging and flashing)
- 🛠 **Compiler**: `arm-none-eabi-gcc` (if using Makefile)
- 🔧 **Startup & Linker**: You can use default CMSIS startup or write your own for learning
- 📍 **Target MCU**: STM32F103VCT6 (Cortex-M3, 256 KB Flash)

---

## 📦 Project Structure

