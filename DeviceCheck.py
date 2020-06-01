import asyncio
from bleak import discover

"""
    BLEのデバイスのID一覧を表示するスクリプト
"""


async def run():
    # 接続されているBLEデバイス一覧を変数に格納する
    devices  = await discover()
    for dev in devices:
        # デバイス情報の表示
        print(dev)

# イベントループを設定する。スレッドの生成
loop = asyncio.get_event_loop()
# スレッドの開始
loop.run_until_complete(run())