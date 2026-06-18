/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (c) 2020 Fernando Mercês
  *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <Windows.h>
#include <stdio.h>

int running = false; // menteb.in/apoie
DWORD tid = 0;
HANDLE thread;


void mouse_click(void) {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
    int* r = (int*)lpParam;
    while (*r) {
        mouse_click();
        Sleep(100);
    }
    return 0;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    bool fEatKeyStroke = false;

    if (nCode == HC_ACTION) {
        switch (wParam) {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
            if (fEatKeyStroke = (p->vkCode == VK_F6)) {
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {

                    if (running == 0) {
                        printf("Autoclicker started. Press F6 to stop it.\n");
                        running = 1;
                        thread = CreateThread(NULL, 0, MyThreadFunction, &running, 0, &tid);
                    }
                    else {
                        running = 0;
                        CloseHandle(thread);
                        printf("Autoclicker stopped.\n");
                    }
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    // nothing
                }
                break;
            }
            break;
        }
    }

    return (fEatKeyStroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}


int main(void)
{
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    MSG msg;

    while (!GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hhkLowLevelKybd);
    return 0;
}