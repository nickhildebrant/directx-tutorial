#pragma once
#include <wrl.h>

class GDIPlusManager {
public:
	GDIPlusManager();
	~GDIPlusManager();

private:
	static ULONG_PTR token;
	static int refCount;
};