#pragma once

#define CUBE_INDEX_SIZE 36
extern WORD g_aCubeIndex[];
#define CUBE_VERTEX_SIZE 8
extern D3DXVECTOR3 g_aCubeVertex[];

#define SINGLETON(class_name) private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SAFE_WNDPROC(p) if(p) {(p)->WndProc(hWnd, message, wParam, lParam);}
#define SAFE_UPDATE(p) if(p) { (p)->Update();}
#define SAFE_RENDER(p) if(p) { (p)->Render();}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL;}

#define SCREEN_POINT(lParam) LOWORD(lParam), HIWORD(lParam)

#define METHOD_WNDPROC(method) void method(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)


enum SCENE_INDEX {
	SCENE_GRID,
	SCENE_OBJMAP,
	SCENE_HEIGHTMAP,
	SCENE_TEST,
	SCENE_SHOTTING
};

enum TAG_DISPLAYOBJECT {
	TAG_PLAYER
};

enum class ITEM_TAG
{
	Pistol,
	Bullet
};

enum class ITEM_STATE
{
	Dropped,     //땅에 떨어진 상태
	InInventory, //인벤토리에 있음
	Mounting     //장착중
};

struct KEYBOARD_STATE
{
	D3DXVECTOR3 deltaPos;
	D3DXVECTOR3	deltaRot;
	bool		bJump;
};

//	1. Position 정점의 좌표 x,y,z(float)				: D3DFVF_XYZ
// 	2. RHW (float)                                  : D3DFVF_XYZRHW (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 	3. Blending Weight Data 결합 가중치 (float)		: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 	4. Vertex Normal 정점의 법선 벡터 x,y,z(float)	: D3DFVF_NORMAL
// 	5. Vertex Point Size 정점의 점 크기 (float)		: D3DFVF_PSIZE
// 	6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 	7. Specular Color (DWORD)						: D3DFVF_SPECULAR
// 	8. Texture Coordinate Set 1 (float)             : D3DFVF_TEX0 - D3DFVF_TEX8

struct VERTEX_PC
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	VERTEX_PC() {}
	VERTEX_PC(D3DXVECTOR3 _p, D3DCOLOR _c) :p(_p), c(_c) {}

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};

struct VERTEX_PT
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	VERTEX_PT() {}
	VERTEX_PT(D3DXVECTOR3 _p, D3DXVECTOR2 _t) :p(_p), t(_t) {}
    VERTEX_PT(const float x, const float y, const float z, const float u, const float v)
        : p(x, y, z)
        , t(u, v)
    {
    }

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct VERTEX_PN
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;

	VERTEX_PN() {}
	VERTEX_PN(D3DXVECTOR3 _p, D3DXVECTOR3 _n) :p(_p), n(_n) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct VERTEX_PNT
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	VERTEX_PNT() {}
	VERTEX_PNT(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
		:p(_p), n(_n), t(_t) {}
    VERTEX_PNT(const float x, const float y, const float z, 
               const float nx, const float ny, const float nz, 
               const float u, const float v)
        : p(x, y, z)
        , n(nx, ny, nz)
        , t(u, v)
    {
    }

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};
};
struct VERTEX_RHWC	//w의 역수라는 의미 //w값으로 같은 차원인지 아닌지를 계산하는데, 
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;

	VERTEX_RHWC() {}
	VERTEX_RHWC(D3DXVECTOR4 _p, D3DCOLOR _c)
		:p(_p), c(_c) {}
    VERTEX_RHWC(const float x, const float y, const float z, const float w, 
                const D3DCOLOR c)
        : p(x, y, z, w)
        , c(c)
    {
    }

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};

struct MTLTEX : public BaseObject
{
	D3DMATERIAL9		material;
	LPDIRECT3DTEXTURE9	pTexture;
	int					id;

	MTLTEX() {
		ZeroMemory(&material, sizeof(D3DMATERIAL9));
		pTexture = NULL;}
	
	void SetMaterial(const D3DMATERIAL9 &_material) 
	{material = _material;}
	D3DMATERIAL9 GetMaterial() { return material; }
	void SetTexture(LPDIRECT3DTEXTURE9 _pTexture)
	{pTexture = _pTexture;}
	LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
};

struct ASE_POS_SAMPLE
{
	int			tick;
	D3DXVECTOR3 position;
};

struct ASE_ROT_SAMPLE
{
	int				tick;
	D3DXQUATERNION	quaternion;
};

struct ASE_SCENE
{
	int numFirstFrame;
	int numLastFrame;
	int frameSpeed;
	int ticksPerFrame;
};

struct BoundingSphere
{
	D3DXVECTOR3 center;
	float		radius;
	bool		isPicked;

	BoundingSphere() :isPicked(false) {}
	BoundingSphere(D3DXVECTOR3 _center, float _radius) :center(_center),
		radius(_radius), isPicked(false) {}
};

DWORD FtoDw(float f);

float GetRandomFloat(float lowBound, float highBound);
