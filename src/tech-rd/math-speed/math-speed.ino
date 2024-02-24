
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(3000);

  unsigned long count = 0;
  unsigned long startTime = 0;
  unsigned long endTime = 0;
  double result = 0.0f;
  double totResult = 0.0f;

  Serial.print("random()... ");
  for (int i = 0; i < 5; i++) {
    Serial.print(random(1000), DEC);
    Serial.print(" ");
  }
  Serial.println("");

#define absd(x) ((x) > 0.0 ? (x) : -(x))
#define CALCULATING_TIME_SECONDS 5
  float calculatingTimeSeconds = CALCULATING_TIME_SECONDS;




  Serial.print("Start... ");
  Serial.print("none ");
  Serial.print(calculatingTimeSeconds, DEC);
  Serial.println("s");
  count = 0;
  startTime = millis();
  endTime = startTime + calculatingTimeSeconds * 1000;
  result = 0.0f;
  totResult = 0.0f;
  while (millis() < endTime) {
    result += 0.0;
    totResult += result;
    count++;
  }
  Serial.print("Ready: count: ");
  Serial.print(count, DEC);
  Serial.print(" , ");
  Serial.print(((double)count) / ((double)calculatingTimeSeconds), DEC);
  Serial.print(" /s");
  Serial.print(" result :");
  Serial.print(result, DEC);
  Serial.print(" totResult :");
  Serial.print(totResult, DEC);
  Serial.println();
  Serial.println();


  Serial.print("Start... ");
  Serial.print("sin() ");
  Serial.print(calculatingTimeSeconds, DEC);
  Serial.println("s");
  count = 0;
  startTime = millis();
  endTime = startTime + calculatingTimeSeconds * 1000;
  result = 0.0f;
  totResult = 0.0f;
  while (millis() < endTime) {
    result = sin((double)random(1000));
    totResult += result;
    count++;
  }
  Serial.print("Ready: count: ");
  Serial.print(count, DEC);
  Serial.print(" , ");
  Serial.print(((double)count) / ((double)calculatingTimeSeconds), DEC);
  Serial.print(" /s");
  Serial.print(" result :");
  Serial.print(result, DEC);
  Serial.print(" totResult :");
  Serial.print(totResult, DEC);
  Serial.println();
  Serial.println();


  Serial.print("Start... ");
  Serial.print("cos() ");
  Serial.print(calculatingTimeSeconds, DEC);
  Serial.println("s");
  count = 0;
  startTime = millis();
  endTime = startTime + calculatingTimeSeconds * 1000;
  result = 0.0f;
  totResult = 0.0f;
  while (millis() < endTime) {
    result = cos((double)random(1000));
    totResult += result;
    count++;
  }
  Serial.print("Ready: count: ");
  Serial.print(count, DEC);
  Serial.print(" , ");
  Serial.print(((double)count) / ((double)calculatingTimeSeconds), DEC);
  Serial.print(" /s");
  Serial.print(" result :");
  Serial.print(result, DEC);
  Serial.print(" totResult :");
  Serial.print(totResult, DEC);
  Serial.println();
  Serial.println();

  Serial.print("Start... ");
  Serial.print("tan() ");
  Serial.print(calculatingTimeSeconds, DEC);
  Serial.println("s");
  count = 0;
  startTime = millis();
  endTime = startTime + calculatingTimeSeconds * 1000;
  result = 0.0f;
  totResult = 0.0f;
  while (millis() < endTime) {
    result = tan((double)random(1000));
    totResult += result;
    count++;
  }
  Serial.print("Ready: count: ");
  Serial.print(count, DEC);
  Serial.print(" , ");
  Serial.print(((double)count) / ((double)calculatingTimeSeconds), DEC);
  Serial.print(" /s");
  Serial.print(" result :");
  Serial.print(result, DEC);
  Serial.print(" totResult :");
  Serial.print(totResult, DEC);
  Serial.println();
  Serial.println();



  Serial.print("Start... ");
  Serial.print("sqrt() ");
  Serial.print(calculatingTimeSeconds, DEC);
  Serial.println("s");
  count = 0;
  startTime = millis();
  endTime = startTime + calculatingTimeSeconds * 1000;
  result = 0.0f;
  totResult = 0.0f;
  while (millis() < endTime) {
    result = sqrt((double)random(1000));
    totResult += result;
    count++;
  }
  Serial.print("Ready: count: ");
  Serial.print(count, DEC);
  Serial.print(" , ");
  Serial.print(((double)count) / ((double)calculatingTimeSeconds), DEC);
  Serial.print(" /s");
  Serial.print(" result :");
  Serial.print(result, DEC);
  Serial.print(" totResult :");
  Serial.print(totResult, DEC);
  Serial.println();
  Serial.println();


  Serial.print("Start... ");
  Serial.print("complex ");
  Serial.print(calculatingTimeSeconds, DEC);
  Serial.println("s");
  count = 0;
  startTime = millis();
  endTime = startTime + calculatingTimeSeconds * 1000;
  result = 0.0f;
  totResult = 0.0f;
  while (millis() < endTime) {
    double r1 = sin(((double)random(1000)));
    double r2 = cos(((double)random(1000)));
    double r3 = tan(((double)random(1000)));
    result = sqrt(sqrt(r1 * r1) + sqrt(r2 * r2) + sqrt(r3 * r3));
    totResult += result;
    count++;
  }
  Serial.print("Ready: count: ");
  Serial.print(count, DEC);
  Serial.print(" , ");
  Serial.print(((double)count) / ((double)calculatingTimeSeconds), DEC);
  Serial.print(" /s");
  Serial.print(" result :");
  Serial.print(result, DEC);
  Serial.print(" totResult :");
  Serial.print(totResult, DEC);
  Serial.println();
  Serial.println();



  Serial.print("Done. ");
}

void loop() {
  // put your main code here, to run repeatedly:
}
