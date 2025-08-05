#include "Screen/PageFlipper.h"

namespace GC {

  class Display {
  public:
    Display();
    ~Display();

    bool FlipPage() { return mFlipper.present(); }
  private:  
    void CleanUp();
  public:
    DisplayState mState;
    PageFlipper mFlipper;
    bool ERROR = false;
  };
}
