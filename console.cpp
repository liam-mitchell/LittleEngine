/*
 * palette.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: Danyl
 */


#include "console.h"

/******************************************************************************
  windowsVersionTest

  Checks to see if have Vista/7 or earlier by attempting to retrieve function
  from kernel32.dll that is only available in Vista+ version of Windows.
******************************************************************************/
int windowsVersionTest(void)
{
    /* Retrieving pointers for Windows Vista/7 Functions */
  PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
    GetProcAddress(GetModuleHandle("kernel32.dll"), "GetCurrentConsoleFontEx");

    /* If exists then we have Vita/7 */
  if (pGetCurrentConsoleFontEx)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/******************************************************************************
  SetConsolePalette

  Sets the console palette and font size.
******************************************************************************/
VOID WINAPI SetConsolePalette(COLORREF palette[], int fontX, int fontY, wchar_t *fontName)
{
  int i;
  HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Retrieving pointers for Windows Vista/7 Functions */
  PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
    GetProcAddress(GetModuleHandle("kernel32.dll"), "GetCurrentConsoleFontEx");
  PSetCurrentConsoleFontEx pSetCurrentConsoleFontEx = (PSetCurrentConsoleFontEx)
    GetProcAddress(GetModuleHandle("kernel32.dll"), "SetCurrentConsoleFontEx");
  PGetConsoleScreenBufferInfoEx pGetConsoleScreenBufferInfoEx = (PGetConsoleScreenBufferInfoEx)
    GetProcAddress(GetModuleHandle("kernel32.dll"), "GetConsoleScreenBufferInfoEx");
  PSetConsoleScreenBufferInfoEx pSetConsoleScreenBufferInfoEx = (PSetConsoleScreenBufferInfoEx)
    GetProcAddress(GetModuleHandle("kernel32.dll"), "SetConsoleScreenBufferInfoEx");

    /* Check for pointers: if they exist, we have Vista/7 and we can use them */
  if (pGetCurrentConsoleFontEx && pSetCurrentConsoleFontEx &&
      pGetConsoleScreenBufferInfoEx && pSetConsoleScreenBufferInfoEx)
  {
    CONSOLE_SCREEN_BUFFER_INFOEX cbi;
    CONSOLE_FONT_INFOEX cfi = {sizeof(CONSOLE_FONT_INFOEX)};

      /* Tell the font info how big it is, to avoid memory corruption */
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    pGetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

      /* Set the font type to name indicated by wide string literal */
      /* Set to 0 to keep current settings */
    lstrcpyW(cfi.FaceName, fontName);
    cfi.dwFontSize.X = fontX;
    cfi.dwFontSize.Y = fontY;
    cfi.FontFamily = 0; /* Set to 0x30 for Terminal font */
    cfi.FontWeight = 0;

    PSetCurrentConsoleFontEx pSetCurrentConsoleFontEx = (PSetCurrentConsoleFontEx)
      GetProcAddress(GetModuleHandle("kernel32.dll"), "SetCurrentConsoleFontEx");
    PGetConsoleScreenBufferInfoEx pGetConsoleScreenBufferInfoEx = (PGetConsoleScreenBufferInfoEx)
      GetProcAddress(GetModuleHandle("kernel32.dll"), "GetConsoleScreenBufferInfoEx");
    PSetConsoleScreenBufferInfoEx pSetConsoleScreenBufferInfoEx = (PSetConsoleScreenBufferInfoEx)
      GetProcAddress(GetModuleHandle("kernel32.dll"), "SetConsoleScreenBufferInfoEx");

      /* Set the console font info */
    pSetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

      /* Get the size of the structure before filling the struct */
    cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    pGetConsoleScreenBufferInfoEx(hOutput, &cbi);

      /* Loop through the given palette, copying the data into the color table */
    for (i = 0 ; i < 16 ; ++i)
    {
      cbi.ColorTable[i] = palette[i];
    }

      /* Set the console screen buffer info */
    pSetConsoleScreenBufferInfoEx(hOutput, &cbi);
  }
  else  /* We don't have access to the vista functions */
  {
    int i;
    CONSOLE_INFO ci = { sizeof(ci) };
    HWND hwndConsole = GetConsoleWindow();

    GetConsoleSizeInfo(&ci, hOutput);

      /* Set to 0 to keep current settings */
    ci.FontSize.X = fontX;
    ci.FontSize.Y = fontY;
    ci.FontFamily = 0; /* Set to 0x30 for Terminal font */
    ci.FontWeight = 0;

    lstrcpyW(ci.FaceName, fontName);
    ci.CursorSize = 100;
    ci.FullScreen = FALSE;
    ci.QuickEdit = FALSE;
    ci.AutoPosition = 0x10000;
    ci.InsertMode = TRUE;
    ci.ScreenColors = MAKEWORD(0x7, 0x0);
    ci.PopupColors = MAKEWORD(0x5, 0xf);
    ci.HistoryNoDup = TRUE;
    ci.HistoryBufferSize = 50;
    ci.NumberOfHistoryBuffers = 4;

    for(i = 0; i < 16; i++)
    {
      ci.ColorTable[i] = palette[i];
    }

    ci.CodePage = 0;
    ci.Hwnd = hwndConsole;
    lstrcpyW(ci.ConsoleTitle, L"");

    SetConsoleInfo(hwndConsole, &ci);
  }
}

/******************************************************************************
  GetConsoleSizeInfo (XP only)

  Fills up some info about the console font in the CONSOLE_INFO struct.
******************************************************************************/
static void GetConsoleSizeInfo(CONSOLE_INFO *pci, HANDLE hOutput)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(hOutput, &csbi);
  pci->ScreenBufferSize = csbi.dwSize;
  pci->WindowSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  pci->WindowSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  pci->WindowPosX = csbi.srWindow.Left;
  pci->WindowPosY = csbi.srWindow.Top;
}

/******************************************************************************
  SetConsoleInfo (XP only)

  Ends up sending a message to windows to reset the console info.
******************************************************************************/
BOOL SetConsoleInfo(HWND hwndConsole, CONSOLE_INFO *pci)
{
  DWORD dwConsoleOwnerPid;
  HANDLE hProcess;
  HANDLE hSection, hDupSection;
  PVOID ptrView = 0;
  HANDLE hThread;

  /* Open the process which "owns" the console */
  GetWindowThreadProcessId(hwndConsole, &dwConsoleOwnerPid);
  hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwConsoleOwnerPid);


  /* Create a SECTION object backed by page-file, then map a view of  */
  /* this section into the owner process so we can write the contents  */
  /* of the CONSOLE_INFO buffer into it  */
  hSection = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, pci->Length, 0);


  /* Copy our console structure into the section-object */
  ptrView = MapViewOfFile(hSection, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, pci->Length);
  memcpy(ptrView, pci, pci->Length);
  UnmapViewOfFile(ptrView);


  /* Map the memory into owner process  */
  DuplicateHandle(GetCurrentProcess(), hSection, hProcess, &hDupSection, 0, FALSE, DUPLICATE_SAME_ACCESS);

  /* Send console window the "update" message WM_SETCONSOLEINFO */
  SendMessage(hwndConsole, WM_SETCONSOLEINFO, (WPARAM)hDupSection, 0);

  /*clean up */
  hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)CloseHandle, hDupSection, 0, 0);
  CloseHandle(hThread);
  CloseHandle(hSection);
  CloseHandle(hProcess);
  return TRUE;
}

/***************************************************************************
 * bound_check
 *
 * ensures that variables x and y are within the boundaries of the console window,
 * and changes them to be so if they are not
 ***************************************************************************/

void bound_check(int &x, int &y, Image *image) {
	if (x < 0)
		x = 0;
	if (x > WIDTH - image->getWidth())
		x = WIDTH - image->getWidth();
	if (y < 0)
		y = 0;
	if (y > HEIGHT - image->getHeight())
		y = HEIGHT - image->getHeight();
}

/***************************************************************************
 * initializeConsole
 *
 * sets console's title, font size and font name, as well as setting the palette
 * to the values of palette in the function - defaults to Windows default RGB,
 * search MSDN for RGB macros to learn more about changing these values
 *
 * note - also initializes default background to blue, use any of the provided
 * palette values or FOREGROUND_RED || FOREGROUND_GREEN || FOREGROUND_BLUE to change
 ***************************************************************************/

void initializeConsole(char *title, int fontX, int fontY, wchar_t *fontName) {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	COLORREF palette[16] =
		  {
				0x00000000, 0x00800000, 0x00008000, 0x00808000,
				0x00000080, 0x00800080, 0x00008080, 0x00c0c0c0,
				0x00808080, 0x00ff0000, 0x0000ff00, 0x00ffff00,
				0x000000ff, 0x00ff00ff, 0x0000ffff, 0x00ffffff
		  };

	SetConsoleTitle(title);
	SetConsolePalette(palette, fontX, fontY, fontName);

	COORD bufferSize = {WIDTH, HEIGHT};
	SMALL_RECT windowSize = {0, 0, WIDTH - 1, HEIGHT - 1};

	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			consoleBuffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)219;
			consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE;
		}
	}

}

COORD characterBufferSize = {WIDTH, HEIGHT};
COORD characterPosition = {0, 0};
SMALL_RECT consoleWriteArea = {0, 0, WIDTH - 1, HEIGHT - 1};
