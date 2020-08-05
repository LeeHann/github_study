#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  Sint16 data[5] = {0, };
  for(int i=0; i<5; i++){
    printf("[%2d:%2d] \n", i, data[i]);
  }

  Sint16 data2[] = {1,2,3,4,5,6,7,8};
  
  print("size : %d\n", sizeof(data2) / sizeof(Sint16));

  Sint16 _size = sizeof(data2) / sizeof(Sint16);

  for(int i=0; i<_size; i++){
    printf("[%2d:%2d] \n", i, data[i]);
  }
  
  SDL_Quit();
  return 0;
}