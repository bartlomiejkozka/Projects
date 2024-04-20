from enum import Enum
import random as rd


class ChessColor(Enum):
    WHITE = 1
    BLACK = 2


class ChessDirection(Enum):
    HORIZONTAL = 1
    VERTICAL = 2
    DIAGONAL = 3


from King import King
from Queen import Queen
from Knight import Knight
from Rook import Rook
from Bishop import Bishop
from Pawn import Pawn


class Board:
    def __init__(self):
        self.dimension = (8,8)
        self._board = [[None for _ in range(self.dimension[1])] for _ in range(self.dimension[0])]

        if rd.randint(0,1) == 0:
            self.upColor = ChessColor.WHITE
            self.downColor = ChessColor.BLACK
        else:
            self.upColor = ChessColor.BLACK
            self.downColor = ChessColor.WHITE

        self.fillBoard()

        self.whiteStrikedList = []
        self.blackStrikedList = []

        self.colorMove = ChessColor.WHITE


# ===================SHORT FUNCTIONS=======================
    def __getitem__(self, key):
        return self._board[key[0]][key[1]]

    def __setitem__(self, tuplePos, chessMan):
        self._board[tuplePos[0]][tuplePos[1]] = chessMan

    def setBoardCell(self, tuplePos, chessMan, color, board=None):
        if board is None: man = chessMan(color)
        else: man = chessMan(color, board)
        self[tuplePos] = man

    def isEmptyCell(self, tuplePos):
        return self[tuplePos] == None

    def isStrike(self, stop, color):
        return self._board[stop[0]][stop[1]] != None and self._board[stop[0]][stop[1]].color != color

    def isCollision(self, stop, color):
        return self._board[stop[0]][stop[1]] != None and self._board[stop[0]][stop[1]].color == color

    def addSriked(self, stop):
        if self._board[stop[0]][stop[1]].color is ChessColor.WHITE:
            self.blackStrikedList.append(type(self._board[stop[0][stop[1]]]).__name__)
        elif self._board[stop[0]][stop[1]].color is ChessColor.BLACK:
            self.whiteStrikedList.append(type(self._board[stop[0][stop[1]]]).__name__)

    def getkingPosition(self, color):
        for row in range(self.dimension[0]):
            for col in range(self.dimension[1]):
                if isinstance(self._board[row][col], King) and self._board[row][col].color == color:
                    return (row, col)

    def changeColor(self):
        if self.colorMove == ChessColor.WHITE: self.colorMove = ChessColor.BLACK
        elif self.colorMove == ChessColor.BLACK: self.colorMove = ChessColor.WHITE



# ======================LONG FUNCTIONS======================
    def fillBoard(self):
        color = None
        for row in range(self.dimension[0]):
            if row > 1 and row < 6:
                continue
            elif row <= 1:
                color = self.upColor
            elif row >= 6:
                color = self.downColor
            for col in range(self.dimension[1]):
                if row == 0 or row == 7:
                    if col == 0 or col == 7:
                        self[(row, col)] = Rook(color)
                    elif col == 1 or col == 6:
                        self.setBoardCell((row, col), Knight, color)
                    elif col == 2 or col == 5:
                        self.setBoardCell((row, col), Bishop, color)
                    elif col == 3:
                        self.setBoardCell((row, col), Queen, color)
                    elif col == 2:
                        self.setBoardCell((row, col), King, color)
                elif row == 1 or row == 6:
                    self.setBoardCellPawn((row, col), Pawn, color, self)

#===================================

    def isObsctacleBetween(self, start, stop, directionsList):  # start, stop --> tuples

        def diagonalMove(start, stop): # return True if obstacle exist
            if stop[0] > start[0]:  # south direction
                if stop[1] > start[1]:  # south-east direction
                    return not all([self.isEmptyCell((row, col)) for row, col in
                                zip(range(start[0] + 1, stop[0]), range(start[1] + 1, stop[1]))])
                elif stop[1] < start[1]:  # south-west direction
                    return not all([self.isEmptyCell((row, col)) for row, col in
                                zip(range(start[0] + 1, stop[0]), range(start[1] - 1, stop[1], -1))])
            elif stop[0] < start[0]:  # north direction
                if stop[1] > start[1]:  # north-east direction
                    return not all([self.isEmptyCell((row, col)) for row, col in
                                zip(range(start[0] - 1, stop[0], -1), range(start[1] + 1, stop[1]))])
                elif stop[1] < start[1]:  # north-west direction
                    return not all([self.isEmptyCell((row, col)) for row, col in
                                zip(range(start[0] - 1, stop[0], -1), range(start[1] - 1, stop[1], -1))])
            else:
                raise Exception("IsObstacleBetween error: diagonalMove function\n")

        def horizontalMove(start, stop):
            if start[1] < stop[1]:
                return not all([self.isEmptyCell((start[0], x)) for x in range(start[1]+1, stop[1])])
            elif start[1] > stop[1]:
                return not all([self.isEmptyCell((start[0], x)) for x in range(start[1] - 1, stop[1], -1)])

        def verticalMove(start, stop):
            if start[0] < stop[0]:
                return not all([self.isEmptyCell((x, start[1])) for x in range(start[0]+1, stop[0])])
            elif start[0] > stop[0]:
                return not all([self.isEmptyCell((x, start[1])) for x in range(start[0] - 1, stop[0], -1)])

        for dir in directionsList:
            match dir:
                case ChessDirection.VERTICAL:
                    if start[1] == stop[1]:
                        return verticalMove(start, stop)
                    else:
                        continue

                case ChessDirection.HORIZONTAL:
                    if start[0] == stop[0]:
                        return horizontalMove(start, stop)
                    else:
                        continue

                case ChessDirection.DIAGONAL:
                    if start[0] != stop[0] and start[1] != stop[1]:
                        return diagonalMove(start, stop)
                    else:
                        continue

#===================================

    def move(self, start, stop):
        # ChessMan color check
        if self._board[start[0]][start[1]].color != self.colorMove:
            return False

        # Check if castling is
        if self.castling(start, stop):
            return True

        # Check is the move appropriate in general
        if not stop in self._board[start[0]][start[1]].validMove(start, self.dimension):
            return False

        # Check if is the obstacle on the way
        if self._board[start[0]][start[1]].isFlier is False:
            if self.isObsctacleBetween(start, stop, self._board[start[0]][start[1]].directions):
                return False

        # Check if is the on stop cell the friend ChessMan
        if self.isCollision(stop, self._board[start[0]][start[1]].color):
            return False

        # Check if is strike
        if self.isStrike(stop, self._board[start[0]][start[1]].color):
            self.addSriked(stop)

        if self._board[start[0]][start[1]] == Rook or self._board[start[0]][start[1]] == King:
            self._board[start[0]][start[1]].unmoved = False

        # Check if the pawn has moved diagonal (want to strike)
        if isinstance(self._board[start[0]][start[1]], Pawn) and stop[1] != start[1]:
            if self._board[stop[0]][stop[1]] is None:
                return False

        self._board[stop[0]][stop[1]] = self._board[start[0]][start[1]]
        self._board[start[0]][start[1]] = None
        self.addSriked(stop)
        self.changeColor()
        return True

#===================================

    # ROSZADA
    def castling(self, start, stop):
        # up-left rokade
        if start == (0, 4) and stop == (0, 2) and self._board[0][4].unmoved is True and \
                self._board[0][0].unmoved is True and all([self.isEmptyCell((0, x)) for x in range(1, 3+1)]):
            self._board[0][2] = self._board[0][4]
            self._board[0][4] = None
            self._board[0][3] = self._board[0][0]
            self._board[0][0] = None
            return True
        # up-right rokade
        elif start == (0, 4) and stop == (0, 6) and self._board[0][4].unmoved is True and \
                self._board[0][7].unmoved is True and all([self.isEmptyCell((0, x)) for x in range(5, 6+1)]):
            self._board[0][6] = self._board[0][4]
            self._board[0][4] = None
            self._board[0][5] = self._board[0][7]
            self._board[0][7] = None
            return True
        # down-left
        elif start == (7, 4) and stop == (7, 2) and self._board[7][4].unmoved is True and \
                self._board[7][0].unmoved is True and all([self.isEmptyCell((7, x)) for x in range(1, 3+1)]):
            self._board[7][2] = self._board[7][4]
            self._board[7][4] = None
            self._board[7][3] = self._board[7][0]
            self._board[7][0] = None
            return True
        # down-right
        elif start == (7, 4) and stop == (7, 6) and self._board[7][4].unmoved is True and \
                self._board[7][7].unmoved is True and all([self.isEmptyCell((7, x)) for x in range(5, 6+1)]):
            self._board[7][6] = self._board[7][4]
            self._board[7][4] = None
            self._board[7][5] = self._board[7][7]
            self._board[7][7] = None
            return True

        return False

    # ===================================

    # SZACH
    def isCheck(self, kingPos):
        for row in range(self.dimension[0]):
            for col in range(self.dimension[1]):
                if self._board[row][col].color != self.colorMove:
                    # for Knight
                    if self._board[row][col].isFlier is True:
                        if kingPos in self._board[row][col].validMove((row, col), self.dimension):
                            return [True, (row, col)]
                    # for Pawn
                    elif isinstance(self._board[row][col], Pawn):
                        if self.upColor != self.colorMove:
                            if (row + 1, col + 1) == kingPos:
                                return [True, (row, col)]
                            elif (row + 1, col - 1) == kingPos:
                                return [True, (row, col)]
                        elif self.downColor != self.colorMove:
                            if (row - 1, col + 1) == kingPos:
                                return [True, (row, col)]
                            elif (row - 1, col - 1) == kingPos:
                                return [True, (row, col)]
                    # for the rest
                    elif kingPos in self._board[row][col].validMove((row, col), self.dimension):
                        if not self.isObsctacleBetween((row, col), kingPos,
                                                       self._board[row][col].validMove((row, col), self.dimension)):
                            return [True, (row, col)]     # Check
        return [False, (0, 0)]


    # SZACH MAT
    def isCheckMate(self, kingPos):
        for position in self._board[kingPos[0]][kingPos[1]].validMove(kingPos, self.dimension[0]):
            if self.isCollision(position, self._board[kingPos[0]][kingPos[1]].color):
                continue
            elif not self.isCheck(position)[0]:
                    return False

        # sprawdzenie czy nie da sie zasłonic lub zbić
        killerPos = self.isCheck(kingPos)
        polesBetween = []

        if kingPos[0] > killerPos[0]:  # south direction
            if kingPos[1] > killerPos[1]:  # south-east direction
                polesBetween = [(row, col) for row, col in
                                zip(range(killerPos[0], kingPos[0]), range(killerPos[1], kingPos[1]))]
            elif kingPos[1] < killerPos[1]:  # south-west direction
                polesBetween = [(row, col) for row, col in
                                zip(range(killerPos[0], kingPos[0]), range(killerPos[1], kingPos[1], -1))]
        elif kingPos[0] < killerPos[0]:  # north direction
            if kingPos[1] > killerPos[1]:  # north-east direction
                polesBetween = [(row, col) for row, col in
                                zip(range(killerPos[0], kingPos[0], -1), range(killerPos[1], kingPos[1]))]
            elif kingPos[1] < killerPos[1]:  # north-west direction
                polesBetween = [(row, col) for row, col in
                                zip(range(killerPos[0], kingPos[0], -1), range(killerPos[1], kingPos[1], -1))]
        elif kingPos[0] == killerPos[0]:    # horizontal
            if kingPos[1] < killerPos[1]:
                polesBetween = [(kingPos[0], col) for col in range(killerPos[1], kingPos[1], -1)]
            elif kingPos[1] > killerPos[1]:
                polesBetween = [(kingPos[0], col) for col in range(killerPos[1], kingPos[1])]
        elif kingPos[1] == killerPos[1]:    # vertical
            if kingPos[0] < killerPos[0]:
                polesBetween = [(row, kingPos[1]) for row in range(killerPos[0], kingPos[0], -1)]
            elif kingPos[0] > killerPos[0]:
                polesBetween = [(row, kingPos[1]) for row in range(killerPos[0], kingPos[0])]


        for row in range(self.dimension[0]):
            for col in range(self.dimension[1]):
                for item in self._board[row][col].validMove((row, col), self.dimension[0]):
                    if isinstance(self._board[row][col], Pawn) and item[1] != col and item == kingPos:
                            return False
                    elif item in polesBetween:
                        return False

        return True

    # PRZELICZANIE PUNKTÓW
    # GRAFICZNE PRZEDSTAWIENIE
    # TIMER

