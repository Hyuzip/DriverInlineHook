#pragma once

#include <ntddk.h>
#include <intrin.h>



KIRQL g_OldIrql = PASSIVE_LEVEL;



//关闭内存保护
VOID MemoryProtectOff()
{
	g_OldIrql = KeRaiseIrqlToDpcLevel();
	
	//关闭中断
	_disable();


	ULONGLONG cr0 = __readcr0();
	cr0 &= ~0x10000;
	__writecr0(cr0);
}

//开启内存保护
VOID MemoryProtectOn()
{
	KeLowerIrql(g_OldIrql);
	//开启中断
	_enable();

	ULONGLONG cr0 = __readcr0();
	cr0 |= 0x10000;
	__writecr0(cr0);
}