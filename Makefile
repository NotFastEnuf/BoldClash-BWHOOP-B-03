ifdef USE_GCC
	CC	= arm-none-eabi-gcc
	CXX 	= arm-none-eabi-g++
	ASM 	= arm-none-eabi-as
	LD 		= arm-none-eabi-gcc
	OBJCOPY = arm-none-eabi-objcopy
	SIZE    = arm-none-eabi-size
else
	CC 		= armcc --c99
	CXX 	= armcc  --cpp
	ASM 	= armasm
	LD 	= armlink
	OBJCOPY = fromelf
endif

SDIR = .
SRC_C = $(wildcard $(SDIR)/Silverware/src/*.c) \
		$(wildcard $(SDIR)/Utilities/*.c) \
		$(wildcard $(SDIR)/Libraries/STM32F0xx_StdPeriph_Driver/src/*.c)
SRC_CXX = $(wildcard $(SDIR)/Silverware/src/*.cpp)

ifdef USE_GCC
SRC_C += $(wildcard $(SDIR)/gcc/*.c)
SRC_S += $(SDIR)/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc_ride7/startup_stm32f030.s
SRC_S += $(SDIR)/gcc/qfplib/qfplib.s
LDFLAGS := -Wl,-wrap,__aeabi_dmul \
	   -Wl,-wrap,__aeabi_fadd \
	   -Wl,-wrap,__aeabi_fdiv \
	   -Wl,-wrap,__aeabi_fmul \
	   -Wl,-wrap,__aeabi_fsub \
	   -Wl,-wrap,__aeabi_i2f  \
	   -Wl,-wrap,__aeabi_ui2f \
	   -Wl,-wrap,__aeabi_f2iz \
	   -Wl,-wrap,__aeabi_f2uiz \
	   -Wl,-wrap,__aeabi_fcmpeq \
	   -Wl,-wrap,__aeabi_fcmplt \
	   -Wl,-wrap,__aeabi_fcmple \
	   -Wl,-wrap,__aeabi_fcmpge \
	   -Wl,-wrap,__aeabi_fcmpgt \
	   -Wl,-wrap,__aeabi_fcmpun
else
SRC_S += $(SDIR)/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/arm/startup_stm32f031.s
endif

INCLUDES = -I$(SDIR)/Silverware/src -I$(SDIR)/Libraries/CMSIS/Device/ST/STM32F0xx/Include -I $(SDIR)/Libraries/CMSIS/Include -I $(SDIR)/Utilities -I $(SDIR)/Libraries/STM32F0xx_StdPeriph_Driver/inc

CPU = cortex-m0

SRCS     = $(SRC_C) $(SRC_CXX) $(SRC_S)
ODIR     = $(SDIR)/obj

OBJS 	 = $(addprefix $(ODIR)/, $(notdir $(SRC_C:.c=.o) $(SRC_S:.s=.o) $(SRC_CXX:.cpp=.o)))
VPATH 	 = $(dir $(SRCS))

ifndef USE_GCC
export ARM_TOOL_VARIANT = mdk_lite
export ARMCC5_ASMOPT = --diag_suppress=9931
export ARMCC5_CCOPT = --diag_suppress=9931
export ARMCC5_LINKOPT = --diag_suppress=9931
export CPU_TYPE = STM32F030F4
export CPU_VENDOR = STMicroelectronics
export CPU_CLOCK = 0x00B71B00
export UV2_TARGET = BWhoop
endif


ifndef USE_GCC
CFLAGS   := --cpu $(CPU) $(INCLUDES) -D__EVAL -D__MICROLIB -g -O2 --apcs=interwork --split_sections -D__UVISION_VERSION="524" -DUSE_STDPERIPH_DRIVER -DSTM32F031 --fpmode=fast
ASMFLAGS := --cpu $(CPU) --pd "__EVAL SETA 1" -g --apcs=interwork --pd "__MICROLIB SETA 1" --pd "__UVISION_VERSION SETA 524" --xref
LDFLAGS  := --cpu $(CPU) --library_type=microlib --ro-base 0x08000000 --entry 0x08000000 --rw-base 0x20000000 --entry Reset_Handler --first __Vectors --strict --info summarysizes
DEPENDS  := --depend=
else
CFLAGS   := -mcpu=$(CPU) $(INCLUDES) -DDISABLE_GESTURES2 -Os -g -mthumb -fdata-sections -ffunction-sections \
            -fsingle-precision-constant -ffast-math \
            -nostartfiles --specs=nano.specs --specs=nosys.specs
CFLAGS   += -DUSE_STDPERIPH_DRIVER -DSTM32F031
LDFLAGS  += $(CFLAGS) -Wl,-T,flash.ld,-Map,output.map,--gc-sections -L$(SDIR)/gcc
ASMFLAGS := -mcpu=$(CPU)
DEPENDS  := -MD -MP -MF 
endif

.PHONY: default all
default: silverware.hex

$(VERBOSE).SILENT:

$(OBJS): | $(ODIR)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o: %.cpp
	@echo " + Compiling '$(notdir $<)'"
	$(CXX) $(CFLAGS) $(DEPENDS)$(@:.o=.dep) -c -o $@ $<

$(ODIR)/%.o: %.c
	@echo " + Compiling '$(notdir $<)'"
	$(CC) $(CFLAGS) $(DEPENDS)$(@:.o=.dep) -c -o $@ $<

$(ODIR)/%.o: %.s
	@echo " + Compiling '$(notdir $<')"
	$(ASM) $(ASMFLAGS) -o $@ $<

silverware.hex: silverware.axf
ifdef USE_GCC
	$(OBJCOPY) -O ihex $< $@
else
	fromelf $< --i32combined --output $@
endif

silverware.axf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
ifdef USE_GCC
	$(SIZE) $@
endif

clean:
	rm -Rf $(ODIR) silverware.axf silverware.hex

-include $(OBJS:.o=.dep)
