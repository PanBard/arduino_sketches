#include <ArduinoJson.h>

StaticJsonDocument<100> doc;
String json;

String get_JSON_string()
{
  doc["id"] = parts[1];
  doc["value"] = parts[2];
  serializeJson(doc, json);
  return json;
}