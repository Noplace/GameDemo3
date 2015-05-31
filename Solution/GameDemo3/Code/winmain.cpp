/*****************************************************************************************************************
* Copyright (c) 2015 Khalid Ali Al-Kooheji                                                                       *
*                                                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and              *
* associated documentation files (the "Software"), to deal in the Software without restriction, including        *
* without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
* copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the       *
* following conditions:                                                                                          *
*                                                                                                                *
* The above copyright notice and this permission notice shall be included in all copies or substantial           *
* portions of the Software.                                                                                      *
*                                                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT          *
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.          *
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, * DAMAGES OR OTHER LIABILITY,      *
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE            *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                                         *
*****************************************************************************************************************/
#include "gamedemo3.h"


namespace demo {

class Win32App  {
 public:
  Win32App(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pScmdline, int iCmdshow) : apprunning_mutex_(NULL) {
    Initialize();
  }
  virtual ~Win32App() {
    if (apprunning_mutex_)
      CloseHandle(apprunning_mutex_);
  }

  bool Win32App::IsAlreadyRunning(LPCWSTR identifier) {
    apprunning_mutex_ = CreateMutex(NULL,TRUE,identifier);
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
      return true;
    }
    return false;
  }

  void Initialize() {
    lua_State* L;
    L = lua_open();

	  /* load Lua base libraries */
	  luaL_openlibs(L);

	  /* run the script */
	  auto result = luaL_dofile(L, "D:\\Personal\\Projects\\GameDemo3\\Solution\\GameDemo3\\Scripts\\test.lua");

	  /* cleanup Lua */
	  lua_close(L);
  }

  int Run() {
    return 0;
    MSG msg;

    do {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      } else {
        
      }
    } while(msg.message!=WM_QUIT);

    return static_cast<int>(msg.wParam);
  }
 private:
  HANDLE apprunning_mutex_;
  
};

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pScmdline, int iCmdshow) {
  demo::Win32App app(hInstance,hPrevInstance,pScmdline,iCmdshow);
  return app.Run();
}