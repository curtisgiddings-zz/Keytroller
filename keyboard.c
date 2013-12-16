#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include "SDL.h"
#include "xdo.h"

//Use xdotool for keyboard triggers
//http://nothingtocode.blogspot.com/2013/07/setting-up-sdl2-in-ubuntu-or-linux-mint.html
// A backspace // R1 & L1 to shift letters
// D Pad for auto-complete
// Joystick depression to move cursor (When center button is pressed switch
//                                     left and right to arrow left & right)

void stick_event_handler(SDL_Event event);
void button_down_handler(SDL_Event event);
void button_up_handler(SDL_Event event);

int A = 0;
int RB = 0;
int LB = 0;
int R3 = 0;
xdo_t* xdo;
int ret = 0;

int main(){
  xdo = xdo_new(NULL);
  if (SDL_Init( SDL_INIT_JOYSTICK ) < 0 ){
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Joystick *stick;
  SDL_JoystickEventState(SDL_ENABLE);
  stick = SDL_JoystickOpen(0);
  SDL_JoystickID stickID = SDL_JoystickInstanceID(stick);
  
  if (SDL_JoystickNumAxes(stick) < 4 ){
    fprintf(stderr, "This keyboard requires at least 4 axes. \n");
    exit(1);
  }

  SDL_Event event;
  SDL_Event ljoyevent;
  SDL_Event lbuttonevent;
  
  for(;;){
    while(SDL_PollEvent(&event)){
      switch(event.type){
        case SDL_JOYAXISMOTION:
        if( (!ljoyevent.type) || (event.jaxis.timestamp - ljoyevent.jaxis.timestamp > 200)){
          if ( ((event.jaxis.value < -20000) || (event.jaxis.value > 20000))){
           stick_event_handler(event); 
           ljoyevent = event;
          }
        }
        break;

        case SDL_JOYBUTTONUP:
        if( (!lbuttonevent.type) || (event.jbutton.timestamp - ljoyevent.jbutton.timestamp > 200)){
          button_up_handler(event);
          lbuttonevent = event;
          printf("Here");
        }
        break;
        case SDL_JOYBUTTONDOWN:
          button_down_handler(event);
        break;
      }
    }
  } 
}

void stick_event_handler(SDL_Event event){
  //Left Stick Horizontal
  if( event.jaxis.axis == 0 ){
    if( event.jaxis.value > 0){
     //Right
     printf("Left Stick Right\n %d", event.jaxis.value);
    }
    if( event.jaxis.value < 0){
    //Left
     printf("Left Stick Left\n");
    }
  }
  //Left Stick Vertial 
  if( event.jaxis.axis == 1 ){
    if( event.jaxis.value > 0){
    //Down
     printf("Left Stick Down\n");
    }
    if( event.jaxis.value < 0){
     //Up
     printf("Left Stick Up\n");
    }
  }
  //Right Stick Horizontal
  if( event.jaxis.axis == 3 ){
    if( event.jaxis.value > 0){
     //Right
     printf("Right Stick Right\n");
    }
    if( event.jaxis.value < 0){
    //Left
     printf("Right Stick Left\n");
    }
  }
  //Right Stick Vertical
  if( event.jaxis.axis == 4 ){
    if( event.jaxis.value > 0){
    //Down
     printf("Right Stick Down\n");
    }
    if( event.jaxis.value < 0){
     //Up
     printf("Right Stick Up\n");
    }
  }
}

void button_down_handler(SDL_Event event){
  switch(event.jbutton.button){
    case 4:
      LB = 1;
    break;
    case 5:
      RB = 1;
    break; case 10:
      R3 = 1;
    break;
    case 0:
  break;
  }
}

void button_up_handler(SDL_Event event){
  switch(event.jbutton.button){
    case 4:
      LB = 0;
    break;
    case 5:
      RB = 0;
    break;
    case 10:
      R3 = 0;
    break;
    case 0:
      printf("Here");
      // xdo_send_keysequence_window_down(xdo, CURRENTWINDOW, "A", 0);
    break;
    case 1:
       xdo_send_keysequence_window_down(xdo, CURRENTWINDOW, "BackSpace", 0);
    break;
  break;
  }
}
