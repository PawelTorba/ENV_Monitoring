#include "mbedtls/md.h"
#include <WiFi.h>
#include "azure.h"

#include <WiFiClientSecure.h>
#include <HTTPClient.h>

WiFiClientSecure wifiClient;
HTTPClient httpClient;

const char* iothubHost = "";
const char* deviceId = "";
const char* deviceKey = "";

String urlEncode(const String &msg) {
    String encoded = "";
    char c;
    char bufHex[4];
    for (int i = 0; i < msg.length(); i++) {
        c = msg.charAt(i);
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
        encoded += c;
        } else {
        sprintf(bufHex, "%%%02X", c);
        encoded += bufHex;
        }
    }
    return encoded;
}

String createSasToken() {
    String resourceUri = String(iothubHost) + "/devices/" + String(deviceId);
    String encodedUri = urlEncode(resourceUri);

    long expiry = time(NULL) + 3600; 
    String stringToSign = encodedUri + "\n" + String(expiry);

    size_t keyLen;
    unsigned char key[64];
    int result = mbedtls_base64_decode(key, sizeof(key), &keyLen,
                            (const unsigned char *)deviceKey,
                            strlen(deviceKey));
    
    if (result != 0) {
        Serial.printf("Base64 decode error: %d\r\n", result);
    }
    
    unsigned char hmacResult[32];
    mbedtls_md_context_t ctx;
    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1);
    mbedtls_md_hmac_starts(&ctx, key, keyLen);
    mbedtls_md_hmac_update(&ctx,
                            (const unsigned char *)stringToSign.c_str(),
                            stringToSign.length());
    mbedtls_md_hmac_finish(&ctx, hmacResult);
    mbedtls_md_free(&ctx);

    char base64Sig[64];
    size_t sigLen;
    mbedtls_base64_encode((unsigned char *)base64Sig, sizeof(base64Sig), &sigLen,
                            hmacResult, 32);

    base64Sig[sigLen] = '\0';
    String signature = urlEncode(String(base64Sig));

    String sasToken = "SharedAccessSignature sr=" + encodedUri +
                        "&sig=" + signature +
                        "&se=" + String(expiry);

    return sasToken;
}

void connectIoTHub() {
    wifiClient.setInsecure();
    String token = createSasToken();
    Serial.println("SAS Token created successfully");
}

void sendToIoTHub(String payload) {
    String url = "https://" + String(iothubHost) + "/devices/" + String(deviceId) + "/messages/events?api-version=2020-09-30";
    String token = createSasToken();
    String authHeader = token;

    wifiClient.setInsecure();
    httpClient.begin(wifiClient, url);
    httpClient.addHeader("Authorization", authHeader);
    httpClient.addHeader("Content-Type", "application/json");

    int httpCode = httpClient.POST(payload);

    if (httpCode == 204) {
        Serial.printf("Message sent successfully (HTTP %d)\r\n", httpCode);
    } else {
        Serial.printf("Message failed to send (HTTP %d)\r\n", httpCode);
        Serial.println(httpClient.getString());
    }

    httpClient.end();
}
