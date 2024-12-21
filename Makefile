CXX           = gcc-14

FRONT_SRC     = main.cpp Tokenization.cpp Ast.cpp RecursiveDescent.cpp
SUBMODULE_SRC = Color-printf/color_printf.cpp

FRONT_DIR     = ./Frontend
BUILD_DIR     = /build/
SRC_DIR       = /src/
INC_DIR       = /inc/
LIBS_DIR      = ./libs/

CFLAGS        = -I libs/Custom-asserts -I libs/Color-printf -I libs/Binary-tree/inc -I libs/Debug-macros -I libs/Buffer -I Frontend/inc

FRONTEND      = frontend
OBJECT        = $(patsubst %.cpp, %.o, $(SRC))

GREEN_COLOR   = \033[1;32m
YELLOW_COLOR  = \033[1;33m
DEFAULT_COLOR = \033[0m

DED_FLAGS     = -D _DEBUG -ggdb2 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla

.PHONY : clean all frontend frontend_run frontend_clean

# all : $(addprefix $(SRC_DIR), $(SRC))
# 	clear
# 	@mkdir -p build
# 	$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(TARGET))
# 	@printf "$(GREEN_COLOR)$(TARGET) COMPILED$(DEFAULT_COLOR)\n"
#
# run : $(addprefix $(SRC_DIR), $(SRC))
# 	clear
# 	@mkdir -p build
# 	$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(TARGET))
# 	@printf "$(GREEN_COLOR)$(TARGET) COMPILED$(DEFAULT_COLOR)\n"
# 	$(addprefix $(BUILD_DIR), $(TARGET))

frontend : $(addprefix $(FRONT_DIR), $(addprefix $(SRC_DIR), $(FRONT_SRC)))
	clear
	@mkdir -p $(FRONT_DIR)$(BUILD_DIR)
	@$(CXX) $(CFLAGS) $(DED_FLAGS) $^ $(addprefix $(LIBS_DIR), $(SUBMODULE_SRC)) -o $(addprefix $(FRONT_DIR), $(addprefix $(BUILD_DIR), $(FRONTEND)))
	@printf "$(GREEN_COLOR)$(FRONTEND) COMPILED$(DEFAULT_COLOR)\n"

frontend_run : $(addprefix $(FRONT_DIR), $(addprefix $(SRC_DIR), $(FRONT_SRC)))
	clear
	@make
	@$(FRONT_DIR)$(BUILD_DIR)$(FRONTEND)

frontend_clean :
	@rm -f -r $(addprefix $(FRONT_DIR)$(BUILD_DIR), *.o) $(FRONT_DIR)/*.dSYM
	@printf  "$(YELLOW_COLOR)$(FRONTEND) CLEANED$(DEFAULT_COLOR)\n"

clean :
	@make frontend_clean
	@rm -f -r $(addprefix $(BUILD_DIR), *.o) *.dSYM ./Tree-dumps/*
	@printf  "$(YELLOW_COLOR)$(TARGET) CLEANED$(DEFAULT_COLOR)\n"

doxygen :
	doxygen
