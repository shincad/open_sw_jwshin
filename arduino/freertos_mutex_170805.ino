#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define MS(x) ((unsigned long)(x)/portTICK_PERIOD_MS)

SemaphoreHandle_t xMutex;

void vPrint(void *);

void setup()
{
  Serial.begin(115200);

  xMutex = xSemaphoreCreateMutex();
  if (NULL != xMutex) {
    xTaskCreate(vPrint, "Printer1", configMINIMAL_STACK_SIZE, (void *)"Printer 1: +++++++++++++++++++++++++++++", 1, NULL);
    xTaskCreate(vPrint, "Printer2", configMINIMAL_STACK_SIZE, (void *)"Printer 2: -----------------------------", 2, NULL);

    vTaskStartScheduler();
  } else {
    Serial.println("Create mutex failed.");
  }
  while (1) ;
}

void loop()
{
}

void vPrint(void *pvParameters)
{
  unsigned char led_state = 0;

  while (1) {
    xSemaphoreTake( xMutex, portMAX_DELAY);       // block forever until the semaphore is given
    // Critical section start
    printer((char *)pvParameters);
    // Critical section end
    xSemaphoreGive( xMutex );
    vTaskDelay(MS(random(500)));
  }
}

void printer(char *p)
{
  while (*p != '\0') {
    Serial.print(*p++);
    delay(1);
  }
  Serial.println(" ");
}
