

#include "main.h"


#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx9.h"
#include "imgui\imgui_impl_win32.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


//detours
#include "detours.h"
#if defined _M_X64
#pragma comment(lib, "detours.X64/detours.lib")
#elif defined _M_IX86
#pragma comment(lib, "detours.X86/detours.lib")
#endif
#include "imgui/imgui_internal.h"

#include "r_settings.h"

#include "Image.h"
#include "Snowflake.cpp/Snowflake.hpp"
#include "memory.h"
#include "esp_rozen.h"
#include "bypass.h"

typedef HRESULT(APIENTRY *SetStreamSource)(IDirect3DDevice9*, UINT, IDirect3DVertexBuffer9*, UINT, UINT);
SetStreamSource SetStreamSource_orig = 0;

typedef HRESULT(APIENTRY *SetVertexDeclaration)(IDirect3DDevice9*, IDirect3DVertexDeclaration9*);
SetVertexDeclaration SetVertexDeclaration_orig = 0;

typedef HRESULT(APIENTRY *SetVertexShaderConstantF)(IDirect3DDevice9*, UINT, const float*, UINT);
SetVertexShaderConstantF SetVertexShaderConstantF_orig = 0;

typedef HRESULT(APIENTRY *SetVertexShader)(IDirect3DDevice9*, IDirect3DVertexShader9*);
SetVertexShader SetVertexShader_orig = 0;

typedef HRESULT(APIENTRY *SetPixelShader)(IDirect3DDevice9*, IDirect3DPixelShader9*);;
SetPixelShader SetPixelShader_orig = 0;


typedef HRESULT(APIENTRY *DrawIndexedPrimitive)(IDirect3DDevice9*, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
DrawIndexedPrimitive DrawIndexedPrimitive_orig = 0;

typedef HRESULT(APIENTRY *DrawPrimitive)(IDirect3DDevice9*, D3DPRIMITIVETYPE, UINT, UINT);
DrawPrimitive DrawPrimitive_orig = 0;

typedef HRESULT(APIENTRY *SetTexture)(IDirect3DDevice9*, DWORD, IDirect3DBaseTexture9 *);
SetTexture SetTexture_orig = 0;

typedef HRESULT(APIENTRY* Present) (IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
Present Present_orig = 0;

typedef HRESULT(APIENTRY* EndScene) (IDirect3DDevice9*);
EndScene EndScene_orig = 0;

typedef HRESULT(APIENTRY *Reset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
Reset Reset_orig = 0;

//==========================================================================================================================

WNDPROC game_wndproc = NULL;

// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		//Log("ImGui_ImplWin32_WndProcHandler");
		return true;
	}

	return CallWindowProc(game_wndproc, hWnd, msg, wParam, lParam);
}

void ToggleButton(const char* str_id, bool* v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.75f;
	float radius = height * 0.50f;

	ImGui::InvisibleButton(str_id, ImVec2(width, height));
	if (ImGui::IsItemClicked())
		*v = !*v;

	float t = *v ? 1.0f : 0.0f;

	ImGuiContext& g = *GImGui;
	float ANIM_SPEED = 0.08f;
	if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *v ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImColor(25, 25, 25), ImVec4(ImColor(35, 35, 35)), t));
	else
		col_bg = ImGui::GetColorU32(ImLerp(ImColor(25, 25, 25), ImVec4(ImColor(35, 35, 35)), t));

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}


//==========================================================================================================================
#define wolfplayer (NumVertices == 37 )|


#define HummanBoyunluk primCount == 30
#define Wolf primCount == 41
#define Wolf2 primCount == 124
#define Wolf3  primCount == 84
#define Wolf5  primCount == 37
#define Wolf6  primCount == 44
DWORD dwZFunc = NULL;
#define Wolfteams Stride == 44 || Stride == 32 || Stride == 40 || Stride == 36


UINT Filtrados[800] = { 0 };
int Contador = 0;
UINT utltimoFiltrado;

void ItemsAdd(UINT AtualValor) {
	if (utltimoFiltrado == AtualValor)
		return;
	utltimoFiltrado = AtualValor;

	bool off_ = false;
	if (Contador == 0) {
		Filtrados[0] = AtualValor;
		Contador++;
		printf("valor: %d \n", AtualValor);
	}
	if (Contador >= 200 || AtualValor == 0)
		return;
	for (int i = 0; i < (Contador - 1); i++)
	{
		if (Filtrados[i] == AtualValor) {
			off_ = true;
		}
	}
	if (!off_) {
		Filtrados[Contador] = AtualValor;
		Contador++;
		printf("Valor: %d \n", AtualValor);
	}
}

UINT ItemsIndexados = 0;

int incme = 0;
void ItemsIncrement() {
	if (incme < Contador) {
		ItemsIndexados = Filtrados[incme];
		printf("========>ItemsIndexados: %d \n", ItemsIndexados);
		incme++;
	}
}


void ItemsDecrement() {
	if (incme > 0) {
		ItemsIndexados = Filtrados[incme];
		printf("========>ItemsIndexados: %d \n", ItemsIndexados);
		incme--;
	}
}

bool SpriteCreated1 = false;
LPDIRECT3DTEXTURE9 IMAGE1;
LPD3DXSPRITE SPRITE1 = NULL;
IDirect3DPixelShader9* sAdd = NULL;
char ShaderAdd[] = "ps.1.0 def c0, 0.0f, 0.0f, 0.0f, 0.0f tex t0 add r0, c0, t0";
ID3DXBuffer* ShaderBufferAdd = NULL;
LPDIRECT3DSTATEBLOCK9 pStateBlock = NULL;
float pSize1 = 50; //pic size
bool i = false;
DWORD dwPixel;

HRESULT APIENTRY DrawIndexedPrimitive_hook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{


	if ((Stride == 40) ||
		(Stride == 44))
	{
		if (esp_settings.Chams)
		{
			// Disable the 'Z' Buffer.
			pDevice->GetRenderState(D3DRS_ZFUNC, &dwPixel);
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

			// Color non-visible objects.
			pDevice->SetTexture(0, Red);

			// Call Dip.


			// Enable the 'Z' Buffer
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, dwPixel);

			// Color visible objects.
			pDevice->SetTexture(0, Yellow);
		}

	}





	if (esp_settings.m_espline)
	{
		if (Wolf || Wolf2 || Wolf3)
		{
			AddModel(pDevice, 1, 120.5f);
		}
	}




	if (esp_settings.m_inofog)
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	}


	if (esp_settings.m_ifullbright)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, false);
		pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 255));
	}






	if (esp_settings.m_ichams)
	{
		if (Wolf || Wolf2 || Wolf3 || Wolf5 || Wolf6 )
		{
			AddModel(pDevice, 1, 120.5f);
			/*pDevice->SetTexture(0, Red);*/
		}
	}



	if (esp_settings.m_espline) {
		if (Wolfteams) {
			pDevice->SetRenderState(D3DRS_ZENABLE, 0);
			DrawIndexedPrimitive_orig(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, 1);
		}
	}

	if (esp_settings.m_iespdistance) {
		if (Wolfteams) {
			pDevice->SetTexture(0, Red);
		}
	}

	if (esp_settings.m_crcile_esp)
	{
		// Disable the 'Z' Buffer
		pDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	}

	if (esp_settings.m_health_esp) {
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	if (GetAsyncKeyState(VK_NUMPAD5) & 1)
	{
		ItemsDecrement();
	}

	if (GetAsyncKeyState(VK_NUMPAD6) & 1)
	{
		ItemsIncrement();
	}

	if (NumVertices)
		ItemsAdd(NumVertices);

	if (NumVertices == ItemsIndexados) {

		if (SpriteCreated1 == FALSE)
		{
			D3DXAssembleShader(ShaderAdd, sizeof(ShaderAdd), NULL, NULL, 0, &ShaderBufferAdd, NULL);
			pDevice->CreatePixelShader((const DWORD*)ShaderBufferAdd->GetBufferPointer(), &sAdd);
			ShaderBufferAdd->Release();
			
		
		
			pDevice->SetTexture(0, Red);
			SpriteCreated1 = TRUE;
			
		}

		D3DXCreateSprite(pDevice, &SPRITE1);

		SPRITE1->Begin(D3DXSPRITE_ALPHABLEND | -1);
		SPRITE1->Draw(IMAGE1, NULL, NULL, NULL, 0xFFFFFFFF);
		SPRITE1->End();
		if (SPRITE1 != NULL) { SPRITE1->Release(); SPRITE1 = NULL; }

		LPDIRECT3DSTATEBLOCK9 pStateBlock = NULL;
		pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);
		pStateBlock->Capture();

		pDevice->SetTexture(0, IMAGE1);
		pDevice->SetPixelShader(sAdd);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//<-
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

		pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pSize));
		pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, *((DWORD*)&pSize1));
		pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, *((DWORD*)&pSize1));
		pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, 1);

		pStateBlock->Apply();
		pStateBlock->Release();
	}

	return DrawIndexedPrimitive_orig(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

//=====================================================================================================================

void Rozen_Tema() {
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_ChildBg] = ImColor(24, 29, 59, 0);
	colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.11f, 0.50f);
	colors[ImGuiCol_FrameBg] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_Header] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_HeaderActive] = ImColor(28, 28, 36, 255);
	colors[ImGuiCol_HeaderHovered] = ImColor(30, 30, 38, 255);
	colors[ImGuiCol_PopupBg] = ImColor(35, 35, 45, 255);
	colors[ImGuiCol_Button] = ImColor(17, 17, 17);
	colors[ImGuiCol_ButtonHovered] = ImColor(19, 19, 19);
	colors[ImGuiCol_ButtonActive] = ImColor(19, 19, 19);
}


IDirect3DTexture9* logggo = nullptr;
ImFont* ee = nullptr;

// Main code
bool buttons = true; bool logolar = true;
bool discord = true; bool background = true;

bool discord_hwid = true;

void text_char(char* text)
{
	ImGui::Text(text);
}
bool m_itest = false;

int ez_menu = 0;

bool dw_3d_box = 0;


float	getSizeX(286.283);



ImVec2 pos;
ImDrawList* draw;
LPDIRECT3DDEVICE9 pDevice;
void decorations()
{
	pos = ImGui::GetWindowPos();
	draw = ImGui::GetWindowDrawList();


	if (background)
	{
		draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 0), ImVec2(pos.x + 700, pos.y + 430), ImColor(10, 10, 10), 12);
	}

	// Background sol
	draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 50), ImVec2(pos.x + 280, pos.y + 430), ImColor(10, 10, 10), 8);

	// Background Yukarý Seperator
	draw->AddRectFilled(ImVec2(pos.x + 280, pos.y + 50), ImVec2(pos.x + 277, pos.y + 430), ImColor(15, 25, 35));

	if (discord)
	{
		// hwid cizgiler
		draw->AddRectFilled(ImVec2(pos.x + 9, pos.y + 365), ImVec2(pos.x + 273, pos.y + 421), ImColor(0, 0, 0), 5);
		// hwid 
		draw->AddRectFilled(ImVec2(pos.x + 10, pos.y + 366), ImVec2(pos.x + 272, pos.y + 420), ImColor(25, 25, 25), 5);
	}

	// Background üst
	draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 10), ImVec2(pos.x + 700, pos.y + 50), ImColor(15, 15, 15));
	draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 50), ImVec2(pos.x + 700, pos.y + 52), ImColor(15, 25, 35)); // Background Seperator

	// Yukarý Ayýrýcý Seperator xd
	draw->AddRectFilled(ImVec2(pos.x + 277, pos.y + 43), ImVec2(pos.x + 279, pos.y + 19), ImColor(15, 25, 35));

	// Name
	 draw->AddText(ee, 13.f, ImVec2(pos.x + 45, pos.y + 22), ImColor(255, 255, 255), u8"RozenCommunity | Wolfteam Premium");

	// Tab page name
	if (ez_menu == 0) // visual
	{
		draw->AddText(ee, 13.f, ImVec2(pos.x + 288, pos.y + 22), ImColor(255, 255, 255), u8"Visual");
	}
	if (ez_menu == 1) // aimbot
	{
		draw->AddText(ee, 13.f, ImVec2(pos.x + 288, pos.y + 22), ImColor(255, 255, 255), u8"Aimbot");
	}
	if (ez_menu == 2) // weapon
	{
		draw->AddText(ee, 13.f, ImVec2(pos.x + 288, pos.y + 22), ImColor(255, 255, 255), u8"Weapons");
	}
	if (ez_menu == 3) // Movement
	{
		draw->AddText(ee, 13.f, ImVec2(pos.x + 288, pos.y + 22), ImColor(255, 255, 255), u8"Movement");
	}
	if (ez_menu == 4) // Others
	{
		draw->AddText(ee, 13.f, ImVec2(pos.x + 288, pos.y + 22), ImColor(255, 255, 255), u8"Others");
	}
	if (ez_menu == 5) // Settings
	{
		draw->AddText(ee, 13.f, ImVec2(pos.x + 288, pos.y + 22), ImColor(255, 255, 255), u8"Settings");
	}

	if (buttons)
	{
		// visual
		ImGui::SetCursorPosX(5); ImGui::SetCursorPosY(52);
		if (ImGui::Button("", ImVec2(271.9f, 50)))
		{
			ez_menu = 0;
		}
		ImGui::SetWindowFontScale(1.4);
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(62); ImGui::Text("Visual");
		ImGui::SetWindowFontScale(0.8);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(80); ImGui::Text("Show enemies behind the wall.");
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(530); ImGui::SetCursorPosY(50);
		// Aimbot
		ImGui::SetCursorPosX(5); ImGui::SetCursorPosY(103);
		if (ImGui::Button(" ", ImVec2(271.9f, 50))) // buton genisligi
		{
			ez_menu = 1;
		}
		ImGui::SetWindowFontScale(1.4);
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(112); ImGui::Text("Aimbot");
		ImGui::SetWindowFontScale(0.8);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(130); ImGui::Text("Outo-aims the character.");
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(530); ImGui::SetCursorPosY(50);
		// Weapons
		ImGui::SetCursorPosX(5); ImGui::SetCursorPosY(154);
		if (ImGui::Button("   ", ImVec2(271.9f, 50))) // buton genisligi
		{
			ez_menu = 2;
		}
		ImGui::SetWindowFontScale(1.4);
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(163); ImGui::Text("Weapons");
		ImGui::SetWindowFontScale(0.8);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(182); ImGui::Text("Changing the character's weapon attributes.");
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(530); ImGui::SetCursorPosY(50);
		// Movement
		ImGui::SetCursorPosX(5); ImGui::SetCursorPosY(205);
		if (ImGui::Button("     ", ImVec2(271.9f, 50))) // buton genisligi
		{
			ez_menu = 3;
		}
		ImGui::SetWindowFontScale(1.4);
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(213); ImGui::Text("Movement");
		ImGui::SetWindowFontScale(0.8);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(233); ImGui::Text("Gives the character flying sprint abilities");
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(530); ImGui::SetCursorPosY(50);

		// Others
		ImGui::SetCursorPosX(5); ImGui::SetCursorPosY(256);
		if (ImGui::Button("      ", ImVec2(271.9f, 50))) // buton genisligi
		{
			ez_menu = 4;
		}
		ImGui::SetWindowFontScale(1.4);
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(266); ImGui::Text("Others");
		ImGui::SetWindowFontScale(0.8);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(283); ImGui::Text("Other features");
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(530); ImGui::SetCursorPosY(50);
		// Settings
		ImGui::SetCursorPosX(5); ImGui::SetCursorPosY(307);
		if (ImGui::Button("       ", ImVec2(271.9f, 50))) // buton genisligi
		{
			ez_menu = 5;
		}
		ImGui::SetWindowFontScale(1.4);
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(315); ImGui::Text("Settings");
		ImGui::SetWindowFontScale(0.8);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
		ImGui::SetCursorPosX(50); ImGui::SetCursorPosY(335); ImGui::Text("Section with settings");
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(530); ImGui::SetCursorPosY(50);
	}
	if (discord_hwid)
	{
		// discord name
		ImGui::SetCursorPos(ImVec2(53, 380));
		ImGui::SetWindowFontScale(1); ImGui::Text("pingals#1658");
		// discord hwid
		ImGui::SetCursorPos(ImVec2(53, 396));
		ImGui::SetWindowFontScale(0.9); ImGui::Text("Hwid : 125-951-145-95C-14A-62E-Q22-9CS-W1L");
	}
}


bool animasyon = 0;
std::vector<Snowflake::Snowflake> snow;
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080
#define SNOW_LIMIT 300
HRESULT APIENTRY EndScene_hook(IDirect3DDevice9* pDevice)
{
	if (pDevice == nullptr) return EndScene_orig(pDevice);

	if (GetAsyncKeyState(VK_F10) & 1)
		Log("endscene called");

	if (!is_imgui_initialised)
	{
		//get viewport
		pDevice->GetViewport(&Viewport);
		ScreenCX = (float)Viewport.Width / 2.0f;
		ScreenCY = (float)Viewport.Height / 2.0f;

		//generate texture
		GenerateTexture(pDevice, &Red, D3DCOLOR_ARGB(255, 255, 0, 0));
		GenerateTexture(pDevice, &Green, D3DCOLOR_RGBA(0, 255, 0, 255));
		GenerateTexture(pDevice, &Blue, D3DCOLOR_ARGB(255, 0, 0, 255));
		GenerateTexture(pDevice, &Yellow, D3DCOLOR_ARGB(255, 255, 255, 0));

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard; //control menu with mouse
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

		io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 12.0f);
		io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arial.ttf", 13.0f);
		ee = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arial.ttf", 13.0f);
		io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 13.0f);
		io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 15.0f);

		Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 1.f/*minimum size*/, 10.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, WINDOW_WIDTH, WINDOW_HEIGHT, Snowflake::vec3(0.f, 0.005f)/*gravity*/, ImColor(125, 125, 125)/*color*/);

		// Find a handle to the first top-level window belonging to the game process.
		//EnumWindows(find_game_hwnd, GetCurrentProcessId());

		// Window handle to which focus belongs for this Direct3D device (similar to EnumWindows.. above)
		D3DDEVICE_CREATION_PARAMETERS d3dcp;
		pDevice->GetCreationParameters(&d3dcp);
		game_hwnd = d3dcp.hFocusWindow;

		if (game_hwnd != NULL)
		{
			// Swap out the window message handler for our own, allowing us to intercept input events
			game_wndproc = (WNDPROC)SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

			// Perform final ImGui setup tasks and..
			ImGui_ImplWin32_Init(game_hwnd);
			ImGui_ImplDX9_Init(pDevice);
			ImGui::GetIO().ImeWindowHandle = game_hwnd;

			//load settings
			LoadCfg();

			is_imgui_initialised = true;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*
	//may have to delay shitproc for 2 sec in a few games
	if(!is_wndproc_initialised)
	if (timeGetTime() - wndproctime >= 2000)
	{
		is_wndproc_initialised = true;
		//Log("is_wndproc_initialised");
		// Swap out the window message handler for our own, allowing us to intercept input events.
		game_wndproc = (WNDPROC)SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
		wndproctime = timeGetTime();
	}
	*/

	//info
	if (animasyon)
	{

		ImGui::SetNextWindowPos({ 1 , 1 });
		ImGui::SetNextWindowSize(ImVec2({ ImGui::GetIO().DisplaySize.x,ImGui::GetIO().DisplaySize.y }));

		if (ImGui::Begin("Watermark", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground))
		{
			POINT mouse;
			RECT rc = { 0 };
			GetCursorPos(&mouse);
			Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y), Snowflake::vec3(rc.left, rc.top));
		}
	}

	//menu key
	//GetAsyncKeyState & 1 may not work in every game
	static auto is_down = false;
	static auto is_clicked = false;
	if (GetAsyncKeyState(VK_INSERT))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GetAsyncKeyState(VK_INSERT) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else {
		is_clicked = false;
		is_down = false;
	}

	//show menu
	if (is_clicked)
	{
		ShowMenu = !ShowMenu;
		//save settings
		SaveCfg();
	}

	//mouse cursor on in menu
	//ImGuiIO& io = ImGui::GetIO();
	if (ShowMenu)
		ImGui::GetIO().MouseDrawCursor = 1;
	//io.MouseDrawCursor = true;
	else
		ImGui::GetIO().MouseDrawCursor = 0;
	//io.MouseDrawCursor = false;

//draw menu
	if (ShowMenu)
	{
		Rozen_Tema();
		ImGui::Begin("RozenUI", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
		{
			pos = ImGui::GetWindowPos();
			draw = ImGui::GetWindowDrawList();

			ImGui::SetWindowSize(ImVec2(700, 430));

			// icons
			// visual
			if (m_visual == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_visual, sizeof(bytes::my_visual), &m_visual);

			// aimbot
			if (m_aimbot == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_aimbot, sizeof(bytes::my_aimbot), &m_aimbot);

			// weapons
			if (m_weapons == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_weapons, sizeof(bytes::my_weapons), &m_weapons);

			// others
			if (m_movement == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_movement, sizeof(bytes::my_movement), &m_movement);

			// movement
			if (m_others == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_others, sizeof(bytes::my_others), &m_others);

			// settings
			if (m_settings == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_settings, sizeof(bytes::my_settings), &m_settings);

			// settings
			if (m_discord_logo == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_discord_logo, sizeof(bytes::my_discord_logo), &m_discord_logo);

			// logo
			if (m_logo == NULL)
				D3DXCreateTextureFromFileInMemory(pDevice, bytes::my_logo, sizeof(bytes::my_logo), &m_logo);

		    decorations();

			if (ez_menu == 0) // visual
			{
				
				draw->AddRectFilled(ImVec2(pos.x + 280, pos.y + 52), ImVec2(pos.x + 700, pos.y + 429), ImColor(10, 10, 10), 12);
				ImGui::SetCursorPos(ImVec2(283, 56)); // bekle 1 dk
				ImGui::BeginChild("##visual", ImVec2(440, 369),true);
				{
					// Esp 3D
					if (ImGui::Button("        ", ImVec2(411, 35)))
					{
						esp_settings.m_box3d = !esp_settings.m_box3d;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(19); ImGui::Text("+ Esp Box"); // ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(66) bunlar neyse ben cýkýyorum bb
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(17); ToggleButton("e", &esp_settings.m_box3d);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();


					if (ImGui::Button("         ", ImVec2(411, 35)))
					{
						esp_settings.m_box2d = !esp_settings.m_box2d;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(65); ImGui::Text("+ Esp Line");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(63); ToggleButton("e", &esp_settings.m_box2d);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("          ", ImVec2(411, 35)))
					{
						esp_settings.m_espname = !esp_settings.m_espname;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(111); ImGui::Text("+ Esp Name");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(109); ToggleButton("e", &esp_settings.m_espname);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("            ", ImVec2(411, 35)))
					{
						esp_settings.m_ichams = !esp_settings.m_ichams;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(157); ImGui::Text("+ Stride ESP");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(155); ToggleButton("e", &esp_settings.m_ichams);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("             ", ImVec2(411, 35)))
					{
						esp_settings.Chams = !esp_settings.Chams;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(203); ImGui::Text("+ Chams 2");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(201); ToggleButton("e", &esp_settings.Chams);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("              ", ImVec2(411, 35)))
					{
						esp_settings.m_espline = !esp_settings.m_espline;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(249); ImGui::Text("+ Esp Wall");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(247); ToggleButton("e", &esp_settings.m_espline);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("               ", ImVec2(411, 35)))
					{
						esp_settings.m_iespdistance = !esp_settings.m_iespdistance;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(295); ImGui::Text("+ Esp Chams");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(293); ToggleButton("e", &esp_settings.m_iespdistance);


					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("                ", ImVec2(411, 35)))
					{
						esp_settings.m_icrosshair = !esp_settings.m_icrosshair;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(341); ImGui::Text("+ CrossHair");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(339); ToggleButton("e", &esp_settings.m_icrosshair);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("                ", ImVec2(411, 35)))
					{
						esp_settings.m_inofog = !esp_settings.m_inofog;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(387); ImGui::Text("+ No Fog");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(385); ToggleButton("e", &esp_settings.m_inofog);

				}
				//ImGui::EndGroup();
				ImGui::EndChild();
			}
			if (ez_menu == 1) // Aimbot
			{
				draw->AddRectFilled(ImVec2(pos.x + 280, pos.y + 52), ImVec2(pos.x + 700, pos.y + 429), ImColor(10, 10, 10), 12);
				ImGui::SetCursorPos(ImVec2(283, 56));
				ImGui::BeginGroup();
				{
					// Aimbot
					if (ImGui::Button("        ", ImVec2(411, 35)))
					{
						aim_settings.dw_aimbot = !aim_settings.dw_aimbot;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(66); ImGui::Text("+ Aimbot");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(63); ToggleButton("e", &aim_settings.dw_aimbot);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("         ", ImVec2(411, 35)))
					{
						aim_settings.dw_aim_fov = !aim_settings.dw_aim_fov;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(111); ImGui::Text("+ Fov");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(108); ToggleButton("e", &aim_settings.dw_aim_fov);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("          ", ImVec2(411, 35)))
					{
						aim_settings.dw_aimsmoth = !aim_settings.dw_aimsmoth;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(156); ImGui::Text("+ Aim Smoth");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(154); ToggleButton("e", &aim_settings.dw_aimsmoth);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();



					if (ImGui::Button("          ", ImVec2(411, 35)))
					{
						weapon_settings.dw_wallshot = !weapon_settings.dw_wallshot;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(202); ImGui::Text("+ AlwaysHeadshot");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(200); ToggleButton("e", &weapon_settings.dw_wallshot);

				}
				ImGui::EndGroup();
			}
			if (ez_menu == 2) // weapon
			{
				draw->AddRectFilled(ImVec2(pos.x + 280, pos.y + 52), ImVec2(pos.x + 700, pos.y + 429), ImColor(10, 10, 10), 0);
				ImGui::SetCursorPos(ImVec2(283, 56));
				ImGui::BeginGroup();
				{
					// Esp 3D
					if (ImGui::Button("        ", ImVec2(411, 35)))
					{
						weapon_settings.dw_infiniteammo = !weapon_settings.dw_infiniteammo;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(66); ImGui::Text("+ infinite Ammo");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(63); ToggleButton("e", &weapon_settings.dw_infiniteammo);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("         ", ImVec2(411, 35)))
					{
						weapon_settings.dw_repidfire = !weapon_settings.dw_repidfire;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(111); ImGui::Text("+ Repid Fire");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(108); ToggleButton("e", &weapon_settings.dw_repidfire);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("          ", ImVec2(411, 35)))
					{
						weapon_settings.dw_norecoil = !weapon_settings.dw_norecoil;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(156); ImGui::Text("+ No Recoil");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(154); ToggleButton("e", &weapon_settings.dw_norecoil);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("            ", ImVec2(411, 35)))
					{
						weapon_settings.dw_nospread = !weapon_settings.dw_nospread;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(203); ImGui::Text("+ No Spread");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(200); ToggleButton("e", &weapon_settings.dw_nospread);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("             ", ImVec2(411, 35)))
					{
						weapon_settings.dw_wallshot = !weapon_settings.dw_wallshot;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(248); ImGui::Text("+ Wall Shot");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(245); ToggleButton("e", &weapon_settings.dw_wallshot);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();
				
					
					
					if (ImGui::Button("              ", ImVec2(411, 35)))
					{
						weapon_settings.noreload = !weapon_settings.noreload;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(293); ImGui::Text("+ No Reload");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(290); ToggleButton("e", &weapon_settings.noreload);
				
					
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					
					
					if (ImGui::Button("              ", ImVec2(411, 35)))
					{
						weapon_settings.always_headshot = !weapon_settings.always_headshot;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(339); ImGui::Text("+ Always Head Shot");
					ImGui::SetCursorPosX(660); ImGui::SetCursorPosY(337); ToggleButton("e", &weapon_settings.always_headshot);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();
					
					
					
				
				}
				ImGui::EndGroup();
			}
			if (ez_menu == 3) // Movement bende wolfteam geliyorum 1 dakkika giriyim oda kur ok
			{
				draw->AddRectFilled(ImVec2(pos.x + 280, pos.y + 52), ImVec2(pos.x + 700, pos.y + 429), ImColor(10, 10, 10), 0);
				ImGui::SetCursorPos(ImVec2(283, 56));
				ImGui::BeginGroup();
				{
					ImGui::Text("esp box 2d");
					ImGui::SliderFloat("+ New Box X", &m_iLBSizeX, -120, 520);
					ImGui::SliderFloat("+ New Box Y", &m_iLBSizeY, -120, 520);
					ImGui::SliderInt("+ New Box S", &m_iLBOXSize, -120, 520);
					ImGui::SliderFloat("+ New Box Z", &m_iBoxSizeZ, -120, 520);
				}
				ImGui::EndGroup();
			}



			if (ez_menu == 4) // Others
			{
				draw->AddRectFilled(ImVec2(pos.x + 280, pos.y + 52), ImVec2(pos.x + 700, pos.y + 429), ImColor(10, 10, 10), 12);
				ImGui::SetCursorPos(ImVec2(283, 56)); // bekle 1 dk
				ImGui::BeginChild("##visual", ImVec2(440, 369), true);
				{
					// Esp 3D
					if (ImGui::Button("        ", ImVec2(411, 35)))
					{
						player_settings.nofalldamage = !player_settings.nofalldamage;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(19); ImGui::Text("+ No Fall Damage"); // ImGui::SetCursorPosX(300); ImGui::SetCursorPosY(66) bunlar neyse ben cýkýyorum bb
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(17); ToggleButton("e", &player_settings.nofalldamage);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();


					if (ImGui::Button("         ", ImVec2(411, 35)))
					{
						player_settings.ms = !player_settings.ms;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(65); ImGui::Text("+ Perfect MS");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(63); ToggleButton("e", &player_settings.ms);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("          ", ImVec2(411, 35)))
					{
						player_settings.Instant_Respawn = !player_settings.Instant_Respawn;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(111); ImGui::Text("+ Instant Respawn");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(109); ToggleButton("e", &player_settings.Instant_Respawn);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("            ", ImVec2(411, 35)))
					{
						player_settings.allfreezeplayer = !player_settings.allfreezeplayer;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(157); ImGui::Text("+ All Freeze Player");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(155); ToggleButton("e", &player_settings.allfreezeplayer);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("             ", ImVec2(411, 35)))
					{
						player_settings.godmode = !player_settings.godmode;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(203); ImGui::Text("+God Mode");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(201); ToggleButton("e", &player_settings.godmode);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("              ", ImVec2(411, 35)))
					{
						player_settings.dw_teamkill = !player_settings.dw_teamkill;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(249); ImGui::Text("+ TeamKill");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(247); ToggleButton("e", &player_settings.dw_teamkill);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("               ", ImVec2(411, 35)))
					{
						player_settings.sphack = !player_settings.sphack;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(295); ImGui::Text("+ YP Booster");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(293); ToggleButton("e", &player_settings.sphack);


					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("                ", ImVec2(411, 35)))
					{
						player_settings.nogravity = !player_settings.nogravity;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(341); ImGui::Text("+ No Gravity");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(339); ToggleButton("e", &player_settings.nogravity);

					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(125, 125, 125)));
					ImGui::Text("_____________________________________________________________________"); // Ayýrýcý :D
					ImGui::PopStyleColor();

					if (ImGui::Button("                ", ImVec2(411, 35)))
					{
						player_settings.antistun = !player_settings.antistun;
					}
					ImGui::SetWindowFontScale(1);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(387); ImGui::Text("+ Anti Stun");
					ImGui::SetCursorPosX(378); ImGui::SetCursorPosY(385); ToggleButton("e", &player_settings.antistun);

				}
				//ImGui::EndGroup();
				ImGui::EndChild();
			}














			if (logolar)
			{
				// Visual
				ImGui::SetCursorPos(ImVec2(10, 60));
				ImGui::Image(m_visual, ImVec2(30, 30));
				// Aimbot
				ImGui::SetCursorPos(ImVec2(10, 112));
				ImGui::Image(m_aimbot, ImVec2(30, 30));
				// Weapons
				ImGui::SetCursorPos(ImVec2(10, 162));
				ImGui::Image(m_weapons, ImVec2(30, 30));
				// Movements
				ImGui::SetCursorPos(ImVec2(10, 215));
				ImGui::Image(m_movement, ImVec2(30, 30));
				// Others
				ImGui::SetCursorPos(ImVec2(10, 265));
				ImGui::Image(m_others, ImVec2(30, 30));
				// Settings
				ImGui::SetCursorPos(ImVec2(10, 315));
				ImGui::Image(m_settings, ImVec2(30, 30));

				// hwid discord
				ImGui::SetCursorPos(ImVec2(13, 375));
				ImGui::Image(m_discord_logo, ImVec2(36, 36));
				// Logo
				ImGui::SetCursorPos(ImVec2(10, 15));
				ImGui::Image(m_logo, ImVec2(30, 30));
			}
			ImGui::End();
		}
	}


	if (ImGui::Begin("Transparent", reinterpret_cast<bool*>(true), ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings));
	{
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

		if (ModelInfo.size() != NULL && bESP)
		{
			for (size_t i = 0; i < ModelInfo.size(); i++)
			{
				ImDrawList* LunaUI = ImGui::GetBackgroundDrawList();
				if (esp_settings.m_box2d) // bunu acmayý unutma
				{
					DrawESPLine(viewport.Width / 2.0f, viewport.Height, (int)ModelInfo[i]->Position2D.x, (int)ModelInfo[i]->Position2D.y - 5, 1, false, D3DCOLOR_ARGB(255, 255, 000, 000), pDevice);
				}
				if (esp_settings.m_box3d)
				{
					DrawBox((int)ModelInfo[i]->Position2D.x - m_iLBSizeX, (int)ModelInfo[i]->Position2D.y - m_iLBSizeY, m_iLBOXSize, m_iBoxSizeZ, D3DCOLOR_ARGB(255, 255, 000, 000)); // 2 d box bu 1 dk
				}
			}
			ModelInfo.clear();
		}

	}

	ImDrawList* LunaUI2 = ImGui::GetOverlayDrawList();
	if (esp_settings.m_icrosshair)
	{
		LunaUI2->AddCircle(ImVec2({ ImGui::GetIO().DisplaySize.x / 2,ImGui::GetIO().DisplaySize.y / 2 }), 15, ImColor(255, 255, 255), 120.0f);
		LunaUI2->AddCircleFilled(ImVec2({ ImGui::GetIO().DisplaySize.x / 2,ImGui::GetIO().DisplaySize.y / 2 }), 15, ImColor(0, 0, 0), 120.0f);
	}



	// Rendering
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return EndScene_orig(pDevice);
}

//==========================================================================================================================

HRESULT APIENTRY Reset_hook(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT ResetReturn = Reset_orig(pDevice, pPresentationParameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	return ResetReturn;
}

//==========================================================================================================================

HRESULT APIENTRY SetStreamSource_hook(LPDIRECT3DDEVICE9 pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT sStride)
{
	if (StreamNumber == 0)
		Stride = sStride;

	return SetStreamSource_orig(pDevice, StreamNumber, pStreamData, OffsetInBytes, sStride);
}

//==========================================================================================================================

HRESULT APIENTRY SetVertexDeclaration_hook(LPDIRECT3DDEVICE9 pDevice, IDirect3DVertexDeclaration9* pdecl)
{
	if (pdecl != NULL)
	{
		pdecl->GetDeclaration(decl, &numElements);
	}

	return SetVertexDeclaration_orig(pDevice, pdecl);
}

//==========================================================================================================================

HRESULT APIENTRY SetVertexShaderConstantF_hook(LPDIRECT3DDEVICE9 pDevice, UINT StartRegister, const float *pConstantData, UINT Vector4fCount)
{
	if (pConstantData != NULL)
	{
		mStartregister = StartRegister;
		mVectorCount = Vector4fCount;
	}

	return SetVertexShaderConstantF_orig(pDevice, StartRegister, pConstantData, Vector4fCount);
}

//==========================================================================================================================

HRESULT APIENTRY SetVertexShader_hook(LPDIRECT3DDEVICE9 pDevice, IDirect3DVertexShader9 *veShader)
{
	if (veShader != NULL)
	{
		vShader = veShader;
		vShader->GetFunction(NULL, &vSize);
	}
	return SetVertexShader_orig(pDevice, veShader);
}

//==========================================================================================================================

HRESULT APIENTRY SetPixelShader_hook(LPDIRECT3DDEVICE9 pDevice, IDirect3DPixelShader9 *piShader)
{
	if (piShader != NULL)
	{
		pShader = piShader;
		pShader->GetFunction(NULL, &pSize);
	}
	return SetPixelShader_orig(pDevice, piShader);
}

//==========================================================================================================================

HRESULT APIENTRY DrawPrimitive_hook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	//in some games hp bars are drawn here

	return DrawPrimitive_orig(pDevice, PrimitiveType, StartVertex, PrimitiveCount);
}

//==========================================================================================================================

HRESULT APIENTRY SetTexture_hook(LPDIRECT3DDEVICE9 pDevice, DWORD Sampler, IDirect3DBaseTexture9 *pTexture)
{
	/*
	//get texture/desc size (usually not needed, decreases fps)
	texture = static_cast<IDirect3DTexture9*>(pTexture);
	if (texture)
	{
		if (FAILED(texture->GetLevelDesc(0, &sDesc)))
			goto out;

		if (sDesc.Pool == D3DPOOL_MANAGED && texture->GetType() == D3DRTYPE_TEXTURE)
		{
			HRESULT hr = texture->LockRect(0, &pLockedRect, NULL, D3DLOCK_DONOTWAIT | D3DLOCK_READONLY | D3DLOCK_NOSYSLOCK);

			if (SUCCEEDED(hr))
			{
				if (pLockedRect.pBits != NULL)
					qCRC = QuickChecksum((DWORD*)pLockedRect.pBits, pLockedRect.Pitch); //get crc
					//qCRC = QuickChecksum((DWORD*)pLockedRect.pBits, 12);
			}
			texture->UnlockRect(0);
		}
	}
out:
	*/
	return SetTexture_orig(pDevice, Sampler, pTexture);
}

//==========================================================================================================================

HRESULT APIENTRY Present_hook(IDirect3DDevice9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	return Present_orig(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

//=====================================================================================================================

DWORD WINAPI D3Dimgui(LPVOID lpParameter)
{
	while (!GetModuleHandleA("d3d9.dll")) {
		Sleep(200);
	}

	IDirect3D9* d3d = NULL;
	IDirect3DDevice9* d3ddev = NULL;

	HWND tmpWnd = CreateWindowA("BUTTON", "DX", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, Hand, NULL);
	if (tmpWnd == NULL)
	{
		//Log("[DirectX] Failed to create temp window");
		return 0;
	}

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		DestroyWindow(tmpWnd);
		//Log("[DirectX] Failed to create temp Direct3D interface");
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = tmpWnd;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if (result != D3D_OK)
	{
		d3d->Release();
		DestroyWindow(tmpWnd);
		MessageBox(game_hwnd, "Run the game first and inject dll later", "Failed to create temp Direct3D device.", MB_OK);
		//MessageBox(game_hwnd, L"Run the game first and inject dll later", L"Failed to create temp Direct3D device.", MB_OK);
		//Log("[DirectX] Failed to create temp Direct3D device. Run the game first and inject dll later"); 
		return 0;
	}

	// We have the device, so walk the vtable to get the address of all the dx functions in d3d9.dll
#if defined _M_X64
	DWORD64* dVtable = (DWORD64*)d3ddev;
	dVtable = (DWORD64*)dVtable[0];
#elif defined _M_IX86
	DWORD* dVtable = (DWORD*)d3ddev;
	dVtable = (DWORD*)dVtable[0]; // == *d3ddev
#endif
	//Log("[DirectX] dVtable: %x", dVtable);

	//for(int i = 0; i < 95; i++)
	//{
			//Log("[DirectX] vtable[%i]: %x, pointer at %x", i, dVtable[i], &dVtable[i]);
	//}

	// Detour functions x86 & x64
	SetStreamSource_orig = (SetStreamSource)dVtable[100];
	SetVertexDeclaration_orig = (SetVertexDeclaration)dVtable[87];
	SetVertexShaderConstantF_orig = (SetVertexShaderConstantF)dVtable[94];
	SetVertexShader_orig = (SetVertexShader)dVtable[92];
	SetPixelShader_orig = (SetPixelShader)dVtable[107];

	DrawIndexedPrimitive_orig = (DrawIndexedPrimitive)dVtable[82];
	DrawPrimitive_orig = (DrawPrimitive)dVtable[81];
	SetTexture_orig = (SetTexture)dVtable[65];
	Present_orig = (Present)dVtable[17];
	EndScene_orig = (EndScene)dVtable[42];
	Reset_orig = (Reset)dVtable[16];
	
	Sleep(15);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)SetStreamSource_orig, (PBYTE)SetStreamSource_hook);
	DetourAttach(&(LPVOID&)SetVertexDeclaration_orig, (PBYTE)SetVertexDeclaration_hook);
	DetourAttach(&(LPVOID&)SetVertexShaderConstantF_orig, (PBYTE)SetVertexShaderConstantF_hook);
	DetourAttach(&(LPVOID&)SetVertexShader_orig, (PBYTE)SetVertexShader_hook);
	DetourAttach(&(LPVOID&)SetPixelShader_orig, (PBYTE)SetPixelShader_hook);

	DetourAttach(&(LPVOID&)DrawIndexedPrimitive_orig, (PBYTE)DrawIndexedPrimitive_hook);
	DetourAttach(&(LPVOID&)DrawPrimitive_orig, (PBYTE)DrawPrimitive_hook);
	DetourAttach(&(LPVOID&)SetTexture_orig, (PBYTE)SetTexture_hook);
	DetourAttach(&(LPVOID&)Present_orig, (PBYTE)Present_hook);
	DetourAttach(&(LPVOID&)EndScene_orig, (PBYTE)EndScene_hook);
	DetourAttach(&(LPVOID&)Reset_orig, (PBYTE)Reset_hook);
	DetourTransactionCommit();
	
	//Log("[Detours] Detours attached\n");

	d3ddev->Release();
	d3d->Release();
	DestroyWindow(tmpWnd);

	return 1;
}

//==========================================================================================================================

void OpenConsole(std::string Title)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	SetConsoleTitle(Title.c_str());
}


BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Hand = hModule;
		DisableThreadLibraryCalls(hModule); 
		if (Beep(100, 100))
		{
			OpenConsole("sssw");
			CreateThread(0, 0, D3Dimgui, 0, 0, 0); //init our hooks
			CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)memory_c, &hModule, NULL, nullptr);
			HideModule(hModule); // bypass fix lenirse baska bir bypass ým daha var nice kanka
		}
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
