#pragma once
#include <Windows.h>
/*
/ ERSTE GEH VERSUCHE IN VC++ WINAPI 22.02.2020
/ Copyright (c) 2020 
/ CODE Verstehn zwischen API und GUI sowie daten auslesen oder schreiben in GUI oder Variabeln
*/

//FLAT STYLE WIN10 :-)))))
#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")
#pragma comment(lib, "ComCtl32.lib")




//WINMAIN SCHLEIFE
BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
//DIALOG SCHLEIFE
HINSTANCE	hInst;
BOOL CALLBACK AddDialogProc(HWND, UINT, WPARAM, LPARAM);
//COMBOBOX Behandlung
HWND cbs = NULL;
// BITMAP AUF BUTTON
HBITMAP HBMP;
//COmbobox Daten Füller
const char *cbs_add[] = { "One - 1","Two - 2","Three - 3" };



void opendlg(HWND hwnd) {

	//EDITBOX
	HWND edit = NULL;

	//CONST FILEOPENDIALOG AUS DER MSDN MICROSFT :-))
	OPENFILENAME  ofn;       // common dialog box structure
	TCHAR szFile[260] = { 0 };       // if using TCHAR macros
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ("All\0*.*\0Executable\0*.exe\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		// use ofn.lpstrFile
		//HOL über das HWND die EDIT BOX
		edit = GetDlgItem(hwnd, IDC_EDIT1);
		//SENDMESSAGE SETZE TEXT REIN 
		SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)TEXT(ofn.lpstrFile));

	}
}

void ABOUT_DLG(HWND hwnd) {

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AddDialogProc);

}
