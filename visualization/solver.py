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
        (140, (0, 1, 3, 5, 7, 8, 10, 13, 14, 15, 17, 19, )),
        (141, (0, 1, 2, 6, 8, 11, 14, 15, 17, 19, 20, 21, 22, 23, 24, )),
        (142, (0, 1, 2, 7, 8, 9, 10, 11, 13, 15, 19, 23, )),
        (143, (0, 5, 11, 12, 13, 16, 20, 21, 24, )),
        (144, (4, 10, 11, 12, 16, 18, 21, 22, )),
        (145, (2, 3, 4, 6, 8, 9, 12, 13, 14, 18, 20, 23, )),
        (146, (1, 2, 4, 6, 8, 9, 10, 13, 14, 16, 19, 23, )),
        (147, (0, 2, 5, 6, 7, 8, 10, 11, 13, 15, 18, 23, 24, )),
        (148, (2, 4, 5, 6, 7, 9, 11, 13, 14, 17, 18, 20, 21, 22, )),
        (149, (1, 4, 5, 8, 15, 16, 19, 20, 24, )),
        (150, (1, 2, 4, 7, 9, 10, 11, 13, 14, 15, 18, 19, 22, 23, 24, )),
        (151, (1, 2, 4, 9, 11, 12, 13, 14, 15, 17, 18, 21, 22, )),
        # (152, ()),
        (153, (1, 3, 5, 10, 11, 13, 15, 17, 19, 20, 23, 24, )),
        # (154, ()),
        (155, (1, 4, 5, 6, 7, 9, 11, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23)),
        # (156, ()),
        (157, (1, 3, 5, 8, 13, 14, 15, 16, 19, 20, 23)),
        (158, (1, 4, 5, 6, 7, 8, 9, 11, 12, 15, 18, 19, 20, 22)),
        (159, (1, 2, 7, 8, 9, 15, 17, 18, 19, 20, 22)),
        (160, (0, 1, 3, 6, 7, 8, 9, 10, 11, 13, 16, 19, 21, 22, 24)),
        (161, (0, 2, 3, 4, 7, 10, 14, 17, 18, 21, 23, 24)),
        (162, (0, 1, 2, 4, 9, 10, 16, 17, 22)),
        (163, (1, 2, 3, 6, 7, 13, 14, 15, 17, 19, 22)),
        (164, (1, 6, 9, 10, 12, 13, 17, 23)),
        (165, (1, 5, 6, 7, 8, 9, 11, 14, 15, 16, 17, 19, 23)),
        (166, (0, 1, 3, 5, 6, 9, 10, 14, 16, 17, 19, 20, 22, 23, 24)),
        (167, (0, 2, 3, 5, 6, 11, 12, 17, 18, 19, 20)),
        (168, (0, 2, 3, 4, 7, 8, 9, 11, 17, 19, 20, 22, 24)),
        (169, (0, 1, 2, 3, 6, 8, 9, 11, 12, 17, 20, 24)),
        (170, (0, 4, 5, 7, 8, 9, 10, 11, 12, 13, 16, 18, 21, 23, 24)),
        (171, (1, 2, 4, 5, 7, 9, 11, 13, 14, 15, 16, 18, 19, 20, 21, 22, 24)),
        (172, (1, 2, 3, 4, 5, 6, 9, 13, 15, 16, 17, 18, 19, 20, 23)),
        (173, (1, 2, 3, 6, 8, 12, 13, 15, 16, 22, 24)),
        (174, (3, 4, 5, 6, 7, 8, 9, 11, 14, 15, 19, 20, 24)),
        (175, (3, 4, 9, 11, 12, 14, 18)),
        (176, (6, 8, 10, 12, 13, 15, 17, 18, 19, 21, 22, 23)),
        (177, (5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 21, 23)),
        (178, (0, 6, 8, 9, 10, 11, 14, 16, 17, 22)),
        (179, (2, 6, 7, 9, 10, 11, 12, 13, 16, 17, 19, 21, 22)),
        # (180, ()),
        # (181, ()),
        # (182, ()),
        # (183, ()),
        # (184, ()),
        # (185, ()),
        # (186, ()),
        # (187, ()),
        # (188, ()),
        # (189, ()),
        # (190, ()),
        # (191, ()),
        # (192, ()),
        # (193, ()),
        # (194, ()),
        # (195, ()),
        # (196, ()),
        # (197, ()),
        # (198, ()),
        # (199, ()),
    )

    matrices = []
    for level, lights in (lightss[-1], ):
        for light in lights:
            assert 0 <= light < (rowCountAndColumnCount * rowCountAndColumnCount)

        matrix = ["▯", ] * (rowCountAndColumnCount * rowCountAndColumnCount)

        for light in lights:
            matrix[light] = symbolOn

        matrices.append((level, lights, matrix, ))

    solutions = []
    for level, lights, matrix in matrices:
        print("-----------------------------------")
        print(f"level {level}\n")
        printMatrix2d(matrix)

        solution = solveLightsOff(matrix)
        solutions.append((level, lights, matrix, solution))

        print()
        if solution is not None:
            print(f"        ({level}, {tuple(solution)}),")
        else:
            print(f"        ({level}, {solution}),")
        print()
    print("-----------------------------------")
    print()  # newline


    # for level, lights, matrix, solution in solutions:
    #     print(f"({level}, {tuple(solution)}),")
