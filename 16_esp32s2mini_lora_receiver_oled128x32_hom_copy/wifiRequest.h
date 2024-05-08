#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClientSecure.h>

/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/
//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "192.168.1.42"

#ifndef STASSID
#define STASSID "TP-LINK_11FF"
#define STAPSK "52142505"
#endif


const char* test_root_ca=\
"-----BEGIN CERTIFICATE-----" \
"MIIHOjCCBiKgAwIBAgIQBw9cw86/CkIn2VaPfPj6HzANBgkqhkiG9w0BAQsFADBP"\
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMSkwJwYDVQQDEyBE"\
"aWdpQ2VydCBUTFMgUlNBIFNIQTI1NiAyMDIwIENBMTAeFw0yMzA2MjMwMDAwMDBa"\
"Fw0yNDA3MTYyMzU5NTlaMIGHMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZv"\
"cm5pYTEVMBMGA1UEBxMMUmVkd29vZCBDaXR5MRswGQYDVQQKExJPcmFjbGUgQ29y"\
"cG9yYXRpb24xLzAtBgNVBAMTJmFkYi5ldS1mcmFua2Z1cnQtMS5vcmFjbGVjbG91"\
"ZGFwcHMuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnOxVaiLD"\
"pUzwf2zyhqU0J9awx97+RoD+lUavv/8hduF49itVWkOHy3wxJ76nbJyQbNvd2fkm"\
"K0m4plCg7k88ozbe4+oEyEDZcMS1TkAo6CNbUD1AIaC150TIKjf54FdkTDjman1b"\
"L2ACFPvcGo4Qo4aGNvIbf9o9jDjQkxrkfTegYuhXx0bY6A8rSFS7EbVVnxmidkcA"\
"egdpj8MJxpHIAO+jdxmU7E2Dk09gNvBCX0EqeEwtn9ONDOk1HIP04hv7GeGGLcwP"\
"yzDBqc9njyPc7j2RcSGAi6XkV37b/ZxdtsTOGCTaOyqOPIqWpCG2Ab0zzQJQ1H9U"\
"MgsgN3MxN7c/TQIDAQABo4ID1zCCA9MwHwYDVR0jBBgwFoAUt2ui6qiqhIx56rTa"\
"D5iyxZV2ufQwHQYDVR0OBBYEFNMcPuGdvMic0rQBHMchoF2LIclRMIGDBgNVHREE"\
"fDB6giZhZGIuZXUtZnJhbmtmdXJ0LTEub3JhY2xlY2xvdWRhcHBzLmNvbYIoKi5h"\
"ZGIuZXUtZnJhbmtmdXJ0LTEub3JhY2xlY2xvdWRhcHBzLmNvbYImKi5hZGJhcHBz"\
"LmV1LWZyYW5rZnVydC0xLm9yYWNsZXZjbi5jb20wDgYDVR0PAQH/BAQDAgWgMB0G"\
"A1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjCBjwYDVR0fBIGHMIGEMECgPqA8"\
"hjpodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vRGlnaUNlcnRUTFNSU0FTSEEyNTYy"\
"MDIwQ0ExLTQuY3JsMECgPqA8hjpodHRwOi8vY3JsNC5kaWdpY2VydC5jb20vRGln"\
"aUNlcnRUTFNSU0FTSEEyNTYyMDIwQ0ExLTQuY3JsMD4GA1UdIAQ3MDUwMwYGZ4EM"\
"AQICMCkwJwYIKwYBBQUHAgEWG2h0dHA6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzB/"\
"BggrBgEFBQcBAQRzMHEwJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0"\
"LmNvbTBJBggrBgEFBQcwAoY9aHR0cDovL2NhY2VydHMuZGlnaWNlcnQuY29tL0Rp"\
"Z2lDZXJ0VExTUlNBU0hBMjU2MjAyMENBMS0xLmNydDAJBgNVHRMEAjAAMIIBfAYK"\
"KwYBBAHWeQIEAgSCAWwEggFoAWYAdQDuzdBk1dsazsVct520zROiModGfLzs3sNR"\
"SFlGcR+1mwAAAYjqov06AAAEAwBGMEQCIExSSWEvpqLlreKRxQPEgC3qkcTwUxph"\
"2OP1zjlIihkOAiBkZBU6KmA0StvYeCsFvpENF3HjvCCNt6vAcnq6piTQsAB2AEiw"\
"42vapkc0D+VqAvqdMOscUgHLVt0sgdm7v6s52IRzAAABiOqi/SEAAAQDAEcwRQIh"\
"AOInjSJSZIlQAc5oDY4Mh+9n0dtZ0QhFCAq5OZWTY9NRAiBSQrYN352H9+hrOUi2"\
"xHsxGTDPQIIgwX6WCsUvN/DNmgB1ANq2v2s/tbYin5vCu1xr6HCRcWy7UYSFNL2k"\
"PTBI1/urAAABiOqi/OgAAAQDAEYwRAIgHOZw3Uxzfq4pN71hguJQYxh9nLv+YGpI"\
"hIT8CHjgPMcCIGHxbxa0/0H3hMZj4FM7UsKefEvL2NIjqRnpxG3vzdFDMA0GCSqG"\
"SIb3DQEBCwUAA4IBAQBn8NbbvtYzrhhT6jjMjKtXlz5wOGv7h0wNKW9UFUryK0LB"\
"pKPMb3yg4dijTzhulFOPcpZFNQNtz0MHrmtRpCdmF0RxHoKJ/UFNNNQzH2r0wgMY"\
"EeNXl1FyS6KH1cDved/iZT6Q7UqlJcq7u2YNwqYpsdBm7c8be8X9ZxRpqz07ejHQ"\
"MtLv/zHBi2H9KScxrhOXb99wyaA8pbbbaVJGnMih8jCGWBuL/hkKcgSxUy6OpHCF"\
"uzy2jRkzwq8hWWktjya5wJqjadmpTnOY2B2xtbWRdt/iNepVbG69BU2GiHplChmU"\
"ugEqxhyq8dRVe4TwUiXfckiuB+kbDyVQadmQYSa2"\
"-----END CERTIFICATE-----"\
"-----BEGIN CERTIFICATE-----"\
"MIIE6jCCA9KgAwIBAgIQCjUI1VwpKwF9+K1lwA/35DANBgkqhkiG9w0BAQsFADBh"\
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3"\
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD"\
"QTAeFw0yMDA5MjQwMDAwMDBaFw0zMDA5MjMyMzU5NTlaME8xCzAJBgNVBAYTAlVT"\
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxKTAnBgNVBAMTIERpZ2lDZXJ0IFRMUyBS"\
"U0EgU0hBMjU2IDIwMjAgQ0ExMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC"\
"AQEAwUuzZUdwvN1PWNvsnO3DZuUfMRNUrUpmRh8sCuxkB+Uu3Ny5CiDt3+PE0J6a"\
"qXodgojlEVbbHp9YwlHnLDQNLtKS4VbL8Xlfs7uHyiUDe5pSQWYQYE9XE0nw6Ddn"\
"g9/n00tnTCJRpt8OmRDtV1F0JuJ9x8piLhMbfyOIJVNvwTRYAIuE//i+p1hJInuW"\
"raKImxW8oHzf6VGo1bDtN+I2tIJLYrVJmuzHZ9bjPvXj1hJeRPG/cUJ9WIQDgLGB"\
"Afr5yjK7tI4nhyfFK3TUqNaX3sNk+crOU6JWvHgXjkkDKa77SU+kFbnO8lwZV21r"\
"eacroicgE7XQPUDTITAHk+qZ9QIDAQABo4IBrjCCAaowHQYDVR0OBBYEFLdrouqo"\
"qoSMeeq02g+YssWVdrn0MB8GA1UdIwQYMBaAFAPeUDVW0Uy7ZvCj4hsbw5eyPdFV"\
"MA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw"\
"EgYDVR0TAQH/BAgwBgEB/wIBADB2BggrBgEFBQcBAQRqMGgwJAYIKwYBBQUHMAGG"\
"GGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTBABggrBgEFBQcwAoY0aHR0cDovL2Nh"\
"Y2VydHMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNydDB7BgNV"\
"HR8EdDByMDegNaAzhjFodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vRGlnaUNlcnRH"\
"bG9iYWxSb290Q0EuY3JsMDegNaAzhjFodHRwOi8vY3JsNC5kaWdpY2VydC5jb20v"\
"RGlnaUNlcnRHbG9iYWxSb290Q0EuY3JsMDAGA1UdIAQpMCcwBwYFZ4EMAQEwCAYG"\
"Z4EMAQIBMAgGBmeBDAECAjAIBgZngQwBAgMwDQYJKoZIhvcNAQELBQADggEBAHer"\
"t3onPa679n/gWlbJhKrKW3EX3SJH/E6f7tDBpATho+vFScH90cnfjK+URSxGKqNj"\
"OSD5nkoklEHIqdninFQFBstcHL4AGw+oWv8Zu2XHFq8hVt1hBcnpj5h232sb0HIM"\
"ULkwKXq/YFkQZhM6LawVEWwtIwwCPgU7/uWhnOKK24fXSuhe50gG66sSmvKvhMNb"\
"g0qZgYOrAKHKCjxMoiWJKiKnpPMzTFuMLhoClw+dj20tlQj7T9rxkTgl4ZxuYRiH"\
"as6xuwAwapu3r9rxxZf+ingkquqTgLozZXq8oXfpf2kUCwA/d5KxTVtzhwoT0JzI"\
"8ks5T1KESaZMkE4f97Q="\
"-----END CERTIFICATE-----"\
"-----BEGIN CERTIFICATE-----"\
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh"\
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3"\
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD"\
"QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT"\
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j"\
"b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG"\
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB"\
"CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97"\
"nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt"\
"43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P"\
"T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4"\
"gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO"\
"BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR"\
"TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw"\
"DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr"\
"hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg"\
"06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF"\
"PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls"\
"YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk"\
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4="\
"-----END CERTIFICATE-----\n";


 
void start_wifi()
{
  //  Serial.begin(115200);

  Serial.println();
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // pinMode(LED,OUTPUT); 
  // digitalWrite(LED,HIGH);
}

void send_message_via_http(String parts[])
{

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    // WiFiClient client;
    WiFiClientSecure client;
    HTTPClient http;

    // client.setCACert(test_root_ca);
    client.setInsecure();

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "https://re9tdugg3fb3uf6-dbdyplo.adb.eu-frankfurt-1.oraclecloudapps.com/ords/app2/esp32/fencesensors");  // HTTP

    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    // int httpCode = http.POST("{\"hello\":\"world\"}");
    
    //  int httpCode = http.POST("{hello:world}");
     int httpCode = http.POST(get_JSON_string(parts));

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
        
        // digitalWrite(LED,LOW);
        delay(100);

      }
      else if ( httpCode == 201){
        // digitalWrite(LED,HIGH);
        delay(100);
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

}