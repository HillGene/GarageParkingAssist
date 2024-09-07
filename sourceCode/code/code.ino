void loop() {
  rrss();
  rusmf();
  rusms();

  if (reedActive == 0) {
    if (distanceF <= redF) {
      digitalWrite(redLightF, HIGH);
      digitalWrite(yellowLightF, LOW);
      digitalWrite(greenLightF, LOW);
            Serial.print("DistanceF: ");
  Serial.println(distanceF);
    } else if (distanceF > redF && distanceF <= yellowF) {
      digitalWrite(redLightF, LOW);
      digitalWrite(yellowLightF, HIGH);
      digitalWrite(greenLightF, LOW);
            Serial.print("DistanceF: ");
  Serial.println(distanceF);
    } else {
      digitalWrite(redLightF, LOW);
      digitalWrite(yellowLightF, LOW);
      digitalWrite(greenLightF, HIGH);
            Serial.print("DistanceF: ");
  Serial.println(distanceF);
    }

    if (distanceS <= redS) {
      while (distanceS <= redS) {
        digitalWrite(redLightS, HIGH);
        digitalWrite(yellowLightS, LOW);
        digitalWrite(greenLightS, LOW);
        delay(100);
        digitalWrite(redLightS, LOW);
        digitalWrite(yellowLightS, LOW);
        digitalWrite(greenLightS, LOW);
        delay(100);
        rusms();
      }
    }
  } else {
    digitalWrite(redLightF, LOW);
    digitalWrite(yellowLightF, LOW);
    digitalWrite(greenLightF, LOW);
  }  //end of if reedAcitve
}  //end of void loop

