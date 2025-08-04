#include "Screen/PageFlipper.h"

class Display {
public:
  Display();
  ~Display();
  void CleanUp();

private:
  DisplayState mState;
  PageFlipper mFlipper;
};
