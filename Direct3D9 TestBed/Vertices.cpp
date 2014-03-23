//-----------------------------------------------------------------------------
// File: Vertices.cpp
//
// Desc: In this tutorial, we are rendering some vertices. This introduces the
//       concept of the vertex buffer, a Direct3D object used to store
//       vertices. Vertices can be defined any way we want by defining a
//       custom structure and a custom FVF (flexible vertex format). In this
//       tutorial, we are using vertices that are transformed (meaning they
//       are already in 2D window coordinates) and lit (meaning we are not
//       using Direct3D lighting, but are supplying our own colors).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <d3dx9.h>
#include <strsafe.h>
#pragma warning( default : 4996 )

#include "AnimaMathVector3.h"




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices
IDirect3DVertexDeclaration9 *g_pVD = NULL;
IDirect3DIndexBuffer9	*g_pIB = NULL;

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

struct CUSTOMVERTEX2
{
    FLOAT x, y, z;		// The position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)




//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
	d3dpp.BackBufferCount = 1;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	// Turn off culling, so we see the front and back of the triangle
    //g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    //g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT InitVB()
{
	D3DVERTEXELEMENT9 *elements = 0;
	D3DVERTEXELEMENT9 *elementPtr = 0;

	{
		D3DVERTEXELEMENT9 tempElement = { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 };
		elements = (D3DVERTEXELEMENT9 *)malloc(sizeof(D3DVERTEXELEMENT9));
		memcpy(elements, &tempElement, sizeof(D3DVERTEXELEMENT9));
	}

	{
		D3DVERTEXELEMENT9 tempElement = { 0, (sizeof(float) * 3), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 };
		elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * 2);
		elementPtr = elements + 1;
		memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
	}

	{
		D3DVERTEXELEMENT9 tempElement = D3DDECL_END();
		elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * 3);
		elementPtr = elements + 2;
		memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
	}

	g_pd3dDevice->CreateVertexDeclaration(elements, &g_pVD);

	DWORD bufferUsage = D3DUSAGE_WRITEONLY;
	D3DPOOL memoryPool = D3DPOOL_MANAGED;

    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 3 * ((sizeof(float) * 3) + sizeof(DWORD)),
                                                  bufferUsage, 0,
                                                  memoryPool, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

	AE::Math::Vector3 vertexPosition;
	std::vector<AE::Math::Vector3> positions;
	vertexPosition = AE::Math::Vector3(0.0, 2, 5.0); positions.push_back(vertexPosition);
	vertexPosition = AE::Math::Vector3(2, -2, 5.0); positions.push_back(vertexPosition);
	vertexPosition = AE::Math::Vector3(-2, -2, 5.0); positions.push_back(vertexPosition);

	DWORD color = 0xffffffff;
	std::vector<DWORD> diffuseColors;
	diffuseColors.push_back(color);
	diffuseColors.push_back(color);
	diffuseColors.push_back(color);

	unsigned char *pBytes;
	if(!FAILED(g_pVB->Lock(0, positions.size() * 16, (void**)&pBytes, D3DLOCK_DISCARD)))
	{
		unsigned int sizeofFloat = sizeof(float);
		unsigned int sizeOfFloatTimesTwo = sizeofFloat * 2;
		unsigned int sizeOfFloatTimesThree = sizeofFloat * 3;
		unsigned int sizeofColor = sizeof(DWORD);

		for(AE::uint i = 0; i < 3; i++)
		{
			// Position
			memcpy(pBytes, &positions[i].x, sizeOfFloatTimesThree);
			pBytes += sizeOfFloatTimesThree;

			// Diffuse/specular colors
			memcpy(pBytes, &diffuseColors[i], sizeofColor);
			pBytes += sizeofColor;
		}
		g_pVB->Unlock();
	}

	std::vector<AE::ushort> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(2);

	// Allocate memory
	HRESULT result = g_pd3dDevice->CreateIndexBuffer(indices.size(),
				bufferUsage, D3DFMT_INDEX16, memoryPool, &g_pIB, NULL);
	if(result < 0)
		assert(1 && "DX9: unable to create index buffer");

	AE::ushort *pIndices;
	if(!FAILED(g_pIB->Lock(0, indices.size(), (void**)&pIndices, D3DLOCK_DISCARD)))
	{
		for(AE::uint i = 0; i < indices.size(); i++)
			*pIndices++ = indices[i];

		g_pIB->Unlock();
		//g_pIB->GetDesc(&mIndexBufferDesc);
	}

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pVB != NULL )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity( &matWorld );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	/*D3DXVECTOR3 vEyePt   ( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 5.0f );
	D3DXVECTOR3 vUpVec   ( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );*/

	D3DXMATRIXA16 matView;
	D3DXMatrixIdentity( &matView );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );


    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, just one triangle).
        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, 16 );
        //g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
		//g_pd3dDevice->SetFVF(0);
		g_pd3dDevice->SetVertexDeclaration(g_pVD);
        //g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

		g_pd3dDevice->SetIndices(g_pIB);

		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1);

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();
            }
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}
