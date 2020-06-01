# BT_esptopython

python(PC?Raspi)とESP32をBluetoothで接続する

---

## 概要

ESP32とBLE通信で接続し送信されてきたデータを受け取るPythonプログラム

---

## ファイル構成

- DeviceCheck.py --- ESP32のデバイスIDを見るためのPythonプログラム。
- notification.py --- ESP32からデータを受取、表示するPythonプログラム。
- BLE_test --- ESP32でBLEのデータを送信するプログラム(Arduino IDE)

---

## 実行環境の構築

### Arduino IDE

Arduino IDEのインストール

[Arduino公式ページ](https://www.arduino.cc/en/main/software)

### Pyhon

Pythonをインストールします。

[pythonのインストール方法](https://www.python.jp/install/windows/install_py3.html)

PythonのライブラリのBleakというライブラリを今回使用しました。
(Pybluezというライブラリが有名であるが、windowsだと動かしにくく。
Bleakの方が一応OSなどの依存性が少ないらしい)

``` pip install bleak ```

でインストールを行うことができる。

---

## 実行方法

実行方法はWindows10のものを説明します。
まずArduino IDEでESP32にBLE_testを書き込みます。
その後マイコンが動作しているのをシリアルターミナルで確認したら

``` windowsの設定 => デバイス => BLEまたはその他デバイスを追加する => Bluetooth ```

を選択して`ESP32`選択。ペアリングを行ってください。

その後、Pythonプログラムを実行します。
まずESP32のデバイスIDを調べないといけないので

```python DeviceCheck.py```

を実行してデバイスIDを取得してください
`xx:xx:xx:xx:xx:xx`
このような感じのものです。

これをコピーしてnotification.pyの51行目の部分にペーストします。

あとArduino IDEの送信用キャラスタリックをコピーします
送信用キャラスタリックはIDEの8行目

``` BLE_test.ino
    #define CHARACTERISTIC_UUID_TX "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
```

の文字列部分です。
これをコピーしてnotification.pyの11行目の部分にペーストします。

実行はコマンドプロンプトで

``` python notification.py ```

を入力すると実行。BLE通信で送られてきたものを見ることができます。
`(pythonのハンドラー周りが少し準備が遅い部分があるとかないとかで、改善が必要だと思う。とりあえず早めに作ったので..)`

Bleakのサンプルプログラムを用いた。

---

## 参考URL

1. [Bleak](https://github.com/hbldh/bleak)
2. [Pythonライブラリ bleakでWindows10/macOS/Linux上でtoioコア キューブを動かしてみる - Qiita](https://qiita.com/kenichih/items/8baa27b3aecc94dd8193)
3. [【Python】asyncio（非同期I/O）のイベントループをこねくり回す - Qiita](https://qiita.com/ynakaDream/items/b63fab24bb30dea6ddb1)