#pragma once
int aimheight = 0;
bool bESP = true;

struct ModelInfo_t {
    D3DXVECTOR3 Position2D;
    D3DXVECTOR3 Position3D;
    int Offset;
    int TEAM;
    int Index;
    float CrosshairDistance;
};
std::vector<ModelInfo_t*>ModelInfo;

LPD3DXFONT g_pFont = NULL;
void PrintText(LPD3DXFONT Font, long x, long y, D3DCOLOR fontColor, char* text, ...)
{
    RECT rct;
    rct.left = x - 1;
    rct.right = x + 1;
    rct.top = y - 1;
    rct.bottom = y + 1;

    if (!text) { return; }
    va_list va_alist;
    char logbuf[256] = { 0 };
    va_start(va_alist, text);
    _vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
    va_end(va_alist);
    RECT FontRect = { x, y, x, y };
    g_pFont->DrawText(NULL, logbuf, -1, &rct, DT_NOCLIP, fontColor);
}
float GetDistance(float Xx, float Yy, float xX, float yY)
{
    return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}
void DrawPoint(LPDIRECT3DDEVICE9 pDevice, int baseX, int baseY, int baseW, int baseH, D3DCOLOR Cor)
{
    D3DRECT BarRect = { baseX, baseY, baseX + baseW, baseY + baseH };
    pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Cor, 0, 0);
}
D3DVIEWPORT9 viewport;
void AddModel(IDirect3DDevice9* Device, int Team, float AimH) {
    ModelInfo_t* pModel = new ModelInfo_t;
    pModel->TEAM = Team;
    Device->GetViewport(&viewport);
    D3DXMATRIX projection, view, world;
    D3DXVECTOR3 vScreenCoord(0, AimH, 0), vWorldLocation(0, AimH, 0);

    Device->GetTransform(D3DTS_VIEW, &view);
    Device->GetTransform(D3DTS_PROJECTION, &projection); // bu kod viewmatrix 
    Device->GetTransform(D3DTS_WORLD, &world);

    D3DXVec3Project(&vScreenCoord, &vWorldLocation, &viewport, &projection, &view, &world);
    if (vScreenCoord.z < 5.0f) {
        pModel->Position2D.x = vScreenCoord.x;
        pModel->Position2D.y = vScreenCoord.y;
    }
    ModelInfo.push_back(pModel);
}

// esp line
LPD3DXLINE		g_pLine = NULL;
void DrawESPLine(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color, LPDIRECT3DDEVICE9 pDevice)
{
    D3DXCreateLine(pDevice, &g_pLine);
    D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
    g_pLine->SetWidth(width);
    if (antialias) g_pLine->SetAntialias(1);
    g_pLine->Begin();
    g_pLine->Draw(line, 2, color);
    g_pLine->End();
    g_pLine->Release();
}


float m_iLBSizeX = 10;

float m_iLBSizeY = 10;

int m_iLBOXSize = 20;

float m_iBoxSizeZ = 30;


auto DrawLine(const ImVec2& aPoint1, const ImVec2 aPoint2, ImU32 aColor, const FLOAT aLineWidth) -> VOID
{
    auto vList = ImGui::GetOverlayDrawList();
    vList->AddLine(aPoint1, aPoint2, aColor, aLineWidth);
}

auto DrawBox(float x, float y, float w, float h, ImColor color)-> VOID
{
    DrawLine(ImVec2(x, y), ImVec2(x + w, y), color, 1.3f); // top 
    DrawLine(ImVec2(x, y - 1.3f), ImVec2(x, y + h + 1.4f), color, 1.3f); // left
    DrawLine(ImVec2(x + w, y - 1.3f), ImVec2(x + w, y + h + 1.4f), color, 1.3f);  // right
    DrawLine(ImVec2(x, y + h), ImVec2(x + w, y + h), color, 1.3f);   // bottom 
}
