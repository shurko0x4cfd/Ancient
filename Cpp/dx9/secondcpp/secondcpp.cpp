// firstcpp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "C:\Root\Soft\Creation\Coding\SDKs\MS\DXSDK\June2010\Include\d3d9.h"
#include "C:\Root\Soft\Creation\Coding\SDKs\MS\DXSDK\June2010\Include\d3dx9.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text







#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL

struct CUSTOMVERTEX
{
float x, y, z;
float nx, ny, nz;
DWORD color;
float tu, tv;
};


int errcode;
HWND myWnd;
void* pVertices = NULL;
void* IndexData = NULL;

DWORD dwNumMaterials = 0;

IDirect3D9* g_pD3D = NULL;
IDirect3DDevice9 *g_pd3dDevice = NULL;
IDirect3DTexture9* g_pTexture = NULL;
ID3DXBuffer* pD3DXMtrlBuffer = NULL;
ID3DXMesh* pMesh = NULL;






D3DXMATRIX g_Transform;
D3DXMATRIX g_Projection;

D3DXMATRIX  g_View;
D3DXVECTOR3 Eye (0.0f, -50.0f, -50.0f);
D3DXVECTOR3 LookAt (0.0f, 0.0f, 0.0f);
D3DXVECTOR3 Up (0.0f, 1.0f, 0.0f);

D3DLIGHT9 Light;


// float WindowWidth = 1920.0f;
// float WindowHeight = 1080.0f;

float WindowWidth  = 800.0f;
float WindowHeight = 800.0f;
float Aspect = WindowWidth / WindowHeight;

float FOV = D3DX_PI / 4;


















// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.


	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SECONDCPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SECONDCPP);









    D3DXMatrixIdentity(&g_Transform);
    D3DXMatrixIdentity(&g_View);
    D3DXMatrixIdentity(&g_Projection);

	D3DXMatrixLookAtLH(&g_View, &Eye, &LookAt, &Up);
	D3DXMatrixPerspectiveFovLH(&g_Projection, FOV, Aspect, 1.0f, 500.0f);


	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(NULL == g_pD3D) return E_FAIL;

	


    D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));

	d3dpp.Windowed = true;
//	d3dpp.Windowed = false;

//  d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;

	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    d3dpp.BackBufferWidth            = 0;
    d3dpp.BackBufferHeight           = 0;
      d3dpp.BackBufferCount            = 1;
      d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
      d3dpp.MultiSampleQuality         = 0;
      d3dpp.Flags                      = 0;
//    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
//    d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;


    ZeroMemory(&Light, sizeof(Light));

	Light.Type = D3DLIGHT_POINT;

	Light.Diffuse.r = 1.0f;
	Light.Diffuse.b = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.a = 0.0f;

    Light.Position.x = -400.0f;
    Light.Position.y = 0.0f;
    Light.Position.z = 100.0f;

    Light.Range = 1000.0f;

	


	errcode = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, myWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);
	if(FAILED(errcode))
	{
//    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, myWnd, (DLGPROC)About);
    //return 0;
	}


    _D3DMATERIAL9 g_Material;
    ZeroMemory(&g_Material, sizeof(D3DMATERIAL9));
    
	g_Material.Diffuse.r=255;
	g_Material.Diffuse.g=255;
	g_Material.Diffuse.b=255;
    g_Material.Diffuse.a=0;

	g_Material.Ambient.r=1;
	g_Material.Ambient.g=1;
	g_Material.Ambient.b=1;
    g_Material.Ambient.a=1;
	
	g_Material.Specular.r=255;
	g_Material.Specular.g=255;
	g_Material.Specular.b=255;
    g_Material.Specular.a=0;	

	g_Material.Emissive.r=0.7f;
	g_Material.Emissive.g=0.7f;
	g_Material.Emissive.b=0.7f;
    g_Material.Emissive.a=0.7f;	

    g_Material.Power = 0;







    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

//    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
//    g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(255, 255, 255, 0));


    g_pd3dDevice->SetLight(0, &Light);
    g_pd3dDevice->LightEnable(0, true);

    errcode = D3DXCreateTextureFromFile(g_pd3dDevice, "hl.bmp", &g_pTexture);
	if(FAILED(errcode))
	{
    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, myWnd, (DLGPROC)About);
    //return 0;
	}

	
// /*
    errcode = D3DXLoadMeshFromX("land.x", D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, NULL, NULL, NULL, &pMesh);
	if(FAILED(errcode))
	{
    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, myWnd, (DLGPROC)About);
    //return 0;
	}
// */
 /*
    errcode = D3DXLoadMeshFromX("plane.x", D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, NULL, NULL, NULL, &pMesh);
	if(FAILED(errcode))
	{
    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, myWnd, (DLGPROC)About);
    //return 0;
	}
 */


	
 /*
    DWORD FVF = pMesh -> GetFVF();
	if(!FVF)
	{
    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, myWnd, (DLGPROC)About);
    //return 0;
	}
 */



	g_pd3dDevice->SetTransform(D3DTS_VIEW, &g_View);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_Transform);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &g_Projection);





    errcode = g_pd3dDevice->BeginScene();
	if(FAILED(errcode))
	{
    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, myWnd, (DLGPROC)About);
    //return 0;
	}

	    g_pd3dDevice->SetMaterial(&g_Material);
		g_pd3dDevice->SetTexture(0, g_pTexture);




        
//		g_pd3dDevice->SetFVF(FVF);

		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

        pMesh -> DrawSubset(0);






    g_pd3dDevice->EndScene();

	
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);




    














	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SECONDCPP);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 600, NULL, NULL, hInstance, NULL);
   
   myWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:

                   pMesh -> Release();
				   g_pTexture->Release();
			       g_pd3dDevice->Release();
                   g_pD3D->Release();

				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
 		// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:

			pMesh -> Release();
			g_pTexture->Release();
		    g_pd3dDevice->Release();
            g_pD3D->Release();

			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}




























//    _D3DMATERIAL9 g_Material;
//    ZeroMemory(&g_Material, sizeof(D3DMATERIAL9));
//    g_Material.Diffuse =  D3DCOLOR_XRGB(255, 255, 255);
//    g_Material.Ambient =  D3DCOLOR_XRGB(255, 255, 255);
//    g_Material.Specular = D3DCOLOR_XRGB(255, 255, 255);
//    g_Material.Emissive = D3DCOLOR_XRGB(255, 255, 255);
//    g_Material.Power = 0;
//	  g_pd3dDevice->SetMaterial(&g_Material);

