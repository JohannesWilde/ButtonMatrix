# This script shall reduce the cCode to a python-usable input.

import regex

if __name__ == "__main__":

    cCode = """
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()}, // 0x00
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 10, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 13, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 4>(), createBitmaskToPress<1>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 4>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 7>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 17, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 12, 13>(), createBitmaskToPress<2, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 7>(), createBitmaskToPress<1, 11>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()}, // 0x10
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 9, 14>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9, 13>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 10, 12>(), createBitmaskToPress<2, 18>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 7>(), createBitmaskToPress<1, 11, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 8>(), createBitmaskToPress<2, 16>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 16>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 22, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 3>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2, 18, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2, 6>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9, 12, 14>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6, 7>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 17, 19>(), createBitmaskToPress<3>()}, // 0x20
    {createBitmaskToPress<0, 7>(), createBitmaskToPress<1, 14>(), createBitmaskToPress<2, 17, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0>(), createBitmaskToPress<1, 9>(), createBitmaskToPress<2, 19, 20, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 13>(), createBitmaskToPress<2, 18, 19>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 5>(), createBitmaskToPress<1, 15>(), createBitmaskToPress<2>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 4>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 18, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5>(), createBitmaskToPress<1, 10, 11, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0, 1>(), createBitmaskToPress<1, 8, 12>(), createBitmaskToPress<2>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 5, 6, 7>(), createBitmaskToPress<1>(), createBitmaskToPress<2, 17, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 0>(), createBitmaskToPress<1, 8, 13>(), createBitmaskToPress<2, 17, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4, 7>(), createBitmaskToPress<1, 10>(), createBitmaskToPress<2, 17, 22>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 3, 4>(), createBitmaskToPress<1, 8, 15>(), createBitmaskToPress<2, 23>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 4>(), createBitmaskToPress<1, 14, 15>(), createBitmaskToPress<2, 16, 21>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 2>(), createBitmaskToPress<1, 11, 13>(), createBitmaskToPress<2, 20>(), createBitmaskToPress<3, 24>()},
    {createBitmaskToPress<0, 1, 4>(), createBitmaskToPress<1, 12>(), createBitmaskToPress<2, 16, 17>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 6>(), createBitmaskToPress<1, 11, 12>(), createBitmaskToPress<2, 16, 20>(), createBitmaskToPress<3>()},
    {createBitmaskToPress<0, 1>(), createBitmaskToPress<1, 9, 11, 13>(), createBitmaskToPress<2, 22>(), createBitmaskToPress<3>()}, // 0x30"""

    buttonss = []
    level = 0
    for line in cCode.split("\n"):
        numberStrings = regex.findall("createBitmaskToPress<\d+,* *(.*?)>\(\)", line)
        if 0 != len(numberStrings):
            singleNumberStrings = []
            for numberString in numberStrings:
                singleNumberStrings.extend(numberString.split(","))
            nonEmptySingleNumberStrings = []
            for numberString in singleNumberStrings:
                if 0 != len(numberString):
                    nonEmptySingleNumberStrings.append(numberString)
            numbers = tuple(int(numberString) for numberString in nonEmptySingleNumberStrings)
            buttonss.append((level, numbers))

            level += 1

for buttons  in buttonss:
    print(f"({buttons[0]}, {buttons[1]}),")
