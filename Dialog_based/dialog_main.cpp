#include <Windows.h>
#include <commapi.h>
#include <CommCtrl.h>
#include <string.h>
#include "resource.h"
#include "dialog_based.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND dialog{};
	
	//InitCommonControls();

	// DAMIT DIE FORM SCHÖN AUSSIEHT :-))
	INITCOMMONCONTROLSEX WIN_STYLE;
	WIN_STYLE.dwSize = sizeof(INITCOMMONCONTROLSEX);
	WIN_STYLE.dwICC = ICC_BAR_CLASSES | ICC_COOL_CLASSES | ICC_USEREX_CLASSES;
	InitCommonControlsEx(&WIN_STYLE);

	dialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_BASE), NULL, DialogProc);

	if (!dialog) {
		MessageBox(NULL, "Kann Dialog aus Resource nicht Laden", "CreateDialog...", MB_OK);
		return 1;
	}


	ShowWindow(dialog, nCmdShow);
	UpdateWindow(dialog);

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}



BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
					
		case WM_CREATE:		

			break;
		
		case WM_INITDIALOG:
					
			//ICON SETZEN 

			HICON hIcon;
			hIcon = (HICON)LoadImage(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_MAIN),
				IMAGE_ICON,
				GetSystemMetrics(SM_CXSMICON),
				GetSystemMetrics(SM_CYSMICON),
				0);
			if (hIcon)
			{
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			}

			
			// Holen das Handle vom Dialog "HWND" und Greifen auf die Combobox ID ZU
			cbs = GetDlgItem(hwnd, IDC_CBS1);

			//in Combobox Eintragen 
			for (int i = 0; i < 3; i++) {

				SendMessage(cbs, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)cbs_add[i]));
			}

			//BUTTON ICON TEST
			HICON test;
			
			test = (HICON)LoadImage(GetModuleHandle(0), 
						  MAKEINTRESOURCE(IDB_BITMAP1), 
						  IMAGE_ICON, 
						  GetSystemMetrics(SM_CXSMICON), 
						  GetSystemMetrics(SM_CYSMICON),
						  0);
			//SETZE
			SendMessage(GetDlgItem(hwnd, IDC_ABOUT), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)test);

			break;		

		case WM_COMMAND:

			switch (LOWORD(wParam))
			{
				case IDC_ABOUT:

					MessageBoxA(hwnd, "Eine AboutBox", "MessageBox", MB_ICONINFORMATION);

				break;

				case ID_DATEI_BEENDEN:
					if (MessageBox(hwnd, TEXT("Exit das Programm?"), TEXT("Beenden"), MB_ICONQUESTION | MB_YESNO) == IDYES)						
						{
							DestroyWindow(hwnd);
						}
				break;

				case IDC_DLGOPEN1:

						opendlg(hwnd);
			
				break;

				case IDC_OPENDLG2:
					//LADE ABOUT_DLG mit übergabe Handle
						ABOUT_DLG(hwnd);
				
				break;
			}		
		
		case WM_CLOSE:

		/*	if (MessageBox(hwnd, TEXT("Exit das Programm?"), TEXT("Beenden"), MB_ICONQUESTION | MB_YESNO) == IDYES)
			
			{
				DestroyWindow(hwnd);
			}
			
			return 0;
			*/
			break;

		case WM_DESTROY:

			PostQuitMessage(0);
			break;

	}
	return false;
}

//Messageschleife zu About_dlg Form
BOOL CALLBACK AddDialogProc(HWND hInst, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND Text_1 = NULL;

	const char text_c[] = "Das ist ein Text";
	switch (uMsg)
	{
	case WM_INITDIALOG:
		Text_1 = GetDlgItem(hInst, IDC_TEXT1);
		SendMessage(Text_1, WM_SETTEXT, NULL, (LPARAM)TEXT(text_c));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDABORT:
			EndDialog(hInst, 0);
			break;
		}
	case WM_CLOSE:
		EndDialog(hInst, 0);
		break;
	}
	return FALSE;
}


