#pragma once

#include <ntddk.h>

VOID UnloadDriver(PDRIVER_OBJECT)
{
	DbgPrint("--------Unload Driver--------");
}