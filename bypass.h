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
	PPEB_LDR_DATA Ldr; // atmadý daha? ya mal func tetiklemessen atmaz zaten oyuna gir birde masa üstüne dön oyun kapanýcak bak COMCTL.dll hatasý veriyor ya bu ya kýzým seni cok pis porn yýldýzý yaparým bak aklýný kullan dilini degil aq malý tmm ya teþekür ederim bu kadar yeterli gerisini ben yaparým sq yap o zaman
}PEB, * PPEB;


void HideModule(HINSTANCE hModule) // burda ise ntdll den cekilen veriler ile dll'i gizliyoruz
{
	PEB* peb;
	LDR_MODULE* ldr;
	peb = (PEB*)__readfsdword(0x30);
	ldr = (LDR_MODULE*)peb->Ldr->InLoadOrderModuleList.Flink;
	while (ldr->BaseAddress != 0)// burdan sonra istersen unlik kullan daha da saðlam bypass olur
	{
		if (ldr->BaseAddress == hModule) // ne yapýcaksýn < 0 dan büyüksemi ya býrak lütfen karsýsma artýk tmm ya off sýkýldým ama ben git anime izle
		{
			if (ldr->InLoadOrderModuleList.Blink != 0) // bak bakýyým bi dll gizlemismi calýstý süper ya ben bu sporu yapýyorum anlamadým kýzým git kültür ögren ya sanki senin kültürün iyi de ya iyiyse :D tmm neyse bittimi proje? bitti de tek basýna sadece dll gizler tamam yeterli
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
		ldr = (LDR_MODULE*)ldr->InLoadOrderModuleList.Flink;// buna asm hook eklesene nasýl adresleri bilmiyorum ki kýzým senin aklýný sikiyim ben aq tek yapýcagýn jmp atmak kabalasma ya tmm birsey demedim sana da birsey demek gelmiyor tabi kýzým isine yarayýnca laf yok yaramayýncamý laf cok neyse ya özlür dilerim bitire bilirmissin artýk bilemedim simdi bitirsemmi ki :D lütfen ya sende olmasan kim kod yazcak bana hmm :D
	}
} 