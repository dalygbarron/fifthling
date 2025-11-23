V=1
SOURCE_DIR=src
BUILD_DIR=build
FILE_DIR=filesystem
N64_ROM_REGIONFREE=true
N64_ROM_SAVETYPE=eeprom4k
N64_TOOLS=$(N64_INST)/bin
include $(N64_INST)/include/n64.mk

all: main.z64
.PHONY: all

SRC = $(wildcard src/*.c)
OBJS = $(addprefix $(BUILD_DIR)/,$(patsubst src/%.c,%.o,$(SRC)))

assets_font = $(addprefix fonts/,$(notdir $(wildcard assets/fonts/*.ttf)))
assets_i_png = $(addprefix pics/,$(notdir $(wildcard assets/pics/*.i.png)))
assets_png = $(filter-out $(assets_i_png),$(addprefix pics/,$(notdir $(wildcard assets/pics/*.png))))
assets_xm = $(addprefix music/,$(notdir $(wildcard assets/music/*.xm)))
assets_model = $(addprefix models/,$(notdir $(wildcard assets/models/*.glb)))
assets_conv = $(addprefix $(FILE_DIR)/,$(assets_png:.png=.sprite)\
									 $(assets_font:%.ttf=%.font64)\
									 $(assets_xm:%.xm=%.xm64)\
									 $(assets_model:%.glb=%.model64)\
						             $(assets_i_png:.i.png=.i.sprite))

main.z64: N64_ROM_TITLE="Fifthling"
main.z64: $(BUILD_DIR)/main.dfs

$(BUILD_DIR)/main.dfs: $(assets_conv)
$(BUILD_DIR)/main.elf: $(OBJS)

AUDIOCONV_FLAGS ?=

$(FILE_DIR)/music/%.xm64: assets/music/%.xm
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(FILE_DIR)/music "$<"

$(FILE_DIR)/pics/%.i.sprite: assets/pics/%.i.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE_I] $@"
	@$(N64_TOOLS)/mksprite -f CI8 $<
	@mv $(patsubst %.png, %.sprite, $(notdir $<)) $@

$(FILE_DIR)/pics/%.sprite: assets/pics/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_TOOLS)/mksprite -f RGBA16 -o $(FILE_DIR)/pics $<

$(FILE_DIR)/fonts/%.font64: assets/fonts/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_TOOLS)/mkfont -o $(FILE_DIR)/fonts -s 14 $<

editor:
	$(MAKE) -C editor all

all: main.z64 tools

clean:
	rm -rf $(BUILD_DIR) $(FILE_DIR) main.z64
	$(MAKE) -C tools/editor clean
	
.PHONY: clean tools all

-include $(wildcard $(BUILD_DIR)/*.d)
