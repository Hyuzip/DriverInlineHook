#include <ntddk.h>
#include <windef.h>
#include "MemoryProtect.h"
#include "UnloadDriver.h"


PVOID GetSystemFunctionAddress(PWCHAR FunctionName)
{
	UNICODE_STRING FunctionNameUnicode;
	RtlInitUnicodeString(&FunctionNameUnicode, FunctionName);
	//获得到函数的地址
	return MmGetSystemRoutineAddress(&FunctionNameUnicode);
}

extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING)
{
	NTSTATUS Status = STATUS_SUCCESS;

	do {

	
		PVOID NtOpenProcessAddress = GetSystemFunctionAddress(L"NtOpenProcess");

		if (NtOpenProcessAddress == NULL)
		{
			DbgPrint("--------Fail to get NtOpenProcess Function Address--------");
			Status = STATUS_UNSUCCESSFUL;
			break;
		}
			
		CONST UCHAR ShellCodeSize = 2;
		BYTE ShellCode[ShellCodeSize] =
		{
		0xc3, //ret
		0x90, //nop
		};

		MemoryProtectOff();
		RtlCopyMemory(NtOpenProcessAddress,ShellCode,ShellCodeSize);
		MemoryProtectOn();

		DbgPrint("--------Done...--------");

		DriverObject->DriverUnload = UnloadDriver;

	} while (false);

	return Status;
}