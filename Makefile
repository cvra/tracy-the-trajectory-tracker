
PROJNAME = beacons
Q = @
COLOR = \033[1;31m
COLOR_CLEAR = \033[0m
PRINT = @printf "$(COLOR)%s$(COLOR_CLEAR)\n"



CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
AS  = arm-none-eabi-gcc -x assembler-with-cpp
LD = arm-none-eabi-g++
AR = arm-none-eabi-ar
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump
NM = arm-none-eabi-nm
SZ = arm-none-eabi-size



INCDIR += -I./dependencies/CMSIS/include
INCDIR += -I./dependencies/libopencm3/include
INCDIR += -I./dependencies/uCOS-III/Source
INCDIR += -I./dependencies/uCOS-III/Port
INCDIR += -I./dependencies/uCOS-III/Cfg

# C compiler flags
CFLAGS = -Wall -Werror -Os
CFLAGS += -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS += -MD -DSTM32F3 -DCPU_CFG_CPU_CORE_FREQ=64000000 -g
CFLAGS += $(INCDIR)

ASMFLAGS = $(CFLAGS)

CPPFLAGS += $(CFLAGS)



# Linker flags
LDFLAGS = -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS += -Wl,--gc-sections -nostartfiles
LDFLAGS += -Tlinkerscript.ld
LDFLAGS += -lc -lnosys
LDFLAGS	+= -L./libopencm3/lib
LDFLAGS	+= -L./CMSIS/lib/
LDFLAGS	+= -lopencm3_stm32f3
#LDFLAGS	+= -larm_cortexM4lf_math



CFLAGS += -I dependencies/


# C source files
CSRC = 

CSRC += ./src/trajectory_tracking.c






OBJS = $(CSRC:.c=.o) $(ASMSRC:.s=.o) $(CXXSRC:.cpp=.o)


all: $(PROJNAME).elf $(PROJNAME).bin $(PROJNAME).hex $(PROJNAME).lst $(PROJNAME).size.txt
	$(Q) $(SZ) $(PROJNAME).elf

$(PROJNAME).elf: $(OBJS)
	$(PRINT) "> linking"
	$(Q) $(LD) -o $(PROJNAME).elf $(OBJS) $(LDFLAGS)



%.o: %.c Makefile
	$(PRINT) "> compiling $<"
	$(Q) $(CC) $(CFLAGS) -c ${<} -o ${@}

%.o: %.s Makefile
	$(PRINT) "> assembling $<"
	$(Q) $(AS) $(ASMFLAGS) -c ${<} -o ${@}

%.o: %.cpp Makefile
	$(PRINT) "> compiling $<"
	$(Q) $(CPP) $(CPPFLAGS) -c ${<} -o ${@}

-include $(OBJS:.o=.d)



clean:
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)
	rm -f $(PROJNAME).elf $(PROJNAME).bin $(PROJNAME).hex $(PROJNAME).size.txt $(PROJNAME).lst



# binary file
$(PROJNAME).bin: $(PROJNAME).elf
	$(Q) $(OC) -O binary -j .text -j .rodata -j .data $(PROJNAME).elf $(PROJNAME).bin

$(PROJNAME).hex: $(PROJNAME).elf
	$(Q) $(OC) -O ihex $(PROJNAME).elf $(PROJNAME).hex

# assembly listing
$(PROJNAME).lst: $(PROJNAME).elf
	$(PRINT) "> generating assembly listing"
	$(Q) $(OD) -D -h $(PROJNAME).elf > $(PROJNAME).lst

# space usage
$(PROJNAME).size.txt: $(PROJNAME).elf
	$(PRINT) "> calculating space usage"
	$(Q) $(SZ) $(PROJNAME).elf > $(PROJNAME).size.txt
	$(Q) $(NM) --numeric-sort --print-size -S $(PROJNAME).elf >> $(PROJNAME).size.txt

rebuild: clean all

