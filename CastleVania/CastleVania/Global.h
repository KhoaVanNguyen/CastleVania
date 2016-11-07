
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//GLOBAL CONSTANT

//view mode(used in contructor of game class)
#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
//
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12
//
//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024

//
//GLOBAL VARIANT
//

extern int G_CurForm;
extern int G_NextForm;

extern bool			G_IsInitedDX;		//check if dx is inited
extern int			G_GameDepth;		//depth in game class (i dont know
extern char*		G_GameName;		//name of game, view in caption
extern int			G_FrameRate;		//frame rate(30 -> 60)
extern int			G_ColorMode;		//color mode to init dx
extern bool			G_IsFullScreen;	//check if windows or fullscreen
extern D3DFORMAT	G_BackBufferFormat;//backbuffer format, used in initing dx

extern bool			G_HasBackgroundSound;		//check if background music is on
extern bool			G_HasEffectSound;	//check if sound effect is on

extern int			G_MapWidth;			//count the tiles in map width, 1 tile 50px
extern int			G_MapHeight;			//count the tiles in map height, 1 tile 50px

extern int			G_ScreenWidth;			//width of game screen
extern int			G_ScreenHeight;			//height of game screen

extern int			G_MaxSize;
extern int			G_MinSize;

extern RECT			G_WindowSize;			//size of game screen

extern HINSTANCE					G_hInstance;		// Handle of the game instance
extern HWND							G_hWnd;			// Handle of the Game Window

extern LPDIRECT3D9					G_DirectX;			//handle dx
extern LPDIRECT3DDEVICE9			G_Device;			//dx device
extern LPDIRECT3DSURFACE9			G_BackBuffer;		//backbuffer

extern LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
extern LPDIRECTINPUTDEVICE8			G_KeyBoard;			// The keyboard device 
extern LPD3DXSPRITE					G_SpriteHandler;	// spriteHandler to draw texture

//GLOBAL METHOD

//write string to a tracing file
void GLTrace(char* format, ...);

//show a message box
void GLMessage(char* text);

//show string to the caption of window
void GLTitle(char* text);



#endif