.686
.model flat

#define X_VAR(type, name, addr) PUBLIC _##name \n _##name EQU addr
#define X_FUNC(ret, name, addr, params) PUBLIC _##name \n _##name EQU addr

#include "symbols.inc"

END