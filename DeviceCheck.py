import asyncio
from bleak import discover

async def run():
    devices  = await discover()
    for dev in devices:
        print(dev)

loop = asyncio.get_event_loop()
loop.run_until_complete(run())