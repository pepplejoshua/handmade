#include <windows.h>

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {
	MessageBoxA(0, "This is Handmade Hero.", "Handmade Hero", MB_OK|MB_ICONINFORMATION);
	return 0;
}