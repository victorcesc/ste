#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <XBee.h>

//instalar biblioteca freeRTOS e xbee-arduino

QueueHandle_t xQueue;

XBee xbee = XBee(); // Cria objeto para comunicar com o XBee
 

union{
 uint8_t u8[2];
 uint16_t u16; 
}payload;
// SH + SL: Endereço do XBee que vai receber (coordenador)
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40c04c8a);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload.u8, 2);
ZBTxStatusResponse txStatus = ZBTxStatusResponse();


void vTaskADC(void *pvParameters) //ler do ADC, send to the gatekeeper/ envia o ADC read a cada segundo
{
    int val;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(10000);


    for (;;) {
       val = analogRead(A0);
       xStatus = xQueueSend(xQueue, &val, xTicksToWait);
       vTaskDelay(xTicksToWait);
    }
}

void vTaskKeepAlive(void *pvParameters)// envia 0xffff a cada segundo
{
    int val;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1000);


    for (;;) {
       val = 0xffff;
       xStatus = xQueueSend(xQueue, &val, xTicksToWait);
       vTaskDelay(xTicksToWait);
    }
  
}

void vTaskDequeue(void *pvParameters) // gatekeeper of UART e do Xbee
{
    int val;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1000);

    for (;;) {
        if (xQueueReceive(xQueue, &val, xTicksToWait) == pdPASS){
           payload.u16 = val;
           //Serial.println(val);
           //enviar no xbee
           xbee.send(zbTx);
        }
    }
}

void setup() {
    Serial.begin(9600);
    xbee.setSerial(Serial);
    while (!Serial) ; // wait for serial port to connect

    xQueue = xQueueCreate(5, sizeof(long));

//    xTaskCreate(vTaskADC, "Sender1", 128, (void *) 0,
//                1, // priority
//                NULL);
    xTaskCreate(vTaskKeepAlive, "Sender2", 128, (void *) 0,
                1, // priority
                NULL);
    xTaskCreate(vTaskDequeue, "Receiver", 128, NULL,
                2, // priority
                NULL);
}

void loop() { /* empty */ }
