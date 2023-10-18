PROJECT := Linked_List$(MajV)$(MinV)$(BugFV)
MAKEFILE_VER := 1.00.09

MajV := 01
MinV := 00
BugFV := 00

COMPILER := gcc
LANG := c17

PROC := prepocessor
COMP := compile
COMPL := compilation
ASM := assembler
OUT := testOut

SOURCE := main.c
SOURCE += tara.c

HEADER := tara.h
HEADER += tara_cfg.h

OBJECT_FILES := $(patsubst %.c,$(OUT)/%.o,$(SOURCE))

.PHONY: $(COMP)
$(COMP): clean makedirout $(COMPL) EXE final

.PHONY: final
final:
	@echo "[off]"
	@echo "[\"Compile is successful!\"]"

.PHONY: makedirout
makedirout:
	mkdir -p $(OUT)

.PHONY: $(COMPL)
$(COMPL): $(OBJECT_FILES)

$(OUT)/%.o: %.c $(HEADER)
	$(COMPILER) -std=$(LANG) -pedantic-errors -g -Wall -Wextra -Wconversion -Wsign-conversion -c $< -o $@
	@echo "Compiled $< to $@"

.PHONY: EXE
EXE: $(OUT)/$(COMP).exe

$(OUT)/$(COMP).exe: $(OBJECT_FILES)
	$(COMPILER) -std=$(LANG) -pedantic-errors -g -Wall -Wextra -Wconversion -Wsign-conversion -Werror -o $@ $^

.PHONY: run
run: EXE
	./$(OUT)/$(COMP).exe

.PHONY: clean
clean:
	rm -rf $(OUT)
