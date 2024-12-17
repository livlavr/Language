#include <stdio.h>
#include <stdarg.h>

#include "color_printf.h"
#include "custom_asserts.h"

void style_selector(MY_COLOR color, FORMAT font)
{
    switch(font)
    {
        case BOLD:
            printf("\033[1m");
            break;
        case REGULAR:
            printf("\033[0m");
            break;
        default:
            printf("FONT SELECTOR ERROR");
            break;
    }
    switch(color)
    {
        case GREEN_COLOR:
            printf("\033[32m");
            break;
        case RED_COLOR:
            printf("\033[31m");
            break;
        case YELLOW_COLOR:
            printf("\033[33m");
            break;
        case BLUE_COLOR:
            printf("\033[34m");
            break;
        case MAGENTA_COLOR:
            printf("\033[35m");
            break;
        case CYAN_COLOR:
            printf("\033[36m");
            break;
        case WHITE_COLOR:
            printf("\033[37m");
            break;
        case DEFAULT_COLOR:
            printf("\033[0m");
            break;
        default:
            warning(false, "COLOR SELECTOR ERROR" && !OKEY);
    }
}

int color_printf(MY_COLOR color, FORMAT font, const char * format_line, ...)
{
    check_expression(format_line, POINTER_IS_NULL);

    va_list arguments;
    style_selector(color, font);
    va_start(arguments, format_line);
    vprintf(format_line, arguments);
    va_end(arguments);
    style_selector(DEFAULT_COLOR, REGULAR);
    return 0;
}
