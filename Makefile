INC_DIRS := Core/Drivers Core/Inc
TARGET := firmware
LINKER := stm32f4.ld
BUILD_DIR := build
OPT := -Os
CPU := cortex-m4
SRC_DIR = ./Src


SRCS := $(shell find ${SRC_DIR} -name '*.cpp' -or -name '*.c')
OBJS := $(addsuffix .o, $(basename $(SRCS)))
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))
LINKER := $(addprefix -T ,$(LINKER))

PREFIX := arm-none-eabi
CC := $(PREFIX)-gcc
CXX := $(PREFIX)-g++
OBJCOPY := $(PREFIX)-objcopy
OBJDUMP := $(PREFIX)-objdump
SIZE := $(PREFIX)-size

INC_DIRS := $(addprefix -I , $(INC_DIRS))
CFLAGS := -nostdlib $(OPT) -mcpu=$(CPU) $(INC_DIRS) -fno-exceptions -ffunction-sections -fdata-sections
CXXFLAGS := -nostdlib $(OPT) -mcpu=$(CPU) $(INC_DIRS) -fno-exceptions -ffunction-sections -fdata-sections
LDFLAGS := $(LINKER) -Wl,-Map=$(TARGET).map -lc


all:bin size
size: $(BUILD_DIR)/$(TARGET).size
bin: $(BUILD_DIR)/$(TARGET).bin

%.size: %.elf
	$(SIZE) $<

$(BUILD_DIR)/$(TARGET).bin:$(BUILD_DIR)/$(TARGET).elf
	@echo "Generating Bin"
	@$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(TARGET).elf:$(OBJS)
	@echo "Running elf"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(dir $@)
	@echo "Running src C++"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	@echo "Running src C"
	@$(CC) -c $(CFLAGS) -o $@ $<

flash:bin
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

debug: CXXFLAGS += -g
debug: all

git:clean
	git add -A
	git commit 
	git push origin master

clean:
	rm -rf build

