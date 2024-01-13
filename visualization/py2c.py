# This script shall visualize the resulting pattern from the input button presses.

rowCountAndColumnCount = 5

def toggle(value):
    if "▯" == value:
        value = "▮"
    else:
        value = "▯"
    return value

def toggleButtonAndNeighbors(button, matrix):
    matrix[button] = toggle(matrix[button])
    if 0 != (button % rowCountAndColumnCount):
        matrix[button - 1] = toggle(matrix[button - 1])
    if (rowCountAndColumnCount - 1) != (button % rowCountAndColumnCount):
        matrix[button + 1] = toggle(matrix[button + 1])
    if rowCountAndColumnCount <= button:
        matrix[button - rowCountAndColumnCount] = toggle(matrix[button - rowCountAndColumnCount])
    if (rowCountAndColumnCount * (rowCountAndColumnCount - 1)) > button:
        matrix[button + rowCountAndColumnCount] = toggle(matrix[button + rowCountAndColumnCount])
    return

def printMatrix2d(matrix):
    for row in range(rowCountAndColumnCount):
        for column in range(rowCountAndColumnCount):
            index = rowCountAndColumnCount * rowCountAndColumnCount - 1 - column - row * rowCountAndColumnCount
            print(f"{matrix[index]} ", end="")
        print("\n", end="")
    return

def printCcode(buttons):
    byteEntries = ["0", "1", "2", "3", ]
    buttonsSorted = list(buttons)
    buttonsSorted.sort()
    for button in buttonsSorted:
        byteEntries[button // 8] += f", {button}"

    cCode = "{"
    for entry in byteEntries:
        cCode += f"createBitmaskToPress<{entry}>(), "
    cCode = cCode[:-2]
    cCode += "},"
    print(cCode)
    return

if __name__ == "__main__":
    buttonss = (
        # (0, (12,)),
        # (1, (14,)),
        # (2, (0,)),
        # (3, (10, 14)),
        # (4, (6, 18)),
        # (5, (13, 24)),
        # (6, (13, 14)),
        # (7, (18, 24)),
        # (8, (6, 12)),
        # (9, (16, 17)),
        # (10, (0, 4, 24)),
        # (11, (1, 4, 19)),
        # (12, (7, 15, 23)),
        # (13, (6, 16, 18)),
        # (14, (12, 17, 23)),
        # (15, (12, 13, 17)),
        # (16, (3, 7, 11)),
        # (17, (1, 16, 21)),
        # (18, (3, 12, 19)),
        # (19, (8, 9, 14)),
        # (20, (9, 13, 21)),
        # (21, (11, 15, 24)),
        # (22, (10, 12, 18)),
        # (23, (2, 12, 21)),
        # (24, (7, 11, 15)),
        # (25, (6, 8, 16, 24)),
        # (26, (0, 14, 16, 24)),
        # (27, (8, 15, 22, 23)),
        # (28, (0, 3, 13, 20)),
        # (29, (8, 12, 18, 23)),
        # (30, (2, 6, 12, 20)),
        # (31, (9, 12, 14, 22)),
        # (32, (6, 7, 17, 19)),
        # (33, (7, 14, 17, 21)),
        # (34, (9, 19, 20, 23)),
        # (35, (1, 13, 18, 19)),
        # (36, (4, 5, 15, 24)),
        # (37, (4, 12, 18, 22)),
        # (38, (5, 10, 11, 12)),
        # (39, (0, 1, 8, 12)),
        # (40, (5, 6, 7, 17, 23)),
        # (41, (0, 8, 13, 17, 21)),
        # (42, (4, 7, 10, 17, 22)),
        # (43, (3, 4, 8, 15, 23)),
        # (44, (4, 14, 15, 16, 21)),
        # (45, (2, 11, 13, 20, 24)),
        # (46, (1, 4, 12, 16, 17)),
        # (47, (6, 11, 12, 16, 20)),
        # (48, (1, 9, 11, 13, 22)),
        (49, (1, 11, 22, 13, 9)),
        (50, (11, 22, 20, 3, 9)),
        (51, (1, 3, 9, 13, 21)),
        (52, (9, 17, 10, 15, 20)),
        (53, (1, 6, 15, 22, 24)),
        (54, (5, 11, 15, 14, 18)),
        (55, (14, 12, 7, 6, 0)),
        (56, (24, 22, 21, 15, 7, 0)),  # intermediate
        (57, (20, 21, 13, 18, 17, 23)),
        (58, (0, 1, 6, 17, 18, 24)),
        (59, (12, 10, 15, 20, 23, 24)),
        # (60, ()),
        # (61, ()),
        # (62, ()),
        # (63, ()),
        # (64, ()),
        # (65, ()),
        # (66, ()),
        # (67, ()),
        # (68, ()),
        # (69, ()),
        # (70, ()),
        # (71, ()),
        # (72, ()),
        # (73, ()),
        # (74, ()),
        # (75, ()),
        # (76, ()),
        # (77, ()),
        # (78, ()),
        # (79, ()),
        # (80, ()),
        # (81, ()),
        # (82, ()),
        # (83, ()),
        # (84, ()),
        # (85, ()),
        # (86, ()),
        # (87, ()),
        # (88, ()),
        # (89, ()),
        # (90, ()),
        # (91, ()),
        # (92, ()),
        # (93, ()),
        # (94, ()),
        # (95, ()),
        # (96, ()),
        # (97, ()),
        # (98, ()),
        # (99, ()),
    )

    matrices = []
    for level, buttons in buttonss:
        for button in buttons:
            assert 0 <= button < (rowCountAndColumnCount * rowCountAndColumnCount)

        matrix = ["▯", ] * (rowCountAndColumnCount * rowCountAndColumnCount)

        for button in buttons:
            toggleButtonAndNeighbors(button, matrix)

        matrices.append((level, buttons, matrix, ))


    for level, buttons, matrix in matrices:
        print("-----------------------------------")
        print(f"level {level}\n")
        printMatrix2d(matrix)

    print("-----------------------------------")
    print()  # newline

    for level, buttons, matrix in matrices:
        printCcode(buttons)
