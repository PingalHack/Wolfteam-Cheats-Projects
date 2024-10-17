typedef struct _LDR_MODULE
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
}LDR_MODULE, * PLDR_MODULE;
typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
}PEB_LDR_DATA, * PPEB_LDR_DATA;
typedef struct _PEB
{
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	PPEB_LDR_DATA Ldr; // atmad� daha? ya mal func tetiklemessen atmaz zaten oyuna gir birde masa �st�ne d�n oyun kapan�cak bak COMCTL.dll hatas� veriyor ya bu ya k�z�m seni cok pis porn y�ld�z� yapar�m bak akl�n� kullan dilini degil aq mal� tmm ya te�ek�r ederim bu kadar yeterli gerisini ben yapar�m sq yap o zaman
}PEB, * PPEB;


void HideModule(HINSTANCE hModule) // burda ise ntdll den cekilen veriler ile dll'i gizliyoruz
{
	PEB* peb;
	LDR_MODULE* ldr;
	peb = (PEB*)__readfsdword(0x30);
	ldr = (LDR_MODULE*)peb->Ldr->InLoadOrderModuleList.Flink;
	while (ldr->BaseAddress != 0)// burdan sonra istersen unlik kullan daha da sa�lam bypass olur
	{
		if (ldr->BaseAddress == hModule) // ne yap�caks�n < 0 dan b�y�ksemi ya b�rak l�tfen kars�sma art�k tmm ya off s�k�ld�m ama ben git anime izle
		{
			if (ldr->InLoadOrderModuleList.Blink != 0) // bak bak�y�m bi dll gizlemismi cal�st� s�per ya ben bu sporu yap�yorum anlamad�m k�z�m git k�lt�r �gren ya sanki senin k�lt�r�n iyi de ya iyiyse :D tmm neyse bittimi proje? bitti de tek bas�na sadece dll gizler tamam yeterli
				(ldr->InLoadOrderModuleList.Blink)->Flink = ldr->InLoadOrderModuleList.Flink;
			if (ldr->InLoadOrderModuleList.Blink != 0)
				(ldr->InLoadOrderModuleList.Flink)->Blink = ldr->InLoadOrderModuleList.Blink;
			if (ldr->InInitializationOrderModuleList.Blink != 0)
				(ldr->InInitializationOrderModuleList.Blink)->Flink = ldr->InInitializationOrderModuleList.Flink;
			if (ldr->InInitializationOrderModuleList.Flink != 0)
				(ldr->InInitializationOrderModuleList.Flink)->Blink = ldr->InInitializationOrderModuleList.Blink;
			if (ldr->InMemoryOrderModuleList.Flink != 0)
				(ldr->InMemoryOrderModuleList.Blink)->Flink = ldr->InMemoryOrderModuleList.Flink;
			if (ldr->InMemoryOrderModuleList.Flink != 0)
				(ldr->InMemoryOrderModuleList.Flink)->Blink = ldr->InMemoryOrderModuleList.Blink;
		}
		ldr = (LDR_MODULE*)ldr->InLoadOrderModuleList.Flink;// buna asm hook eklesene nas�l adresleri bilmiyorum ki k�z�m senin akl�n� sikiyim ben aq tek yap�cag�n jmp atmak kabalasma ya tmm birsey demedim sana da birsey demek gelmiyor tabi k�z�m isine yaray�nca laf yok yaramay�ncam� laf cok neyse ya �zl�r dilerim bitire bilirmissin art�k bilemedim simdi bitirsemmi ki :D l�tfen ya sende olmasan kim kod yazcak bana hmm :D
	}
} 