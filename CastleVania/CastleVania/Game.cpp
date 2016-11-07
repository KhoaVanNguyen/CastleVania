#include <windows.h>
#include "Game.h"
#include <d3d9.h>

CGame::CGame(int _nnCmdShow)
{
	nCmdShow = _nnCmdShow;
}

int CGame::InitWindow(int nCmdShow) 
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = G_hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = G_GameName;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	int windowStyle;
	if(G_IsFullScreen) {
		windowStyle = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; //dạng fullscreen
	} else {
		windowStyle = WS_OVERLAPPEDWINDOW; //dạng cửa sổ
	}

	G_hWnd = 
		CreateWindow(
		G_GameName,
		G_GameName,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		G_ScreenWidth,
		G_ScreenHeight,
		NULL,
		NULL,
		G_hInstance,
		NULL);

	if (!G_hWnd) { 
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(G_hWnd, nCmdShow);
	UpdateWindow(G_hWnd);
}


int CGame::InitDirectX() 
{
	G_DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp; 

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	if(G_IsFullScreen) {
		d3dpp.Windowed   = FALSE;
	} else {
		d3dpp.Windowed   = TRUE;
	}
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = G_ScreenHeight;
	d3dpp.BackBufferWidth = G_ScreenWidth;

	G_DirectX->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		G_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&G_Device);

	if (G_Device==NULL) 
	{
		return 0;
	}

	//backbuffer
	G_Device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&G_BackBuffer);

	//sprite handler
	D3DXCreateSprite(G_Device, &G_SpriteHandler);

	return 1;
}

void CGame::InitKeyboard()
{
    HRESULT 
		hr = DirectInput8Create
			( 
				GetModuleHandle(NULL), 
				DIRECTINPUT_VERSION, 
				IID_IDirectInput8, (VOID**)&G_DirectInput, NULL 
			);

	// TO-DO: put in exception handling
	if (FAILED(hr)==true)
		return;
	
	hr = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL); 
	
	// TO-DO: put in exception handling
	if (FAILED(hr)==true) 
		return;

	hr = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)==true) 
		return;

	hr = G_KeyBoard->SetCooperativeLevel(G_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	if (FAILED(hr)==true) 
		return;

    DIPROPDWORD dipdw;

    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = GL_KEY_BUFFER_SIZE;

    hr = G_KeyBoard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (FAILED(hr)==true) 
		return;

	hr = G_KeyBoard->Acquire(); 
	if (FAILED(hr)==true) 
		return;
}

void CGame::InitGame()
{
	InitWindow(nCmdShow);
	InitDirectX();
	InitKeyboard();
	LoadResources(G_Device);
}

void CGame::ProcessKeyBoard()
{
		HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		if(hr != S_OK)
		{
			hr = G_KeyBoard->Acquire();
			G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		}
		// Collect all key states first
		G_KeyBoard->GetDeviceState( sizeof(_KeyStates), _KeyStates);

		if (IsKeyDown(DIK_ESCAPE)) 
		{
			PostMessage(G_hWnd,WM_QUIT,0,0);
		}

		// Collect all buffered events
		DWORD dwElements = GL_KEY_BUFFER_SIZE;
		hr = G_KeyBoard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0 );

		// Scan through all data, check if the key is pressed or released
		for( DWORD i = 0; i < dwElements; i++ ) 
		{
			int KeyCode = _KeyEvents[i].dwOfs;
			int KeyState = _KeyEvents[i].dwData;
			if ( (KeyState & 0x80) > 0)
				OnKeyDown(KeyCode);
			else 
				OnKeyUp(KeyCode);
		}
}

void CGame::OnKeyUp(int KeyCode) { }
void CGame::OnKeyDown(int KeyCode) { }

void GameDraw(int deltaTime)
{
	if (G_Device->BeginScene()) 
	{
		// Clear back buffer with BLACK
		G_Device->ColorFill(G_BackBuffer,NULL,D3DCOLOR_XRGB(0,0,0));
		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//----- start drawing


		//---- end drawing
		G_SpriteHandler->End();
		G_Device->EndScene();
	}

	G_Device->Present(NULL,NULL,NULL,NULL);
}

// Main game message loop
void CGame::GameRun()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;
	
	DWORD tick_per_frame = 100 / G_FrameRate;

	while (!done) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT) done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		DWORD now = GetTickCount();
		_DeltaTime = now - frame_start; 
		if (_DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			RenderFrame();
		}

		ProcessKeyBoard();

		ProcessInput(G_Device, _DeltaTime);
	}
}

void CGame::RenderFrame()
{
	if (G_Device->BeginScene()) 
	{
		RenderFrame(G_Device, _DeltaTime);
		G_Device->EndScene();
	}
	G_Device->Present(NULL,NULL,NULL,NULL);
}

void CGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta) 
{
	d3ddv->ColorFill(G_BackBuffer,NULL,D3DCOLOR_XRGB(0,0,0));
}
void CGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) { }

void CGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta) 
{
	/*HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		if(hr != S_OK)
		{
			hr = G_KeyBoard->Acquire();
			G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		}*/
}

int CGame::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

void CGame::GameEnd()
{
	if (G_Device!=NULL) G_Device->Release();
	if (G_DirectX!=NULL) G_DirectX->Release();
}

LRESULT CALLBACK CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hWnd, message, wParam,lParam);
	}
	return 0;
}
