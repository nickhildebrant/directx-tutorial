#include "Renderer.h"

Renderer::Renderer(Window& window)
{
	createDevice(window);
	createRenderTarget();
}

void Renderer::createDevice(Window& window)
{
	// Define the swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;	// Double buffering = 1, Triple = 2
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 8-bit Color
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.getHandle();
	swapChainDesc.SampleDesc.Count = 1;	// Anti-Aliasing
	swapChainDesc.Windowed = true;	// Windowed, false = fullscreen

	// Create the swap chain device and device context
	auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION,
		&swapChainDesc, &m_swapChain, &m_device, nullptr, &m_deviceContext);

	// Error handling
	if (result != S_OK)
	{
		MessageBox(nullptr, "Error with DX11", "Error", MB_OK);
		exit(0);
	}
}

void Renderer::createRenderTarget()
{
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->Release();
}

void Renderer::beginFrame()
{
	// Setting the background color
	float clearColor[] = { 0.0f, 0.5f, 0.25f, 1 }; // RGBA
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}

void Renderer::endFrame()
{
	// Swapping buffer
	m_swapChain->Present(1, 0);	// First param is V-sync, second is flag
}