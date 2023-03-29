import asyncio

parts = []

class part():
    voltage: float
    async def onTick(self):
        return NotImplemented
    
    def __init__(self):
        parts.append(self)

class sensor(part):

    async def onTick(self):
        print(self.voltage)

class dial(part):

    nextpart: part

    async def onTick(self):
        self.nextpart.voltage = self.voltage


class main():

    async def Loop(loop):
        
        for part in parts:
            await part.onTick()

    def main(self) -> None:

        dial1 = dial()

        sensor1 = sensor()

        dial1.nextpart = sensor1

        dial1.voltage = 5

        loop = asyncio.new_event_loop()
        loop.call_later(5, main())
        task = loop.create_task(main().Loop())
        loop.run_until_complete(task)




if __name__ == '__main__':
    main().main()