#include "Screen/PageFlipper.h"

namespace GC {

  class Display {
  public:
    static bool Init();
    static void Shutdown();

    static bool FlipPage() { return mFlipper.present(); }
  public:
    static DisplayState mState;
    static PageFlipper mFlipper;
  };
}
