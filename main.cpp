#include <Windows.h>

LRESULT CALLBACK KBDHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *s = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

	switch (wParam) {
		case WM_KEYDOWN:
			if (s->vkCode == 91) // left windows button
				return 1;
			break;
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
	HHOOK kbd = SetWindowsHookEx(WH_KEYBOARD_LL, &KBDHook, 0, 0);

	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(kbd);

	return 0;
}
