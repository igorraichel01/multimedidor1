######################################
# Makefile for MulticronometroUsb
# Target: STM32F401CCUx (Cortex-M4, 256 KB Flash, 64 KB RAM)
# Toolchain: arm-none-eabi-gcc
# Use with STM32CubeIDE (Makefile project) or from the command line
######################################

######################################
# Build target
######################################
TARGET = MulticronometroUsb

######################################
# Build output directory (Debug or Release)
######################################
BUILD_DIR ?= Debug

######################################
# Source files
######################################

# Plain C sources (compiled with arm-none-eabi-gcc)
C_SOURCES = \
Core/Src/stm32f4xx_it.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/system_stm32f4xx.c \
Core/Src/syscalls.c \
Core/Src/sysmem.c \
FATFS/App/fatfs.c \
FATFS/Target/usbh_diskio.c \
USB_HOST/App/usb_host.c \
USB_HOST/Target/usbh_conf.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Middlewares/Third_Party/FatFs/src/diskio.c \
Middlewares/Third_Party/FatFs/src/ff.c \
Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
Middlewares/Third_Party/FatFs/src/option/syscall.c \
Middlewares/Third_Party/FatFs/src/option/ccsbcs.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c \
Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c \
Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.c \
Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.c

# C sources that must be compiled as C++ (they use C++ class headers)
# Compiled with arm-none-eabi-g++ -x c++
C_AS_CXX_SOURCES = \
Core/Src/main.c \
Source/File_Handling.c \
Source/cidepe/LCD.c \
Source/cidepe/KBD2.c \
Source/cidepe/Fluxo.c \
Source/cidepe/Modo0.c

# C++ sources (compiled with arm-none-eabi-g++)
CXX_SOURCES = \
Source/Application.cpp \
Source/Hds/HdsDma.cpp \
Source/Hds/HdsGpio.cpp \
Source/Hds/HdsIFlash.cpp \
Source/Hds/HdsMux.cpp \
Source/Hds/Hdsteclado.cpp \
Source/Hds/hdsLcd.cpp \
Source/Mdl/MdlCalib.cpp \
Source/Mdl/MdlEnsaio.cpp \
Source/Mdl/MdlEnsaioAnalogico.cpp \
Source/Mdl/MdlLcd.cpp \
Source/Mdl/MdlSaveDigital.cpp \
Source/Mdl/MdlSensor.cpp \
Source/Mdl/MdlSensorAnalog.cpp \
Source/Mdl/MdlTimeEvents.cpp \
Source/Mdl/MdlUtil.cpp \
Source/cidepe/MdlMSG.cpp \
Source/cidepe/MdlEnsaioDigital.cpp

# ASM sources
ASM_SOURCES = \
Core/Startup/startup_stm32f401xc.s

######################################
# Toolchain
######################################
PREFIX = arm-none-eabi-
CC  = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS  = $(PREFIX)gcc -x assembler-with-cpp
CP  = $(PREFIX)objcopy
SZ  = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

######################################
# CPU / FPU flags
######################################
CPU     = -mcpu=cortex-m4
FPU     = -mfpu=fpv4-sp-d16
FLOAT   = -mfloat-abi=hard
MCU     = $(CPU) -mthumb $(FPU) $(FLOAT)

######################################
# Preprocessor defines
######################################
C_DEFS = \
-DUSE_HAL_DRIVER \
-DSTM32F401xC

# Debug build: add DEBUG define, no optimisation
ifeq ($(BUILD_DIR),Debug)
  OPT   = -Og
  C_DEFS += -DDEBUG
  DEBUG = -g3
else
  OPT   = -Os
  DEBUG =
endif

######################################
# Include paths
######################################
C_INCLUDES = \
-ICore/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-ISource \
-ISource/Includes \
-ISource/cidepe \
-IFATFS/Target \
-IFATFS/App \
-IUSB_HOST/App \
-IUSB_HOST/Target \
-IMiddlewares/Third_Party/FatFs/src \
-IMiddlewares/ST/STM32_USB_Host_Library/Core/Inc \
-IMiddlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc

######################################
# Compiler flags
######################################
ASFLAGS  = $(MCU) $(DEBUG) $(C_DEFS) $(C_INCLUDES) -Wall -fdata-sections -ffunction-sections
CFLAGS   = $(MCU) $(OPT) $(DEBUG) $(C_DEFS) $(C_INCLUDES) \
           -Wall -fdata-sections -ffunction-sections -fstack-usage --specs=nano.specs
CXXFLAGS = $(MCU) $(OPT) $(DEBUG) $(C_DEFS) $(C_INCLUDES) \
           -Wall -fdata-sections -ffunction-sections -fstack-usage --specs=nano.specs \
           -fno-exceptions -fno-rtti -std=gnu++14

######################################
# Linker flags
######################################
LDSCRIPT = STM32F401CCUx_FLASH.ld
LIBS     = -lc -lm -lnosys
LIBDIR   =
LDFLAGS  = $(MCU) --specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) \
           -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

######################################
# Build rules
######################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# Object lists
OBJECTS  = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_AS_CXX_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))

vpath %.c   $(sort $(dir $(C_SOURCES))) $(sort $(dir $(C_AS_CXX_SOURCES)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))
vpath %.s   $(sort $(dir $(ASM_SOURCES)))

# C objects (compiled as C)
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# C objects compiled as C++ (override the plain C rule for specific files)
$(BUILD_DIR)/main.o: Core/Src/main.c Makefile | $(BUILD_DIR)
	$(CXX) -c -x c++ $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/File_Handling.o: Source/File_Handling.c Makefile | $(BUILD_DIR)
	$(CXX) -c -x c++ $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/LCD.o: Source/cidepe/LCD.c Makefile | $(BUILD_DIR)
	$(CXX) -c -x c++ $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/KBD2.o: Source/cidepe/KBD2.c Makefile | $(BUILD_DIR)
	$(CXX) -c -x c++ $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/Fluxo.o: Source/cidepe/Fluxo.c Makefile | $(BUILD_DIR)
	$(CXX) -c -x c++ $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/Modo0.o: Source/cidepe/Modo0.c Makefile | $(BUILD_DIR)
	$(CXX) -c -x c++ $(CXXFLAGS) $< -o $@

# C++ objects
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

# ASM objects
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

# Link
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

# Hex / Bin
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir -p $@

######################################
# Clean
######################################
clean:
	-rm -fR $(BUILD_DIR)

.PHONY: all clean
