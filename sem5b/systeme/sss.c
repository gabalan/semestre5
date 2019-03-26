#include <unistd.h>

int main() {
  char buf[4];
  while(read(0, buf, 4)) write(1, buf, 4);
  return 0;
}
