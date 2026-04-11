#ifndef AZURE_H
#define AZURE_H
#include "time.h"
#include "mbedtls/base64.h"

extern const char* ssid;
extern const char* password;
extern const char* iothubHost;
extern const char* deviceId;
extern const char* deviceKey;

String createSasToken();

void connectIoTHub();

void sendToIoTHub(String payload);

#endif // AZURE_H