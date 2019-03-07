// #pragma once
//-------------------------------------
// (c) 2018 MIT License Marcel Bobolz
// <mailto:ergotamin.source@gmail.com>
//-------------------------------------

#define VHASH ((const unsigned long[]){ 0x6564636261UL, 0UL })

#pragma vscode vermagic

//
int main(int, char **)
{
    __builtin_printf("\nWorks {%s}\n", vermagic);
}
