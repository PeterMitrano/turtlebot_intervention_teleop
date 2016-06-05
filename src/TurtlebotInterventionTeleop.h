#include <termios.h>

class TurtlebotInterventionTeleop {

public:
  TurtlebotInterventionTeleop(int argc, char **argv);

private:
  struct termios t;
};
