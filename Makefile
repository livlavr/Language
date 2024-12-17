CXX           = gcc-14

SRC           = main.cpp ____
SUBMODULE_SRC =
B_SUBMODULES  = Color-printf/color_printf.cpp Stack/src/recalloc.cpp Stack/src/stack_public.cpp \
				Stack/src/stack_security.cpp Stack/src/stack.cpp Stack/src/stack_dump.cpp

BUILD_DIR     = ./build/
SRC_DIR       = ./src/
CFLAGS        = ____
B_CFLAGS      = -I inc -I Custom-asserts -I Color-printf -I Binary-tree/inc -I Debug-macros -I Stack/inc

TARGET        = ____
OBJECT        = $(patsubst %.cpp, %.o, $(SRC))
BUILD_OBJ     = $(addprefix $(BUILD_DIR), $(OBJECT))

GREEN_COLOR    = \033[1;32m
YELLOW_COLOR   = \033[1;33m
DEFAULT_COLOR  = \033[0m

DED_FLAGS     = -D _DEBUG -ggdb2 -std=c++17 -O0 -Wall -Wextra -Weffc++                                     \
			    -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations                     \
				-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported                      \
				-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral           \
				-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor \
				-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls \
				-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2        \
				-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types                \
				-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef                     \
				-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros                              \
				-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing                        \
				-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation       \
				-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer        \
				-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla

vpath %.o   $(BUILD_DIR)
vpath %.cpp $(SRC_DIR)

.PHONY : clean all

all : $(addprefix $(SRC_DIR), $(SRC))
	clear
	@mkdir -p build
	$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(TARGET))
	@printf "$(GREEN_COLOR)$(TARGET) COMPILED$(DEFAULT_COLOR)\n"

run : $(addprefix $(SRC_DIR), $(SRC))
	clear
	@mkdir -p build
	$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(TARGET))
	@printf "$(GREEN_COLOR)$(TARGET) COMPILED$(DEFAULT_COLOR)\n"
	$(addprefix $(BUILD_DIR), $(TARGET))

clean :
	@rm -f -r $(addprefix $(BUILD_DIR), *.o) *.dSYM
	@printf  "$(YELLOW_COLOR)$(TARGET) CLEANED$(DEFAULT_COLOR)\n"

doxygen :
	doxygen
