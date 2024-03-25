#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <windows.h>
SDL_Window* window{NULL};
SDL_Renderer* renderer{NULL};

HANDLE serialHandle;

serialHandle = CreateFile("\\\\.\\COM6", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

DCB serialParams = {0};
COMMTIMEOUTS timeout = {0};

DWORD baudrate = CBR_9600;
BYTE byteSize = 8;
BYTE stopBits = ONESTOPBIT;
BYTE parity = NOPARITY;

int main(int argc, char* args[]) {
   serialParams.DCBlength = sizeof(serialParams);
   GetCommState(serialHandle, &serialParams);
   serialParams.BaudRate = baudrate;
   serialParams.ByteSize = byteSize;
   serialParams.StopBits = stopBits;
   serialParams.Parity = parity;
   SetCommState(serialHandle, &serialParams);

   timeout.ReadIntervalTimeout = 50;
   timeout.ReadTotalTimeoutConstant = 50;
   timeout.ReadTotalTimeoutMultiplier = 50;
   timeout.WriteTotalTimeoutConstant = 50;
   timeout.WriteTotalTimeoutMultiplier = 10;
   SetCommTimeouts(serialHandle, &timeout);

   if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
   {
      window = SDL_CreateWindow("Angle Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_SHOWN);

      if (window != 0) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   }
   else return 1;

   SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);

   bool quit = false;
   SDL_Event event;

   int x = 1366 / 2, y = 768 - 50;
   float angle = 0;
   while (!quit) {
      while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT)
         {
            quit = true;
            break;
         }
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      SDL_Rect rect = {1366 / 2 - 100, 768 - 100, 200, 100};
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &rect);
      SDL_RenderPresent(renderer);

      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderDrawLine(renderer, x, y, x + 300 * cos((angle+90) * M_PI / 180), y - 300 * sin((angle+90) * M_PI / 180));
      
      SDL_RenderPresent(renderer);
      SDL_Delay(10);
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   CloseHandle(serialHandle);
   return 0;
}
