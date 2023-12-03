#ifndef _INPUT_H
#define _INPUT_H

#include <stdlib.h>
#include <wchar.h>

#define WIN32_NO_STATUS
#include <windef.h>
#include <winbase.h>
#include <winnls.h>
#include <winreg.h>
#include <winuser.h>
#include <wingdi.h>
#include <commctrl.h>
#include <windowsx.h>
#include <setupapi.h>
#include <strsafe.h>
#include <cpl.h>

#include "resource.h"

typedef struct
{
    int idIcon;
    int idName;
    int idDescription;
    APPLET_PROC AppletProc;
} APPLET, *PAPPLET;

extern HINSTANCE hApplet;
extern BOOL g_bRebootNeeded;

// Character Count of a layout ID like "00000409"
#define CCH_LAYOUT_ID    8

// Maximum Character Count of a ULONG in decimal
#define CCH_ULONG_DEC    10

#define MAX_STR_LEN      256

/* settings_page.c */
INT_PTR CALLBACK
SettingsPageProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL EnableProcessPrivileges(LPCWSTR lpPrivilegeName, BOOL bEnable);

/* advanced_settings_page.c */
INT_PTR CALLBACK
AdvancedSettingsPageProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* add_dialog.c */
INT_PTR CALLBACK
AddDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

/* edit_dialog.c */
INT_PTR CALLBACK
EditDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* key_settings_dialog.c */

typedef struct
{
    DWORD dwAttributes;
    DWORD dwLanguage;
    DWORD dwLayout;
} KEY_SETTINGS;

INT_PTR CALLBACK
KeySettingsDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

DWORD
ReadAttributes(VOID);

/* key_sequence_dialog.c */
INT_PTR CALLBACK
ChangeKeySeqDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


static inline DWORD
DWORDfromString(const WCHAR *pszString)
{
    WCHAR *pszEnd;

    return wcstoul(pszString, &pszEnd, 16);
}

#define IME_MASK        (0xE0000000UL)
#define SUBST_MASK      (0xD0000000UL)
#define SPECIAL_MASK    (0xF0000000UL)

#define IS_IME_HKL(hKL)             ((((ULONG_PTR)(hKL)) & 0xF0000000) == IME_MASK)
#define IS_SPECIAL_HKL(hKL)         ((((ULONG_PTR)(hKL)) & 0xF0000000) == SPECIAL_MASK)
#define SPECIALIDFROMHKL(hKL)       ((WORD)(HIWORD(hKL) & 0x0FFF))

#define IS_IME_KLID(dwKLID)         ((((ULONG)(dwKLID)) & 0xF0000000) == IME_MASK)
#define IS_SUBST_KLID(dwKLID)       ((((ULONG)(dwKLID)) & 0xF0000000) == SUBST_MASK)

VOID GetSystemLibraryPath(LPWSTR pszPath, INT cchPath, LPCWSTR pszFileName);

#endif /* _INPUT_H */
