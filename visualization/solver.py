# This script shall visualize the resulting pattern from the input button presses.

from py2c import rowCountAndColumnCount, toggleButtonAndNeighbors, printMatrix2d, symbolOn, symbolOff

def solveLightsOff(matrix):
    buttonsPressedToReturn = None
    dimension = rowCountAndColumnCount * rowCountAndColumnCount
    terminate = False

    if all(symbol == symbolOff for symbol in matrix):
        buttonsPressedToReturn = ()
        terminate = True

    for maxNumberOfButtonPresses in range(1, dimension + 1, 1):
        if terminate:
            break

        buttonsPressed = list(range(maxNumberOfButtonPresses))

        workingMatrix = matrix.copy()
        for button in buttonsPressed:
            toggleButtonAndNeighbors(button, workingMatrix)

        permutate = (0 < len(buttonsPressed))
        while permutate and not terminate:
            # check whether finished
            success = all(symbol == symbolOff for symbol in workingMatrix)
            if success:
                buttonsPressedToReturn = buttonsPressed
                terminate = True
            else:
                # permutate next button
                minButtonAdvanced = -1
                supportedMaxIndex = dimension - 1
                while buttonsPressed[minButtonAdvanced] == supportedMaxIndex:
                    if abs(minButtonAdvanced) == maxNumberOfButtonPresses:
                        # last index reached
                        permutate = False
                        break
                    else:
                        # check previous index
                        minButtonAdvanced -= 1
                        supportedMaxIndex -= 1

                if permutate:
                    # advance first index
                    buttonIndex = minButtonAdvanced
                    toggleButtonAndNeighbors(buttonsPressed[buttonIndex], workingMatrix)  # revert old
                    buttonsPressed[buttonIndex] = buttonsPressed[buttonIndex] + 1
                    toggleButtonAndNeighbors(buttonsPressed[buttonIndex], workingMatrix)  # apply new
                    # reset all following
                    for buttonIndex in range(minButtonAdvanced + 1, 0, 1):
                        toggleButtonAndNeighbors(buttonsPressed[buttonIndex], workingMatrix)  # revert old
                        buttonsPressed[buttonIndex] = buttonsPressed[buttonIndex - 1] + 1
                        toggleButtonAndNeighbors(buttonsPressed[buttonIndex], workingMatrix)  # apply new

    return buttonsPressedToReturn



if __name__ == "__main__":
    lightss = (
        (139, (0, 3, 4, 10, 11, 12, 17, 20, )),
    )

    matrices = []
    for level, lights in lightss:
        for light in lights:
            assert 0 <= light < (rowCountAndColumnCount * rowCountAndColumnCount)

        matrix = ["▯", ] * (rowCountAndColumnCount * rowCountAndColumnCount)

        for light in lights:
            matrix[light] = symbolOn

        matrices.append((level, lights, matrix, ))

    solutions = []
    for level, lights, matrix in matrices:
        solution = solveLightsOff(matrix)
        solutions.append((level, lights, matrix, solution))

    for level, lights, matrix, solution in solutions:
        print("-----------------------------------")
        print(f"level {level}\n")
        printMatrix2d(matrix)
        print()
        print(f"({level}, {tuple(solution)}),")
        print()
    print("-----------------------------------")
    print()  # newline

    # for level, lights, matrix, solution in solutions:
    #     print(f"({level}, {tuple(solution)}),")
