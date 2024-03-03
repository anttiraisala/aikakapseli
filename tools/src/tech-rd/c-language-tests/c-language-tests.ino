
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

StructA f2(StructA a){
  return a;
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


  Serial.println("");
  Serial.println("");


  StructA c;
  c.a=4;
  c.b=5;
  StructA d = f2(c);
  c.a=6;
 Serial.print("c.a :");
  Serial.println(c.a);
 Serial.print("c.b :");
  Serial.println(c.b);
 Serial.print("d.a :");
  Serial.println(d.a);
 Serial.print("d.b :");
  Serial.println(d.b);

}

void loop() {
  // put your main code here, to run repeatedly:
}
