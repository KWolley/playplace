/*
 * Project playplace
 * Description:
 * Author:
 * Date:
 */

SYSTEM_MODE(MANUAL);  

#define CELL_CONNECT_SECONDS 60 // time to attempt to connect to cellular
#define CLOUD_CONNECT_SECONDS 20 // time to attempt to connect cloud
#define CLOUD_WAIT 30

unsigned long connectMillis = CELL_CONNECT_SECONDS * 1000;

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay(1000);
  Serial.println("==== LOOP ====");
  unsigned long startTime = millis();
  Particle.connect();
  if (waitFor(Particle.connected, connectMillis))
  {
    Serial.printlnf("time to connect %lu", millis()-startTime);
    Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
    delay(5000);
    Serial.printlnf("wait 5 Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
    if (Particle.connected())
    {
      Serial.println("turn everything off");
      Particle.disconnect();
      Cellular.disconnect();
      Cellular.off();
      Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
      Particle.process();
    }
  }
  else
  {
    Serial.println("did not connect");
    Serial.printlnf("Cellular = %d. Cloud = %d.",(int)Cellular.ready(), (int)Particle.connected());
  }
  
  
  
  
  
  // int cellConnectTime = connectToCell(CELL_CONNECT_SECONDS);
  // if (cellConnectTime > 0)
  // {
  //   int cloudConnectTime = connectToCloud(CLOUD_CONNECT_SECONDS);
  //   if (cloudConnectTime > 0)
  //   {
  //     String outDat = "cell: " + (String) cellConnectTime + ",  cloud: " + (String) cloudConnectTime;
  //     Particle.publish("connectTime",outDat,PRIVATE);
  //     delay(1000);
  //     Particle.disconnect();
  //     Cellular.disconnect();
  //     Cellular.off();
  //   }
  // }

  deepSleep(60*5);
}

// Sleep ULP way
int deepSleep(int seconds)
{
  if (seconds <= 0)
  {
    seconds = 10;
    Serial.printlnf("Zero sleep time, adjusting to 10 seconds sleep time.");
  }
  Serial.printlnf("Going to sleep for %d minutes %d seconds.", seconds / 60, seconds % 60);
  SystemSleepConfiguration config;
  config.mode(SystemSleepMode::HIBERNATE)
        .duration(seconds * 1000);  // Takes msec
  System.sleep(config);
  return 1;
}

// Sleep ULP way
int ULPSleep(int seconds)
{
  if (seconds <= 0)
  {
    seconds = 10;
    Serial.printlnf("Zero sleep time, adjusting to 10 seconds sleep time.");
  }
  Serial.printlnf("Going to sleep for %d minutes %d seconds.", seconds / 60, seconds % 60);
  SystemSleepConfiguration config;
  config.mode(SystemSleepMode::ULTRA_LOW_POWER)
        .duration(seconds * 1000);  // Takes msec
  System.sleep(config);
  return 1;
}

// Connect to cellular
// Returns 1 if fail, 0 if success. Pass it seconds
int connectToCell(int timeoutSec)
{
  int secondCounter = 0;
  Serial.printf("Connecting to cellular ... ");
  Cellular.on();
  Serial.printf("Cell On");
  Cellular.connect();
  Serial.printf("  - Cell Connect");
  while (Cellular.ready() == false)
  {
    secondCounter ++;
    Serial.printlnf("%i",secondCounter);
    if (secondCounter >= timeoutSec)
    {
      Serial.printlnf("FAILED.  Couldn't connect to cellular.");
      Cellular.off();
      return 0;
      break;
    }
    delay(1000);
  }
  Serial.printlnf("OK.");
  return secondCounter;
}

//
int connectToCloud(int timeoutSec)
{
  Serial.printf("Connecting to cloud ... ");
  int secondCounter = 0;
  Particle.connect();
  while (Particle.connected() == false)
  {
    secondCounter ++;
    Particle.process();
    if (secondCounter >= timeoutSec)
    {
      Serial.printlnf("Couldn't connect to Cloud.");
      Cellular.disconnect();
      Cellular.off();
      return 0;
      break;
    }
    delay(1000);
  }
  Serial.printlnf("OK.");
  return secondCounter;
}