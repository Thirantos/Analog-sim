import parts

class component():
    partslist: list(parts.part)
    voltageIn: float
    next: parts.part

class dial(component):
    partslist = [parts.dial]
    