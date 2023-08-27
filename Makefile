PROJECT := Linked_List$(MajV)$(MinV)$(BugFV)
MAKEFILE_VER := 1.00.09

MajV := 01
MinV := 00
BugFV := 00

COMPILER := gcc
LANG := c17

PROC :=	prepocessor
COMP :=	compile
COMPL := compilation
ASM := assembler
OUT := testOut

SOURCE := main.c
SOURCE += 

HEADER := dcm_dsp.h
HEADER += 


OBJECT_FILES := $(patsubst %.c,$(OUT)/%.o,$(SOURCE))

.PHONY: $(COMP) 
$(COMP): clean makedirout $(COMPL) EXE final

.PHONY: final
final:
	echo [off]
	echo  ["Compile is successfull!"]

.PHONY: makedirout
makedirout:

	mkdir $(OUT)

.PHONY: $(COMPL)
$(COMPL): $(SOURCE)
	$(foreach src,$(SOURCE),$(COMPILER) -std=$(LANG) -pedantic-errors -g -Wall -Wextra -Wconversion -Wsign-conversion -c $(src) -o $(patsubst %.c,$(OUT)/%.o,$(src)) && echo "Compiled $(src) to $(patsubst %.c,$(OUT)/%.o,$(src))";)

.PHONY: EXE
EXE: $(OBJECT_FILES)
	$(COMPILER) -std=$(LANG) -pedantic-errors -g -Wall -Wextra -Wconversion -Wsign-conversion -Werror -o $(OUT)/$(COMP).exe $^

clean:
	rm -rf $(OUT) $(OUT)/*.exe $(OUT)/*.elf $(OUT)/*.o $(OUT)/*.i $(OUT)/*.s $(OUT)/*.hex