#include "FrdmK64f_AppShield_Output.h"

FrdmK64f_AppShield_Output::FrdmK64f_AppShield_Output(void)
    : lcd(D11, D13, D12, D7, D10), spkr(D6), led(D5, D9, D8) {}