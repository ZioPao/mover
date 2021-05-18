#include "FrdmK64f_Output.h"

FrdmK64f_Output::FrdmK64f_Output(void) : led(LED_RED, LED_GREEN, LED_BLUE), host(USBTX, USBRX) {} 