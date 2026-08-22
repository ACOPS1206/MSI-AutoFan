#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  int target, targetMin, delay, isOn = 0;
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
    fp = popen("cat /sys/class/thermal/thermal_zone0/temp", "r");
    fscanf(fp, "%d", &cpu);
    pclose(fp);
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
        system(
            "echo 'on' | sudo tee /sys/devices/platform/msi-ec/cooler_boost");
        isOn = 1;
      }
    } else if (cpu <= targetMin && gpu <= targetMin) {
      if (isOn == 1) {
        printf("\nTriggering Fan OFF (CPU:%d | GPU:%d)\n", cpu, gpu);
        system("date");
        system(
            "echo 'off' | sudo tee /sys/devices/platform/msi-ec/cooler_boost");
        isOn = 0;
      }
    }

    sleep(delay);
  }
}
