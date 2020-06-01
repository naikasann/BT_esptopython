#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLEのキャラスタリック
#define SERVICE_UUID           "28b0883b-7ec3-4b46-8f64-8559ae036e4e"
#define CHARACTERISTIC_UUID_TX "2049779d-88a9-403a-9c59-c7df79e1dd7c"

// デバイス名(win10などからこの名前で検知される)
#define DEVICENAME "ESP32"

// Arduinoのシリアル速度
#define SPI_SPEED 115200

// BLE用の変数定義
BLECharacteristic *pCharacteristicTX;
bool deviceConnected = false;
// 送信データ(仮)
int senddata = 0;

// BLE用の接続コールバック
class funcServerCallbacks: public BLEServerCallbacks{
    void onConnect(BLEServer* pServer){
        deviceConnected = true;
    }
    void onDisconnect(BLEServer* pServer){
        deviceConnected = false;
    }
};

// キャラスタリック作成用
void doPrepare(BLEService *pService){
    // Notify用のキャラクタリスティックを作成する
    pCharacteristicTX = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
    pCharacteristicTX->addDescriptor(new BLE2902());
}

void setup() {
  Serial.begin(SPI_SPEED);

  // BLEの初期化
  BLEDevice::init(DEVICENAME);
  // サーバー作成、コールバック設定
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new funcServerCallbacks);
  // サービスの作成
  BLEService *pService = pServer->createService(SERVICE_UUID);
  doPrepare(pService);
  // サービス開始、アドバタイジングの開始
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  // 接続待機
  Serial.println("Waiting to connect...");
  while(!deviceConnected){delay(100);}
  // 接続完了  
  Serial.println("Connection!");
  delay(5000);
}

// 適当にデータを送信する。
void loop() {
  char c[100];

  // デバイスが接続されているとき(コールバック設定だと切断時に時差が生じる。)
  if(deviceConnected){
    // 送信データの作成
    senddata++;
    sprintf(c,"%d",senddata);
    // キャラスタリックにセットして送信する。
    pCharacteristicTX->setValue(c);
    pCharacteristicTX->notify();
    // デバッグ用
    Serial.println(senddata);
  }else{
    // 切断されたとき。
    Serial.println("disconnect");
  }
  // 送信間隔
  delay(1000);
}
