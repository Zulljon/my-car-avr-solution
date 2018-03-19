#	Compile project in Linux. (This is only modify of Atmel Studio 6.2 Makefile) 
#	Usage:
#		$ cd $(path/to/folder)/Device_1/Device_1_s/$(PROJ_NAME)/Debug
#		$ make -f Makefile_492l.mak clean all

RM=rm -fr

#AVR_TOOLCHAIN=$(HOME)/Programs/avr8-gnu-toolchain-linux_x86_64/bin/

CC=$(AVR_TOOLCHAIN)avr-gcc
OBJCOPY=$(AVR_TOOLCHAIN)avr-objcopy
OBJDUMP=$(AVR_TOOLCHAIN)avr-objdump
SIZE=$(AVR_TOOLCHAIN)avr-size
NM=$(AVR_TOOLCHAIN)avr-nm
AVRDUDE=avrdude
MV=mv -f

TARGET=atmega328p
PROJ_NAME=Rx

CCV=`$(CC) --version | grep gcc`
DEFINE=

OPTIMIZATION= -Os

USER_OBJS =

LIBS=
PROJ=

O_SRCS=
C_SRCS=
S_SRCS=
S_UPPER_SRCS=
OBJ_SRCS=
ASM_SRCS=
PREPROCESSING_SRCS=
OBJS=
OBJS_AS_ARGS=
C_DEPS=
C_DEPS_AS_ARGS=
EXECUTABLES=
OUTPUT_FILE_PATH =
OUTPUT_FILE_PATH_AS_ARGS =
AVR_APP_PATH =$$$AVR_APP_PATH$$$
QUOTE="
ADDITIONAL_DEPENDENCIES=
OUTPUT_FILE_DEP=
LIB_DEP=
LINKER_SCRIPT_DEP=

# Every subdirectory with source files must be described here
SUBDIRS=  \
../


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS+=  \
../FSM_EEPROM.c \
../Rx.c \
../uart_function.c \


PREPROCESSING_SRCS+= 


ASM_SRCS+=


OBJS+= \
FSM_EEPROM.o \
Rx.o \
uart_function.o \

OBJS_AS_ARGS+=  \
FSM_EEPROM.o \
Rx.o \
uart_function.o \

C_DEPS+=  \
FSM_EEPROM.d \
Rx.d \
uart_function.d \

C_DEPS_AS_ARGS+= \
FSM_EEPROM.d \
Rx.d \
uart_function.d \

OUTPUT_FILE_PATH+=$(PROJ_NAME).elf

OUTPUT_FILE_PATH_AS_ARGS+=$(PROJ_NAME).elf

ADDITIONAL_DEPENDENCIES=

OUTPUT_FILE_DEP=./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 





%.o: ../%.c
	@echo "Building file: "$<
	@echo "Invoking C Compiler: $(CCV)"
	$(CC) -x c -funsigned-char -funsigned-bitfields $(DEFINE) $(OPTIMIZATION) -ffunction-sections -fdiagnostics-color=always -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=$(TARGET) -c -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o)   -o $@ $< 
	@echo "Finished building: "$<
	


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo "Building target: "$@
	@echo "Invoking: C Compiler $(CCV)"
	$(CC) -fdiagnostics-color=always -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map=$(PROJ_NAME).map -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=$(TARGET)  
	@echo "Finished building target: "$@
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex $(PROJ_NAME).elf $(PROJ_NAME).eep || exit 0
	$(OBJDUMP) -h -S $(PROJ_NAME).elf > $(PROJ_NAME).lss
	$(OBJCOPY) -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures $(PROJ_NAME).elf $(PROJ_NAME).srec
	$(SIZE) $(PROJ_NAME).elf
	
	

# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	-$(RM) $(PROJ_NAME).elf $(PROJ_NAME).a $(PROJ_NAME).hex $(PROJ_NAME).lss $(PROJ_NAME).eep $(PROJ_NAME).map $(PROJ_NAME).srec $(PROJ_NAME).usersignatures
