#include "Screen/Display.h"

Display::Display() : mFlipper(mState) {

  mState.drm_fd = open("/dev/dri/card1", O_RDWR | O_CLOEXEC);
  if (mState.drm_fd < 0) {
    
  }
}

Display::~Display() {
  CleanUp();
}

void Display::CleanUp() {
  
}
