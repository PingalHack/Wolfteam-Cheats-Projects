#pragma once
HANDLE MEMORY = OpenProcess(PROCESS_ALL_ACCESS, 0, GetCurrentProcessId());
DWORD cshelldll;
DWORD wolfteambin;
BOOL PointModule = FALSE;
bool always_headshot = false;
bool engine_getscript = false;

DWORD WINAPI memory_c(HMODULE hModule, LPDIRECT3DDEVICE9 pDevice)
{
    if (!PointModule)
    {
        cshelldll = (DWORD)GetModuleHandle("cshell.dll");
        wolfteambin = (DWORD)GetModuleHandle("Wolfteam.bin");
        PointModule = TRUE;
    }

    typedef PVOID(*name)();
    name namespaktifet = (name)((char*)"PNL_DrawPlayerNameAll");

    while (true)
    {
 //    
 // 
   if (esp_settings.m_espname ==  true) // tamam 
        {

       typedef PVOID(*name)();
       name namespaktifet = (name)((char*)"PNL_DrawPlayerNameAll");
        }
       
 // 
 // 
 // 
 // 
 //    // Name Esp
 //       if (esp_settings.m_espname ==  true) // tamam 
 //       {
 //           DWORD WallHacks = cshelldll + 0x38175D;
 //           DWORD WallValue = 2201498484; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //      
 //       if (esp_settings.m_espname == false) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x38175D;
 //           DWORD WallValue = 2201498485; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       // Inf Ammo
 //       if (weapon_settings.dw_infiniteammo == true) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x586A9;
 //           DWORD WallValue = 4169338485; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       if (weapon_settings.dw_infiniteammo == false) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x586A9;
 //           DWORD WallValue = 4169338484; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       // No Recoil
 //       if (weapon_settings.dw_norecoil == true) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x49E808;
 //           DWORD WallValue = 0; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       if (weapon_settings.dw_norecoil == false) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x49E808;
 //           DWORD WallValue = 1078530011; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       //NoSpread
 //       if (weapon_settings.dw_nospread == true) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x159323;
 //           DWORD WallValue = 1301090420; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }


 //       if (weapon_settings.dw_nospread == false) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x159323;
 //           DWORD WallValue = 1301090421; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       // repifire
 //       if (weapon_settings.dw_repidfire == true) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x13FF9B;
 //           DWORD WallValue = 1574503796; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       if (weapon_settings.dw_repidfire == false) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x13FF9B;
 //           DWORD WallValue = 1574503797; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }


 //       // AlwaysHeadShot
 //       if (weapon_settings.always_headshot == true) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x1DCD85;
 //           DWORD WallValue = 1566441904; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       if (weapon_settings.always_headshot == false) // tamam
 //       {
 //           DWORD WallHacks = cshelldll + 0x1DCD85;
 //           DWORD WallValue = 1566490674; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }


 //    




 //       // WallShot 
 //       if (weapon_settings.dw_wallshot == true) // tamam
 //       {
 //           DWORD WallHacks = wolfteambin + 0x520A1;
 //           DWORD WallValue = 5; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }


 //       if (weapon_settings.dw_wallshot == false) // tamam
 //       {
 //           DWORD WallHacks = wolfteambin + 0x520A1;
 //           DWORD WallValue = 1967244534; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       // movement speed true
 //       if (player_settings.dw_movementspeed == true)
 //       {
 //           DWORD WallHacks = cshelldll + 0x11A102;
 //           DWORD WallValue = 2391618677; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       // movement speed false
 //       if (player_settings.dw_movementspeed == false)
 //       {
 //           DWORD WallHacks = cshelldll + 0x11A102;
 //           DWORD WallValue = 2391618676; // of 21988367
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       // Jump Changer
 //       if (player_settings.dw_jump0 == 0)
 //       {
 //           DWORD WallHacks = cshelldll + 0x4B4D84;
 //           DWORD WallValue = 1065353216; // 
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       if (player_settings.dw_jump1 == 1)
 //       {
 //           DWORD WallHacks = cshelldll + 0x4B4D84;
 //           DWORD WallValue = 1072064102; // 
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       if (player_settings.dw_jump2 == 2)
 //       {
 //           DWORD WallHacks = cshelldll + 0x4B4D84;
 //           DWORD WallValue = 1075419546; //
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }



 //       //TeamKill
 //       if (player_settings.dw_teamkill == true)
 //       {
 //           DWORD WallHacks = cshelldll + 0x1C1335;
 //           DWORD WallValue = 4286937971; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       if (player_settings.dw_teamkill == false)
 //       {
 //           DWORD WallHacks = cshelldll + 0x1C1335;
 //           DWORD WallValue = 4286937972; // of 21988367
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }



 //       // RespawmWhereDie
 //       if (player_settings.respawnwheredied == true)
 //       {
 //           DWORD WallHacks = cshelldll + 0x119A15;
 //           DWORD WallValue = 3897951861; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       if (player_settings.respawnwheredied == false)
 //       {
 //           DWORD WallHacks = cshelldll + 0x119A15;
 //           DWORD WallValue = 3897951860; // of 21988367
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

 //       // NoFallDamage
 //       if (player_settings.nofalldamage == true)
 //       {
 //           DWORD WallHacks = cshelldll + 0x11DA93;
 //           DWORD WallValue = 2654543220; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       if (player_settings.nofalldamage == false)
 //       {
 //           DWORD WallHacks = cshelldll + 0x11DA93;
 //           DWORD WallValue = 2654543221; // of 21988367
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }


 //       if (player_settings.godmode)
 //       {
 //           if (player_settings.godmode == true)
 //           {
 //               DWORD WallHacks = cshelldll + 0x117849;
 //               DWORD WallValue = 3641198040; // on 21988623
 //               WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //           }
 //           if (player_settings.godmode == true)
 //           {
 //               DWORD WallHacks = cshelldll + 0x258E8E;
 //               DWORD WallValue = 3641198040; // on 21988623
 //               WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //           }
 //           if (player_settings.godmode == true)
 //           {
 //               DWORD WallHacks = cshelldll + 0x258EDD;
 //               DWORD WallValue = 3641198040; // on 21988623
 //               WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //           }
 //           if (player_settings.godmode == true)
 //           {
 //               DWORD WallHacks = cshelldll + 0x258F0E;
 //               DWORD WallValue = 3641198040; // on 21988623
 //               WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //           }
 //           if (player_settings.godmode == true)
 //           {
 //               DWORD WallHacks = cshelldll + 0x258F39;
 //               DWORD WallValue = 3641198040; // on 21988623
 //               WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //           }
 //       }

 //       // AllPlayerFreeze
 //       if (player_settings.allfreezeplayer == true)
 //       {
 //           DWORD WallHacks = wolfteambin + 0xD054E;
 //           DWORD WallValue = 5; // on 21988623
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }
 //       if (player_settings.allfreezeplayer == false)
 //       {
 //           DWORD WallHacks = wolfteambin + 0xD054E;
 //           DWORD WallValue = 1574503797; // of 21988367
 //           WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //       }

    //}




 //   if (player_settings.nogravity == true)
 //   {
 //       DWORD WallHacks = cshelldll + 0x1BD2B;
 //       DWORD WallValue = 5; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.nogravity == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0x1BD2B;

 //       DWORD WallValue = 1967244368;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }





 //   if (player_settings.ms == true)
 //   {
 //       DWORD WallHacks = wolfteambin + 0x7EDC6;
 //       DWORD WallValue = 5; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.ms == false)
 //   {
 //       DWORD WallHacks = wolfteambin + 0x7EDC6;

 //       DWORD WallValue = 2088862859;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }




 //   if (weapon_settings.noreload == true) //tamam
 //   {
 //       DWORD WallHacks = cshelldll + 0x13E2AE;
 //       DWORD WallValue = 2257258100; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (weapon_settings.noreload == false) // tamam
 //   {
 //       DWORD WallHacks = cshelldll + 0x13E2AE;

 //       DWORD WallValue = 2257258101;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }



 //   if (texture_settings.wolveshole == true)
 //   {
 //       DWORD WallHacks = cshelldll + 0x37004;
 //       DWORD WallValue = 3624157400; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (texture_settings.wolveshole == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0x37004;

 //       DWORD WallValue = 3624157401;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }




 //   if (player_settings.FreezePlayer == true)
 //   {
 //       DWORD WallHacks = cshelldll + 0xD054E;
 //       DWORD WallValue = 1574503796; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.FreezePlayer == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0xD054E;

 //       DWORD WallValue = 1574503797;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }



 //   if (player_settings.antistun == true)
 //   {
 //       DWORD WallHacks = cshelldll + 0x8216E;
 //       DWORD WallValue = 1574503796; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.antistun == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0x8216E;

 //       DWORD WallValue = 1574503797;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }




 //   if (player_settings.sphack == true) // 2500 wp
 //   {
 //       DWORD WallHacks = cshelldll + 0x1A3C69;
 //       DWORD WallValue = 3071218292; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.sphack == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0x1A3C69;

 //       DWORD WallValue = 3071218293;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }




 //   if (player_settings.Instant_Respawn == true) // 2500 wp
 //   {
 //       DWORD WallHacks = cshelldll + 0x785F1;
 //       DWORD WallValue = 1574503796; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.Instant_Respawn == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0x785F1;

 //       DWORD WallValue = 1574503797;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }




 //   if (player_settings.Wolf_Ability == true) // 2500 wp
 //   {
 //       DWORD WallHacks = cshelldll + 0x59E4D;
 //       DWORD WallValue = 28312949; // suan test edemedigimden value'yi bilmiyorum o yüzden value' yanlýs ola bilir dene simdi
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
 //   }
 //   if (player_settings.Wolf_Ability == false)
 //   {
 //       DWORD WallHacks = cshelldll + 0x59E4D;

 //       DWORD WallValue = 28312948;
 //       WriteProcessMemory(MEMORY, (LPVOID)WallHacks, &WallValue, 4, NULL);
    }




}