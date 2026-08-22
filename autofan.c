#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  if (getuid() != 0) {
    printf("\nYou Should Run This Program With SUDO or Root Account\n\n");
    exit(EXIT_FAILURE);
  }
  int target, targetMin, delay, isOn = 0;
  printf("\nAutoFan\n\n");
  printf("Target Temp >");
  scanf("%d", &target);
  printf("OFF Trigger Temp > ");
  scanf("%d", &targetMin);
  printf("Delay (Seconds) > ");
  scanf("%d", &delay);
  printf("\n");
  int cpu, gpu;
  FILE *fp;
  while (1) {
    fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    fscanf(fp, "%d", &cpu);
    fclose(fp);
    cpu = cpu / 1000;
    // CPU COM
    fp = popen("nvidia-smi --query-gpu=temperature.gpu "
               "--format=csv,noheader,nounits 2>/dev/null",
               "r");
    fscanf(fp, "%d", &gpu);
    pclose(fp);
    // GPU COM

    if (cpu >= target || gpu >= target) {
      if (isOn == 0) {
        printf("\nTriggering Fan ON (CPU:%d | GPU:%d)\n", cpu, gpu);
        system("date");
        fp = fopen("/sys/devices/platform/msi-ec/cooler_boost", "w");
        fputs("on", fp);
        fclose(fp);
        isOn = 1;
      }
    } else if (cpu <= targetMin && gpu <= targetMin) {
      if (isOn == 1) {
        printf("\nTriggering Fan OFF (CPU:%d | GPU:%d)\n", cpu, gpu);
        system("date");
        fp = fopen("/sys/devices/platform/msi-ec/cooler_boost", "w");
        fputs("off", fp);
        fclose(fp);
        isOn = 0;
      }
    }

    sleep(delay);
  }
}
