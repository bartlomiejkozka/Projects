from enum import Enum
import numpy as np

class CellType(Enum):
    EMPTY = 1
    BLOCK_I_LIGHT_BLUE = 2
    BLOCK_O_YELLOW = 3
    BLOCK_T_PURPLE = 4
    BLOCK_J_DARK_BLUE = 5
    BLOCK_L_ORANGE = 6
    BLOCK_S_GREEN = 7
    BLOCK_Z_RED = 8

class Board:
    def __init__(self, width, height):
        self.__width = width
        self.__height = height
        self.__board = np.full((self.height, self.width), CellType.EMPTY)
        self.points = 0

    @property
    def width(self):
        return self.__width

    @property
    def height(self):
        return self.__height

    def get_boardCell(self, row, col):
        return self.__board[row, col]

    def setBoardCell(self, row, col, cellType):
        self.__board[row, col] = cellType

    def set_BlockTypeBoardCell(self, row, col, blockType):
        self.__board[int(row), int(col)] = blockType

    def set_EmptyBoardCell(self, row, col):
        self.__board[row, col] = CellType.EMPTY

    def isEmpty(self, row, col):
        return self.__board[int(row), int(col)] == CellType.EMPTY

    def removeRow(self):
        for row in range(self.height):
            if not any([self.isEmpty(row, j) for j in range(self.width)]):
                self.points += 1
                for i in range(row, 1, -1):
                    for j in range(self.width):
                         self.setBoardCell(i,j, self.get_boardCell(i-1,j))
                for i in range(self.width):
                    self.set_EmptyBoardCell(0, i)
            else:
                pass
