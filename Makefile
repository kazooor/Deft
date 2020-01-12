ARCH        	:= i386
CC 		:= i686-linux-gnu-gcc-8
AS 		:= i686-linux-gnu-as
CCFLAGS 	:= -g -ffreestanding -Wall -Wextra -Werror -Isrc -Isrc/libc -lgcc -nostartfiles -fno-pie
LDFLAGS 	:= -g -ffreestanding -nostdlib -nostartfiles

BUILD_DIR 	:= build
SRC_DIR 	:= src

SOURCES     	:= $(shell find $(SRC_DIR) -type f -name "*.c")
OS.BIN      	:= $(BUILD_DIR)/os.bin

BOOT.S      	:= $(SRC_DIR)/boot.s
LINKER.LD   	:= $(SRC_DIR)/linker.ld
OBJS        	:= $(addprefix $(BUILD_DIR)/,$(SOURCES:.c=.c.o) $(BOOT.S:.s=.s.o))

QEMU        	:= qemu-system-$(ARCH)
QEMU_FLAGS  	:= -serial stdio

all: | all build link run clean

build: link

link: $(LINKER.LD) $(OBJS)
	$(CC) -Wl,-T$(LINKER.LD) -o $(OS.BIN) $(LDFLAGS) $(OBJS)

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CCFLAGS)

run: link
	$(QEMU) -kernel $(OS.BIN) $(QEMU_FLAGS)

clean:
	-rm -rf $(BUILD_DIR)
