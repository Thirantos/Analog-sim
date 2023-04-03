inputs = []

class part():
    voltage = []

    nextPart = None
    nextPort: int
    
    def next(self, part, port: int):
        self.nextPart = part
        self.nextPort = port

    def onUse(self):
        return NotImplemented
    
    def setVoltage(self, voltageIn: float, port: int):
        self.voltage[port].insert(port, voltageIn)

class sensor(part):

    def onUse(self):
        assert len(self.voltage[0]) == 0, "too many arguments"
        print(self.voltage[0])


class dial(part):

    def onUse(self):
        self.nextPart.voltage[self.nextPort] = self.voltage[0]
        self.nextPart.onUse()

def tick():
    for i in inputs:
        i.onUse()