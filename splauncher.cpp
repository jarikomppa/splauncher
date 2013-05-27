#include <windows.h>
#include <process.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    if (strlen(lpCmdLine) < 1)
    {
        MessageBox(NULL,"Usage:\nsplauncher commandline\n\nCreates a new process and attempts to change its processor affinity to only use the first CPU found.","Single-Processor Launcher",MB_OK);
        return 0;
    }

    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    memset(&si,0,sizeof(STARTUPINFO));
    CreateProcess(NULL,lpCmdLine,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);

    if (SetProcessAffinityMask(pi.hProcess,1)==0)
    {
        MessageBox(NULL,"SetProcessAffinityMask failed.\nProcessor affinity not changed.","Single-Processor Launcher",MB_OK);
        return 0;
    }

    return 0;
}
