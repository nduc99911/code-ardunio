#include <ESP8266WiFi.h> // Khai báo sử dụng thư viện ESP8266WiFi.h để thiết lập chế độ HTTP client cho ESP8266
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h> // Khai báo sử dụng thư viện DHT
#define DHTPIN D2 // Chân dữ liệu của DHT11 kết nối với GPIO4 của ESP8266
#define DHTTYPE DHT11 // Loại DHT được sử dụng
DHT dht(DHTPIN, DHTTYPE);

String url = "http://4d53-14-190-101-108.ngrok.io/device";
String key = "thietbi1";
String room = "101";

WiFiClient wifiClient;

const char* ssid = "Hieu Loan"; // Tên mạng Wifi được chỉ định sẽ kết nối (SSID)
const char* password = "0238800126"; // Password của mạng Wifi được chỉ định sẽ kết nối
const int sendingInternval = 3 * 1000; // Biến cập nhật dữ liệu sau mỗi 2s
void setup() {
  Serial.begin(115200);
  dht.begin(); // Khởi tạo DHT1 11 để truyền nhận dữ liệu
  Serial.println("Connecting");
  // Thiết lập ESP8266 là Station và kết nối đến Wifi. in ra dấu `.` trên terminal nếu chưa được kết nối
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\r\nWiFi connected");
  HTTPClient http;
  http.begin(wifiClient ,url +"/create?key="+ key + "&room=" + room);
  http.GET();
  http.end();
}
void loop() {
  // Đọc gía trị nhiệt độ (độ C), độ ẩm. Xuất ra thông báo lỗi và thoát ra nếu dữ liệu không phải là số
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  HTTPClient http2;
  http2.begin(wifiClient ,url +"/pushdata?spO2=" + String(temp, 1) + "&heartbeat=" + String(humi, 1)+"&hypothermia=36.5&key="+ key);
  Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp, 1).c_str(), String(humi, 1).c_str());
  http2.GET();
  http2.end();

  delay(sendingInternval);
}
