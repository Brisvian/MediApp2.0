#include <WiFi.h>
#include <FirebaseESP32.h>

const char *ssid = "NETBETA1B32_2.4";
const char *password = "EXU5U6TrpE";

// Configura las credenciales de Firebase
#define FIREBASE_HOST "https://mediapp-8b556-default-rtdb.firebaseio.com"

const int ldrPin = 34;

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado a WiFi");

  // Configura el objeto FirebaseConfig
  firebaseConfig.host = FIREBASE_HOST;

  // Inicia Firebase
  if (!Firebase.begin(&firebaseConfig)) {
    Serial.println("Error al iniciar Firebase");
    while (1);
  }

  Serial.println("Firebase iniciado correctamente");
}

void loop() {
  int lightValue = analogRead(ldrPin);
  String status;
  if (lightValue < 3300) {
    status = "Medicamento tomado";
  } else if (lightValue > 3500) {
    status = "Medicamento no tomado";
  } else {
    status = "Estado indeterminado";
  }
  
  // Guarda el estado en Firebase
  if (Firebase.pushString(firebaseData, "/estado_medicamento", status)) {
    Serial.println("Estado enviado a Firebase correctamente");
  } else {
    Serial.println("Error al enviar el estado a Firebase");
  }

  // Espera 3 segundos antes de enviar otro estado
  delay(3000);
}
