#pragma once

struct esp_settings
{
    bool m_box3d = 0;
    bool m_box2d = 0;
    bool m_espname = 0;
    bool m_health_esp = 0;
    bool m_crcile_esp = 0;
    bool m_espline = 0;
    bool m_iespdistance = 0;
    bool m_icrosshair = 0;
    bool m_ichams = 0;
    bool m_inofog = 0;
    bool m_ifullbright = 0;
    bool Chams = false;
}esp_settings;



struct aim_settings
{
    bool dw_aimbot = 0;
    bool dw_aim_fov = 0;
    bool dw_aimsmoth = 0;
}aim_settings;
float aim_fov = 32.0f;


struct weapon_settings
{
    bool dw_infiniteammo = false;
    bool dw_norecoil = 0;
    bool dw_nospread = 0;
    bool dw_repidfire = 0;
    bool dw_wallshot = 0;
    bool always_headshot = false;

    bool noreload = false;
}weapon_settings;



struct player_settings
{
    bool dw_movementspeed = 0;
    bool dw_jump0 = 0;
    bool dw_jump1 = 0;
    bool dw_jump2 = 0;
    bool dw_teamkill = 0;
    bool respawnwheredied = 0;
    bool nofalldamage = 0;
    bool godmode = 0;
    bool allfreezeplayer = 0;
    bool nogravity = false;
    bool ms = false;
    bool FreezePlayer = false;
    bool antistun = false;
    bool sphack = false;
    bool Instant_Respawn = false;
    bool Wolf_Ability = false;
    
}player_settings;





struct texture_settings
{
    bool wolveshole = false;
}texture_settings;