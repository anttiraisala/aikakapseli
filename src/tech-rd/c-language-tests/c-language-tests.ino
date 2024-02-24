
struct StructA {
  byte a;
  byte b;
};

StructA getStructA(int i) {
  StructA result;
  result.a = 33;
  result.b = i;

  return result;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  StructA result = getStructA(15);
  Serial.print("result.a :");
  Serial.println(result.a);
  Serial.print("result.b :");
  Serial.println(result.b);
  result = getStructA(17);
  Serial.print("result.a :");
  Serial.println(result.a);
  Serial.print("result.b :");
  Serial.println(result.b);
}

void loop() {
  // put your main code here, to run repeatedly:
}
