// Feito no simulador TinkerCad
// Link de acesso do projeto: https://www.tinkercad.com/things/ekQtUMFEvWu-sensor-de-estufa/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=tnu7M7kfToBRtVYvyc9jfvTXp9UXXYgUAFmtkEz8GbQ

// C++ code
int temp = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(7, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, OUTPUT);
}

void loop()
{
  temp = (-40 + 0.488155 * (analogRead(A0) - 20));
  if (temp > 30) {
    digitalWrite(7, HIGH);
    if (temp > 50) {
      digitalWrite(LED_BUILTIN, HIGH);
      tone(0, 523, 1000); // play tone 60 (C5 = 523 Hz)
    } else {
      noTone(0);
      digitalWrite(LED_BUILTIN, HIGH);
    }
  } else {
    digitalWrite(7, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}