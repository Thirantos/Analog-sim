inputs = []


class part():
    
    def __init__(self) -> None:
        self.input = []
        self.output: list[list] = []

    def next(self, part, port: int):
        Port = [part,port]
        self.output.append(Port)
        

    def onUse(self):
        return NotImplemented
    
    def setinput(self, inputIn: float, port: int):
        self.input.insert(port, inputIn)


class sensor(part):

    def __init__(self) -> None:
        super().__init__()

    input = []

    def onUse(self):
        assert len(self.input) == 1, "too many arguments"
        print(self.input[0])

 
class dial(part):

    input = []
    output: list[list] = []
    
    def __init__(self) -> None:
        self.input = []
        self.output: list[list] = []
        super().__init__()


    def onUse(self):
        for i in self.output:
            i[0].setinput(i[0], self.input[0], i[1])
            i[0].onUse(i[0])
        

def tick():
    for i in inputs:
        i.onUse()