// --- CONFIGURATION DES CAPTEURS ---
const int NUM_CAPTEURS = 3; // Nombre de capteurs utilisés
const int trigPins[NUM_CAPTEURS] = {2, 4, 6}; // Broches TRIG pour envoyer le signal
const int echoPins[NUM_CAPTEURS] = {3, 5, 7}; // Broches ECHO pour recevoir l'écho
const float DISTANCE_DETECTION = 10.0; // Distance seuil pour détecter une main en cm

// --- INITIALISATION ---
void setup() {
  Serial.begin(9600); // Démarrage du moniteur série
  for (int i = 0; i < NUM_CAPTEURS; i++) {
    pinMode(trigPins[i], OUTPUT); // Configure TRIG en sortie
    pinMode(echoPins[i], INPUT);  // Configure ECHO en entrée
  }
}

// --- DÉMARRER MESURE SIMULTANÉMENT ---
void demarrerMesure() {
  for (int i = 0; i < NUM_CAPTEURS; i++) digitalWrite(trigPins[i], LOW);
  delayMicroseconds(2);
  for (int i = 0; i < NUM_CAPTEURS; i++) digitalWrite(trigPins[i], HIGH);
  delayMicroseconds(10);
  for (int i = 0; i < NUM_CAPTEURS; i++) digitalWrite(trigPins[i], LOW);
}

// --- MESURER LA DISTANCE ---
float mesureDistance(int echoPin) {
  unsigned long duration = pulseIn(echoPin, HIGH, 25000); // Mesure la durée de l'écho
  return duration * 0.034 / 2.0; // Convertit en distance (cm)
}

// --- BOUCLE PRINCIPALE ---
void loop() {
  for (int i = 0; i < NUM_CAPTEURS; i++) {
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    float distance = mesureDistance(echoPins[i]);

    if (distance > 0 && distance < DISTANCE_DETECTION) {
      Serial.print("Carton "); Serial.print(i + 1);
      Serial.println(" pris !");
    } else {
      Serial.print("Capteur "); Serial.print(i + 1);
      Serial.print(" : "); Serial.print(distance);
      Serial.println(" cm");
    }

    delay(50); 
  }

  Serial.println("----------------------------"); 
  delay(500);
}
