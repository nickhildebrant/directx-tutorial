#pragma once
#include "ChiliWin.h"
#include <string>
#include <assert.h>
#include <memory>

#include "ExceptionHandler.h"

class Surface {
public:
	class Color {
	public:
		unsigned int dword;

		constexpr Color() noexcept : dword() {}
		
		constexpr Color(const Color& color) noexcept : dword(color.dword) {}

		constexpr Color(unsigned int dw) noexcept : dword(dw) {}
	};

public:
	class Exception : public ExceptionHandler {
	public:
		Exception(int line, const char* file, std::string note) noexcept;

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;

		const std::string& GetNote() const noexcept;

	private:
		std::string note;
	};

public:
	Surface(unsigned int width, unsigned int height) noexcept;
	Surface(Surface&& source) noexcept;
	Surface(Surface&) = delete;

	Surface& operator=(Surface&& donor) noexcept;
	Surface& operator=(const Surface&) = delete;

	~Surface();
	void Clear(Color fillValue) noexcept;

	void PutPixel(unsigned int x, unsigned int y, Color c) noexcept;
	Color GetPixel(unsigned int x, unsigned int y) const noexcept;

	unsigned int GetWidth() const noexcept;
	unsigned int GetHeight() const noexcept;

	Color* GetBufferPtr() noexcept;
	const Color* GetBufferPtr() const noexcept;
	const Color* GetBufferPtrConst() const noexcept;

	static Surface FromFile(const std::string& name);

	void Save(const std::string& filename) const;
	void Copy(const Surface& src) noexcept;

	bool AlphaLoaded() const;

private:
	Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> pBufferParam, bool alphaLoaded = false) noexcept;

private:
	std::unique_ptr<Color[]> pBuffer;

	bool alphaLoaded = false;

	unsigned int width;
	unsigned int height;
};