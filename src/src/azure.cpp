// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <PubSubClient.h>

// const char* ssid = "Dom210A";
// const char* password = "721469827";
// const char* iothubHost = "your-hub.azure-devices.net";
// const char* deviceId = "Environment-monitoring";
// const char* deviceKey = "your-device-key";

// WiFiClientSecure wifiClient;
// PubSubClient mqtt(wifiClient);

// String createSasToken() {
//   // generate SAS token using deviceKey, hostname, and expiry
//   // use HMAC-SHA256 and Base64 encode
// }

// void connectIoTHub() {
//   mqtt.setServer(iothubHost, 8883);
//   while (!mqtt.connected()) {
//     String user = String(iothubHost) + "/" + deviceId + "/?api-version=2018-06-30";
//     String token = createSasToken();
//     if (!mqtt.connect(deviceId, user.c_str(), token.c_str())) {
//       delay(5000);
//     }
//   }
// }

// void sendToIoTHub(int analogValue, int digitalValue) {
//   if (!mqtt.connected()) {
//     connectIoTHub();
//   }
//   String payload = "{\"analog\":" + String(analogValue) + ",\"digital\":" + String(digitalValue) + "}";
//   mqtt.publish(("devices/" + String(deviceId) + "/messages/events/").c_str(), payload.c_str());
// }