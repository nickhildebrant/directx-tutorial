#pragma once
#include <Windows.h>
#include "ExceptionHandler.h"
#include "Keyboard.h"

class Window {
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	int getWidth();
	int getHeight();
	HWND getHandle();

	Keyboard keyboard;

	class Exception : public ExceptionHandler {
	public:
		Exception(int line, const char* file, HRESULT hresult) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hresult) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;

	private:
		HRESULT m_hresult;
	};

private:
	int m_width, m_height;
	HWND m_handle;

	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Singleton for window management
	class WindowClass {
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();

	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Direct3D Rendering Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
};

// macro to send exceptions
#define HWND_EXCEPT(m_hresult) Window::Exception(__LINE__, __FILE__, m_hresult)
#define HWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())