# -*- coding: utf-8 -*-
import logging
import asyncio
import platform

from bleak import BleakClient
from bleak import _logger as logger

# キャラスタリックの設定(Arduino IDEのCHARACTERISTIC_TX部分をコピー)
CHARACTERISTIC_UUID = (
    "2049779d-88a9-403a-9c59-c7df79e1dd7c"
)  # <--- Change to the characteristic you want to enable notifications from.


def notification_handler(sender, data):
    """Simple notification handler which prints the data received."""
    # データを受け取ったら送信主とそのデータを表示(バイナリアレイ型)
    print("{0}: {1}".format(sender, data))

async def run(address, loop, debug=False):
    if debug:
        import sys
        # デバッガーの表示
        loop.set_debug(True)
        l = logging.getLogger("asyncio")
        l.setLevel(logging.DEBUG)
        h = logging.StreamHandler(sys.stdout)
        h.setLevel(logging.DEBUG)
        l.addHandler(h)
        logger.addHandler(h)

    async with BleakClient(address, loop=loop) as client:
        # 接続
        x = await client.is_connected()
        logger.info("Connected: {0}".format(x))

        # notifyの開始
        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        # 5秒間行う
        await asyncio.sleep(5.0, loop=loop)
        # notify終わり
        await client.stop_notify(CHARACTERISTIC_UUID)


if __name__ == "__main__":
    import os

    os.environ["PYTHONASYNCIODEBUG"] = str(1)
    address = (
        # デバイスID設定(OSによって微妙に異なる。windows10は一行下のもの)
        "30:AE:A4:1F:93:32"  # <--- Change to your device's address here if you are using Windows or Linux
        if platform.system() != "Darwin"
        else "243E23AE-4A99-406C-B317-18F1BD7B4CBE"  # <--- Change to your device's address here if you are using macOS
    )
    # スレッド作成
    loop = asyncio.get_event_loop()
    # スレッドの開始
    loop.run_until_complete(run(address, loop, True))