import parts

class main():
    def main(self) -> None:
        dial1 = parts.dial
        sensor1 = parts.sensor
        sensor2 = parts.sensor
        sensor3 = parts.sensor

        dial1.setinput(dial1, 5, 0)

        dial1.next(dial1, sensor1, 0)
        dial1.next(dial1, sensor2, 0)
        dial1.next(dial1, sensor3, 0)

        dial1.onUse(dial1)
        



if __name__ == '__main__':
    main().main()