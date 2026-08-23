#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  if (getuid() != 0) {
    printf("\nYou Should Run This Program With SUDO or Root Account\n\n");
    exit(EXIT_FAILURE);
  }
  char current[4];
  FILE *fp;
  fp = fopen("/sys/devices/platform/msi-ec/cooler_boost", "r");
  fscanf(fp, "%s", &current);
  fclose(fp);
  printf("\nFan Controller\n\nCurrent Fan Status Is: %s", current);
  printf("\nWhat Do You Want To Do?\n1.ON\n2.OFF\n3.View "
         "Command\n\nINPUT > ");
  int in;
  scanf("%d", &in);
  if (in == 1) {
    system("echo 'on' | sudo tee /sys/devices/platform/msi-ec/cooler_boost");
  } else if (in == 2) {
    system("echo 'off' | sudo tee /sys/devices/platform/msi-ec/cooler_boost");
  } else if (in == 3) {
    printf(
        "echo '[on/off]' | sudo tee /sys/devices/platform/msi-ec/cooler_boost");
  } else {
  }
}
