#include <windows.h>

// this callback is used by our window to process msgs
LRESULT MainWindowCallback(
	HWND window, // current window instance
	UINT msg, // received msg
	WPARAM wParam, // conditionally filled based on received msg
	LPARAM lParam // conditionally filled based on received msg
) {
	LRESULT result = 0;
	switch(msg) {
		case WM_SIZE: {
			OutputDebugString("WM_SIZE\n");
		} break;
		case WM_DESTROY: {
			OutputDebugString("WM_DESTROY\n");
		} break;
		case WM_CLOSE: {
			OutputDebugString("WM_CLOSE\n");
		} break;
		case WM_ACTIVATEAPP: {
			OutputDebugString("WM_ACTIVATEAPP\n");
		} break;
		case WM_PAINT: {
			OutputDebugString("WM_PAINT\n");
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(window, &Paint);
			
			int x = Paint.rcPaint.left; // x coord corresponds to Paint's rect left
			int y = Paint.rcPaint.top; // y coord corresponds to Paint's rect top
			// to get the width and height of the area to be painted, we subtract:
			int width = Paint.rcPaint.right - x; // right - left = width of paint area
			int height = Paint.rcPaint.bottom - y; // bottom - top = height of paint area
			
			static DWORD operation = WHITENESS;
			operation = operation == WHITENESS ? BLACKNESS : WHITENESS;

			// paint an area using device context with an "operation"
			PatBlt(DeviceContext, x, y, width, height, operation);
			EndPaint(window, &Paint);
		} break;
		default: {
			// OutputDebugStringA("default\n");
			result = DefWindowProc(window, msg, wParam, lParam); // dispatch to windows to handle for us
		} break;
	}
	return result;
}

int WinMain(
	HINSTANCE Instance, // current instance of "app"?
	HINSTANCE PrevInstance, // prev instance
	LPSTR     CmdLine, // command line w/o exe name
	int       ShowCode // fullscreen vs others
) {
	WNDCLASS WindowClass = {}; // zero init a Window Class
	
	WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback; // use above callback for msg handling
	WindowClass.hInstance = Instance; // set the window instance to app instance
	WindowClass.lpszClassName = "HandmadeHeroWindowClass"; // set name for window class

	if (RegisterClass(&WindowClass)) { // if we successfully register our window class,
		// create a window and grab a handle to it
		HWND windowHandle = CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			"Handmade Hero",
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			Instance,
			0
		);

		// if we have a valid handle (successfully made window),
		if (windowHandle) {
			// we can now loop and handle msgs we have received through windows
			for (;;) {
				MSG recvMsg;
				BOOL msgRes = GetMessage(&recvMsg, 0, 0, 0);
				if (msgRes > 0) {
					// translate msg so it can actually be processed
					TranslateMessage(&recvMsg);
					// actually dispatch msg to our msg handling callback
					DispatchMessage(&recvMsg);
				} else break; // exit the for loop
			}
		} else {}
	} else {
		OutputDebugString("Failed to register Window\n");
	}
	return 0;
}