#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "id";
const char* password = "senha";
const char* planta_id = "ABC123";
const char* sensor_id = "DEF456";

void setup()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
  if(WiFi.status()== WL_CONNECTED)
  {   //Check WiFi connection status
  
    HTTPClient http;   
    
    http.begin("http://ip_api:3000/sensors");  //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/json");             //Specify content-type header
    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["planta_id"] = planta_id;
    doc["sensor_id"] = sensor_id;
    doc["data"] = random(0, 200);
    doc["medida"] = "aaaaaaaaa";
    
    String requestBody;
    serializeJson(doc, requestBody);
    
    int httpResponseCode = http.POST(requestBody);   //Send the actual POST request
    
    if(httpResponseCode>0)
    {
    
      String response = http.getString();                       //Get the response to the request
    
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    }
    else
    {
    
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();  //Free resources
  }
  else
  {
    Serial.println("Error in WiFi connection");   
  }
  
  delay(10000);  //Send a request every 10 seconds
}