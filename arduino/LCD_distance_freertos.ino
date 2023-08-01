/* LCD Distance meters */
/* FREERTOS            */
/* shin jung wook      */


#include <Arduino_FreeRTOS.h>
#include <semphr.h>   // Semaphore를 사용하기 위해
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
 

// 한번에 하나의 Task만 Access 할 수 있도록 LCD를 구성
SemaphoreHandle_t xLCDSemaphore;

void TaskUltraSonicRead(void *pvParameters);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(16,2);


  while(!Serial)
  {
    ;
  }

  if(xLCDSemaphore == NULL)
  {
    xLCDSemaphore = xSemaphoreCreateMutex();
    if( (xLCDSemaphore) != NULL)
    {
      xSemaphoreGive((xLCDSemaphore));
    }
  }

  xTaskCreate(
    TaskUltraSonicRead
    , (const portCHAR *)"UltraSonicRead"
    , 128
    , NULL
    , 2
    , NULL  );
    


    
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskUltraSonicRead( void *pvParameters __attribute__((unused)) )
{
  uint8_t trigPin = 8;
  uint8_t echoPin = 7;

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  for(;;)
  {
    float duration,distance;
    digitalWrite(trigPin,HIGH);
    delay(10);
    digitalWrite(trigPin,LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = ((float)(340*duration) /10000) /2;

    if( xSemaphoreTake( xLCDSemaphore, ( TickType_t ) 5 ) ==pdTRUE) 
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Distance");
      lcd.setCursor(0,1);
      lcd.print(distance);
      lcd.print(" cm ");

      xSemaphoreGive( xLCDSemaphore);
      
    }

    vTaskDelay(1);

    
  }


    
}




