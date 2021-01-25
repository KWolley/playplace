/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/karaw/Documents/aquarealtime/resdev/software/playplace/src/playplace.ino"
#include "Particle.h"

void setup();
void loop();
#line 3 "c:/Users/karaw/Documents/aquarealtime/resdev/software/playplace/src/playplace.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_TRACE);
#define CELL_CONNECT_SECONDS 60 // time to attempt to connect to cellular
unsigned long connectMillis = CELL_CONNECT_SECONDS * 1000;
int failures = 0;

// setup() runs once, when the device is first turned on.
void setup()
{
  Serial.begin(9600);
  delay(2000);
}
// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  delay(2000);
  Log.info("\n\n==== LOOP ====");
  Log.info("Cellular = %d.Cloud = %d.", (int)Cellular.ready(), (int)Particle.connected());
  unsigned long startTime = millis();
  Particle.connect();
  if (waitFor(Particle.connected, connectMillis))
  {
    if (Particle.connected())
    {
      delay(20000);
    }
  }
  else
  {
    failures++;
  }
  Log.info("total time: %lu, failures: %d", millis() - startTime, failures);
  Particle.disconnect();
  Cellular.disconnect();
  Cellular.off();


  SystemSleepConfiguration config;
  config.mode(SystemSleepMode::HIBERNATE)
      .duration(900000); // 15min
  System.sleep(config);
}


// /*
//  * Project playplace
//  * Description:
//  * Author:
//  * Date:
//  */

// SYSTEM_MODE(SEMI_AUTOMATIC);  
// SYSTEM_THREAD(ENABLED);

// SerialLogHandler logHandler(LOG_LEVEL_INFO);


// #define CELL_CONNECT_SECONDS 60 // time to attempt to connect to cellular
// #define CLOUD_CONNECT_SECONDS 30

// uint sleepTime = 15; // time in minutes to sleep

// unsigned long connectMillis = CELL_CONNECT_SECONDS * 1000;
// int failures = 0;

// // setup() runs once, when the device is first turned on.
// void setup() {
//   Serial.begin(9600);
//   delay(2000);
// }

// // loop() runs over and over again, as quickly as it can execute.
// void loop() {
//   delay(2000);
//   Log.info("\n\n==== LOOP ====");
//   Log.info("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//   unsigned long startTime = millis();

//   Particle.connect();
//   Log.info("particle.connect() called");
//   if (waitFor(Particle.connected, connectMillis))
//   {
//     Log.info("Connected in %lu", millis() - startTime);
//     if (Particle.connected())
//     {
//       Log.info("Chill for 20 seconds");
//       delay(20000);
//       Particle.disconnect();
//       Cellular.disconnect();
//       Cellular.off();
//     }
//   }
//   else
//   {
//     failures++;
//   }
  
//   Log.info("total time: %lu, failures: %d", millis()-startTime, failures);

//   deepSleep(60*15);
//   // SystemSleepConfiguration config;
//   // config.mode(SystemSleepMode::HIBERNATE)
//   //       .duration(900000);  // 15min
//   // System.sleep(config);
// }






// int connectOption(int num, uint startTime)
// {
//   Particle.connect();
//   // Option #1 
//   if (num == 1)
//   {
//     // Cellular.on();
//     // Cellular.connect();
//     // Particle.connect();
//     Serial.println("start while");
//     Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//     while (Particle.connected() == false)
//     {
//       if (millis() - startTime > connectMillis)
//       {
//         Serial.println("did not connect");
//         Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//         failures++;
//         break;
//       }
//     }
//     if (Particle.connected())
//     {
//       Serial.println("chill for 20s");
//       delay(20000);
//       Serial.println("NOW turn everything off");
//       Particle.disconnect();
//       Cellular.disconnect();
//       Cellular.off();
//       Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//       Particle.process();
//     }
//     else
//     {
//       Serial.println("Connection Failed");
//       diconnectAll();
//     }
    
//   }
//   else if (num == 2)
//   {
//     //option #2
//     // Cellular.connect();
//     Serial.println("start wait for");
//     Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//     if (waitFor(Particle.connected, connectMillis))
//     {
//       Serial.printlnf("time to connect %lu", millis()-startTime);
//       Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//       if (Particle.connected())
//       {
//         Serial.println("chill for 20s");
//         delay(20000);
//         Serial.println("NOW turn everything off");
//         diconnectAll();
//       }
//     }
//     else
//     {
//       Serial.println("did not connect");
//       Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//       failures++;
//     }
//   }
//   Serial.printlnf("total time: %lu", millis()-startTime);
//   // Serial.printlnf("Current time = " + Time.format(Time.now(), "%Y-%m-%d %H:%M:%S"));
//   Serial.printlnf("Failures = %i",failures);
//   return 1;
// }

// int diconnectAll()
// {
//   Particle.disconnect();
//   Cellular.disconnect();
//   Cellular.off();
//   Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
//   Particle.process();
//   return 1;
// }
// // Sleep ULP way
// int deepSleep(int seconds)
// {
//   if (seconds <= 0)
//   {
//     seconds = 10;
//     Serial.printlnf("Zero sleep time, adjusting to 10 seconds sleep time.");
//   }
//   Serial.printlnf("Going to sleep for %d minutes %d seconds.", seconds / 60, seconds % 60);
//   SystemSleepConfiguration config;
//   config.mode(SystemSleepMode::HIBERNATE)
//         .duration(seconds * 1000);  // Takes msec
//   System.sleep(config);
//   return 1;
// }

// // Sleep ULP way
// int ULPSleep(int seconds)
// {
//   if (seconds <= 0)
//   {
//     seconds = 10;
//     Serial.printlnf("Zero sleep time, adjusting to 10 seconds sleep time.");
//   }
//   Serial.printlnf("Going to sleep for %d minutes %d seconds.", seconds / 60, seconds % 60);
//   SystemSleepConfiguration config;
//   config.mode(SystemSleepMode::ULTRA_LOW_POWER)
//         .duration(seconds * 1000);  // Takes msec
//   System.sleep(config);
//   return 1;
// }

// // Connect to cellular
// // Returns 1 if fail, 0 if success. Pass it seconds
// int connectToCell(int timeoutSec)
// {
//   int secondCounter = 0;
//   Serial.printf("Connecting to cellular ... ");
//   Cellular.on();
//   Serial.printf("Cell On");
//   Cellular.connect();
//   Serial.printf("  - Cell Connect");
//   while (Cellular.ready() == false)
//   {
//     secondCounter ++;
//     Serial.printlnf("%i",secondCounter);
//     if (secondCounter >= timeoutSec)
//     {
//       Serial.printlnf("FAILED.  Couldn't connect to cellular.");
//       Cellular.off();
//       return 0;
//       break;
//     }
//     delay(1000);
//   }
//   Serial.printlnf("OK.");
//   return secondCounter;
// }

// //
// int connectToCloud(int timeoutSec)
// {
//   Serial.printf("Connecting to cloud ... ");
//   int secondCounter = 0;
//   Particle.connect();
//   while (Particle.connected() == false)
//   {
//     secondCounter ++;
//     Particle.process();
//     if (secondCounter >= timeoutSec)
//     {
//       Serial.printlnf("Couldn't connect to Cloud.");
//       Cellular.disconnect();
//       Cellular.off();
//       return 0;
//       break;
//     }
//     delay(1000);
//   }
//   Serial.printlnf("OK.");
//   return secondCounter;
// }

// // log time to connect to cellular and cloud and publish to cloud if success
// int testCellandPublish()
// {
//   int cellConnectTime = connectToCell(CELL_CONNECT_SECONDS);
//   if (cellConnectTime > 0)
//   {
//     int cloudConnectTime = connectToCloud(CLOUD_CONNECT_SECONDS);
//     if (cloudConnectTime > 0)
//     {
//       String outDat = "cell: " + (String) cellConnectTime + ",  cloud: " + (String) cloudConnectTime;
//       Particle.publish("connectTime",outDat,PRIVATE);
//       delay(2000);
//       Particle.disconnect();
//       Cellular.disconnect();
//       Cellular.off();
//     }
//   }
//   return 1;
// }