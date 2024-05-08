#include <ArduinoJson.h>

StaticJsonDocument<100> doc;
String json;

String get_JSON_string(String parts[])
{
  doc["sensor_id"] = parts[1];
  doc["sensor_value"] = parts[2];
  serializeJson(doc, json);
  return json;
}