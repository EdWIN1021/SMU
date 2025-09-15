#pragma comment( lib, "opengl32") 
#include <windows.h>
#include <gl/gl.h>

/* Engine */
#include "Engine/Core/Rgba8.hpp"
#include "Engine/Core/Vertex.hpp"

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Game/GameCommon.hpp"


HGLRC g_openGLRenderingContext = nullptr;


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::Startup()
{
	CreateRenderingContext();
}


void Renderer::Shutdown()
{
}


void Renderer::BeginFrame()
{
}


void Renderer::EndFrame()
{
}


void Renderer::BeginCamera(Camera const& camera)
{
	glLoadIdentity();

	/* arguments are : xLeft, xRight, yBottom, yTop, zNear, zFar */ 
	glOrtho(
		camera.GetOrthoBottomLeft().x,  // left
		camera.GetOrthoTopRight().x,    // right
		camera.GetOrthoBottomLeft().y,  // bottom
		camera.GetOrthoTopRight().y,    // top
		0.f,
		1.f
	);
}


void Renderer::EndCamera(Camera const& camera)
{
}


void Renderer::CreateRenderingContext()
{
	// Creates an OpenGL rendering context (RC) and binds it to the current window's device context (DC)
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset(&pixelFormatDescriptor, 0, sizeof(pixelFormatDescriptor));
	pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cAccumBits = 0;
	pixelFormatDescriptor.cStencilBits = 8;

	HWND windowHandle = ::GetActiveWindow();
	HDC  displayDeviceContext = GetDC( windowHandle );

	int pixelFormatCode = ChoosePixelFormat(displayDeviceContext, &pixelFormatDescriptor);
	SetPixelFormat(displayDeviceContext, pixelFormatCode, &pixelFormatDescriptor);
	g_openGLRenderingContext = wglCreateContext(displayDeviceContext);
	wglMakeCurrent(displayDeviceContext, g_openGLRenderingContext);

	// #SD1ToDo: move all OpenGL functions (including those below) to Renderer.cpp (only!)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Renderer::ClearScreen(Rgba8 const& clearColor)
{
	constexpr float RGB_SCALE = 255.f;
	glClearColor(clearColor.r / RGB_SCALE, clearColor.g / RGB_SCALE, clearColor.b / RGB_SCALE, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::DrawVertexArray(int numVertexes, Vertex const* vertexes)
{
	glBegin(GL_TRIANGLES);
	{
		for (int i = 0; i <  numVertexes; ++ i )
		{
			Vertex vertex = vertexes[i];

			glColor4ub(vertex.m_color.r, vertex.m_color.g, vertex.m_color.b, vertex.m_color.a);
			glTexCoord2f(0.f, 0.f);
			glVertex2f(vertex.m_position.x, vertex.m_position.y);
		}
	}
	glEnd();
}


