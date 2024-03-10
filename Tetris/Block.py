import random
from Board import *

class Block:
    def __init__(self, blockTypeInt, board):
        if not isinstance(CellType(blockTypeInt), CellType) or blockTypeInt == 1:
            raise TypeError("blockType must be an instance of CellType Enum and can't have value = 1!")

        self.blockType = CellType(blockTypeInt)
        if self.blockType == CellType.BLOCK_I_LIGHT_BLUE:
            self.rotation = "--"
        # self.angels = self.setBlockAngles()
        self.setBlockPoints(self.blockType)
        self.board = board  # reference to Board
        self.defaultP = [1, 4]   # pt.(0,0) on (0,4) board pos. default

    def setBlockPoints(self, blockType):
        match blockType:
            case CellType.BLOCK_I_LIGHT_BLUE:
                self.points = [(0,-1), (0,1), (0,2)]
            case CellType.BLOCK_O_YELLOW:
                self.points = [(0,1), (-1,0), (-1,1)]
            case CellType.BLOCK_T_PURPLE:
                self.points = [(0,-1), (0,1), (-1,0)]
            case CellType.BLOCK_J_DARK_BLUE:
                self.points = [(0,-1), (0,1), (-1,-1)]
            case CellType.BLOCK_L_ORANGE:
                self.points = [(0,-1), (0,1), (-1,1)]
            case CellType.BLOCK_S_GREEN:
                self.points = [(0,-1), (-1,0), (-1,1)]
            case CellType.BLOCK_Z_RED:
                self.points = [(0,1), (-1,0), (-1,-1)]

    # def setBlockAngles(self):
    #     if self.blockType == CellType.BLOCK_O_YELLOW:
    #         return (0)
    #     elif self.blockType == CellType.BLOCK_I_LIGHT_BLUE:
    #         return (0,1)
    #     else:
    #         return (0,1,2,3)    # (0 deg, 90 deg, 180 deg, 270 deg)

    @staticmethod
    def Generate(board):
        random_int = random.randint(2,8)
        return Block(random_int, board)

    def isBlocksEmpty(self, realPos):
        if self.board.isEmpty(realPos[0], realPos[1]):
            if not all([self.board.isEmpty(realPos[0]+self.points[i][0],
                                           realPos[1]+self.points[i][1]) for i in range(3)]):
                return False
        else:
            return False
        return True

    def apply(self):
        nextPos = (self.defaultP[0] + 1, self.defaultP[1])
        if self.isBottomEdge() or not self.isBlocksEmpty(nextPos):
            self.board.set_BlockTypeBoardCell(self.defaultP[0], self.defaultP[1], self.blockType)
            for pt in self.points:
                self.board.set_BlockTypeBoardCell(self.defaultP[0] + pt[0], self.defaultP[1] + pt[1], self.blockType)
            return True
        else:
            return False

    def moveLeft(self):
        if not self.isLeftEdge() and not self.isLeftBlock():
            self.defaultP[1] -= 1

    def moveRight(self):
        if not self.isRightEdge() and not self.isRightBlock():
            self.defaultP[1] += 1

    def moveDwon(self):
        if self.apply():
            return False # wywołanie meotdy generate
        else:
            self.defaultP[0] += 1
        return True

    def isLeftEdge(self):
        if self.defaultP[1] == 0:
            return True
        for pt in self.points:
            if self.defaultP[1] + pt[1] == 0:
                return True
        return False

    def isLeftBlock(self):
        leftBlock = (self.defaultP[0], self.defaultP[1]-1)
        if not self.board.isEmpty(leftBlock[0], leftBlock[1]):
            return True
        if all([self.board.isEmpty(leftBlock[0]+pt[0], leftBlock[1]+pt[1]) for pt in self.points]):
            return False
        return True

    def isRightEdge(self):
        if self.defaultP[1] == self.board.width-1:
            return True
        for pt in self.points:
            if self.defaultP[1] + pt[1] == self.board.width-1:
                return True
        return False

    def isRightBlock(self):
        rightBlock = (self.defaultP[0], self.defaultP[1]+1)
        if not self.board.isEmpty(rightBlock[0], rightBlock[1]):
            return True
        if all([self.board.isEmpty(rightBlock[0]+pt[0], rightBlock[1]+pt[1]) for pt in self.points]):
            return False
        return True

    def isBottomEdge(self):
        if self.defaultP[0] == self.board.height-1:
            return True
        for pt in self.points:
            if self.defaultP[0] + pt[0] == self.board.height-1:
                return True
        return False

    def isOver(self):   # implementacja po wygenrowaniu nowego bloku
       if not self.isBlocksEmpty(self.defaultP):
           return True
       return False

    def rotate(self):
        if self.blockType == CellType.BLOCK_O_YELLOW:
            pass
        elif self.blockType == CellType.BLOCK_I_LIGHT_BLUE:
            tmp = [(0,-1), (0,1), (0,2)]
            if self.rotation == "--":
                rotatedP = [(self.points[i][0] * 0 + self.points[i][1] * 1,
                             -self.points[i][0] * 1 + self.points[i][1] * 0) for i in
                            range(3)]
                if (all([(0 <= self.defaultP[0] + rotatedP[i][0] < self.board.height) for i in range(3)]) and
                        all([(0 <= self.defaultP[1] + rotatedP[i][1] < self.board.width) for i in range(3)]) and
                        all([self.board.isEmpty(self.defaultP[0] + rotatedP[i][0], self.defaultP[1] + rotatedP[i][1])
                             for i in range(3)])):
                    for i in range(3):
                        self.points[i] = rotatedP[i]
                    self.rotation = "|"
                else:
                    pass
            elif (self.rotation == "|" and all([(0 <= self.defaultP[0] + tmp[i][0] < self.board.height) for i in range(3)]) and
                        all([(0 <= self.defaultP[1] + tmp[i][1] < self.board.width) for i in range(3)]) and
                        all([self.board.isEmpty(self.defaultP[0] + tmp[i][0], self.defaultP[1] + tmp[i][1])
                             for i in range(3)])):
                self.setBlockPoints(self.blockType)
                self.rotation = "--"
        else:
            rotatedP = [(self.points[i][0]*0 + self.points[i][1]*1,
                         -self.points[i][0]*1 + self.points[i][1]*0) for i in range(3)]
            # sprawdzenie czy powstałe nowe wsp.blokow nie nachodza na inne lub nie sa poza granicami planszy
            if (all([(0 <= self.defaultP[0]+rotatedP[i][0] < self.board.height) for i in range(3)]) and
                    all([(0 <= self.defaultP[1] + rotatedP[i][1] < self.board.width) for i in range(3)]) and
                    all([self.board.isEmpty(self.defaultP[0]+rotatedP[i][0], self.defaultP[1]+rotatedP[i][1]) for i in range(3)])):
                for i in range(3):
                    self.points[i] = rotatedP[i]
            else:
                pass

    def printBlock(self):
        return [tuple(self.defaultP)] + [(self.defaultP[0]+self.points[i][0], self.defaultP[1]+self.points[i][1]) for i in range(3)]

