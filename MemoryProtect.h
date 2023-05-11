#pragma once

#include <ntddk.h>
#include <intrin.h>



KIRQL g_OldIrql = PASSIVE_LEVEL;



//�ر��ڴ汣��
VOID MemoryProtectOff()
{
	g_OldIrql = KeRaiseIrqlToDpcLevel();
	
	//�ر��ж�
	_disable();


	ULONGLONG cr0 = __readcr0();
	cr0 &= ~0x10000;
	__writecr0(cr0);
}

//�����ڴ汣��
VOID MemoryProtectOn()
{
	KeLowerIrql(g_OldIrql);
	//�����ж�
	_enable();

	ULONGLONG cr0 = __readcr0();
	cr0 |= 0x10000;
	__writecr0(cr0);
}