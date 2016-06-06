#include <termios.h>

class TurtlebotInterventionTeleop {
 public:
  TurtlebotInterventionTeleop(int argc, char **argv);

 private:
  struct termios oldt, newt;
  int rotation_speed;
  int move_speed;
};
