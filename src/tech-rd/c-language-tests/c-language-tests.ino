
struct StructA {
  byte a;
  byte b;
};

StructA getStructA(int i, StructA b) {
  StructA result;
  result.a = 33 + b.a;
  result.b = i + b.b;

  return result;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);

  StructA b;
  b.a=3;
  b.b=4;

  StructA result = getStructA(15, b);
  Serial.print("result.a :");
  Serial.println(result.a);
  Serial.print("result.b :");
  Serial.println(result.b);
  result = getStructA(17, b);
  Serial.print("result.a :");
  Serial.println(result.a);
  Serial.print("result.b :");
  Serial.println(result.b);
}

void loop() {
  // put your main code here, to run repeatedly:
}
