import Board as br
import Block as bl
import pygame
import random


class Render:
    def __init__(self, CellDimension):
        self.__board = br.Board(10, 20)
        self.__block = bl.Block.Generate(self.__board)

        pygame.init()
        pygame.display.init()
        pygame.font.init()

        self.cellDim = CellDimension  # in pixels
        self.display = pygame.display.set_mode((self.__board.width * self.cellDim, self.__board.height * self.cellDim))
        pygame.display.set_caption("Tetris Game")
        self.clock = pygame.time.Clock()

        self.move_down_timer = pygame.USEREVENT + 1
        self.speed = 500
        self.speedLevel = 1
        pygame.time.set_timer(self.move_down_timer, self.speed)

        self.scoreFont = pygame.font.Font(None, 40)
        random.seed(10)


    def drawBlock(self, blockType, row, col):
        pygame.draw.rect(self.display, self.getBlockColor(blockType)[0], (col * self.cellDim, row * self.cellDim, self.cellDim, self.cellDim))

        pygame.draw.line(self.display, self.getBlockColor(blockType)[1], (col * self.cellDim, row * self.cellDim), (col * self.cellDim + self.cellDim-2, row * self.cellDim), 2)
        pygame.draw.line(self.display, self.getBlockColor(blockType)[1], (col * self.cellDim + self.cellDim-2, row * self.cellDim), (col * self.cellDim + self.cellDim-2, row * self.cellDim + self.cellDim-2), 2)
        pygame.draw.line(self.display, self.getBlockColor(blockType)[1], (col * self.cellDim + self.cellDim-1, row * self.cellDim + self.cellDim-2), (col * self.cellDim, row * self.cellDim + self.cellDim-2), 2)
        pygame.draw.line(self.display, self.getBlockColor(blockType)[1], (col * self.cellDim, row * self.cellDim + self.cellDim-2), (col * self.cellDim, row * self.cellDim + 1), 2)

        pygame.draw.line(self.display, self.getBlockColor(blockType)[2], (col * self.cellDim + 2, row * self.cellDim + 3), (col * self.cellDim + self.cellDim-4, row * self.cellDim + 3), 4)
        pygame.draw.line(self.display, self.getBlockColor(blockType)[2], (col * self.cellDim + self.cellDim-5, row * self.cellDim + 3), (col * self.cellDim + self.cellDim-5, row * self.cellDim + self.cellDim-3), 4)
        pygame.draw.line(self.display, self.getBlockColor(blockType)[2], (col * self.cellDim + self.cellDim-5, row * self.cellDim + self.cellDim-5), (col * self.cellDim + 2, row * self.cellDim + self.cellDim-5), 4)
        pygame.draw.line(self.display, self.getBlockColor(blockType)[2], (col * self.cellDim + 3, row * self.cellDim + self.cellDim-5), (col * self.cellDim + 3, row * self.cellDim + 4), 4)


    def getBlockColor(self, blockType):
        match blockType:
            case br.CellType.EMPTY:
                return [(0, 0, 0), (40,40,40), (0, 0, 0)]
            case br.CellType.BLOCK_I_LIGHT_BLUE:
                return [(37, 200, 245), (255, 255, 255), (105, 173, 224)]
            case br.CellType.BLOCK_O_YELLOW:
                return [(231, 245, 37), (255, 255, 255), (224, 216, 99)]
            case br.CellType.BLOCK_T_PURPLE:
                return [(221, 37, 245), (255, 255, 255), (214, 111, 232)]
            case br.CellType.BLOCK_J_DARK_BLUE:
                return [(22, 14, 171), (255, 255, 255), (71, 72, 112)]
            case br.CellType.BLOCK_L_ORANGE:
                return [(217, 101, 24), (255, 255, 255), (237, 186, 104)]
            case br.CellType.BLOCK_S_GREEN:
                return [(34, 217, 24), (255, 255, 255), (102, 232, 126)]
            case br.CellType.BLOCK_Z_RED:
                return [(217, 24, 24), (255, 255, 255), (237, 100, 111)]


    def changeGameSpeed(self):
        if pygame.time.get_ticks() >= 10000 * self.speedLevel:
            self.speed -= 10
            self.speedLevel += 1
            pygame.time.set_timer(self.move_down_timer, self.speed)


    def run(self):
        running = True

        while running:
            self.changeGameSpeed()

            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_LEFT:
                        self.__block.moveLeft()
                    elif event.key == pygame.K_RIGHT:
                        self.__block.moveRight()
                    elif event.key == pygame.K_DOWN:
                        if not self.__block.moveDwon():
                            self.__block = bl.Block.Generate(self.__board)
                            if self.__block.isOver():
                                running = False
                    elif event.key == pygame.K_UP:
                        self.__block.rotate()

                if event.type == self.move_down_timer:
                    if not self.__block.moveDwon():
                        self.__block = bl.Block.Generate(self.__board)
                        if self.__block.isOver():
                            running = False

                if event.type == pygame.QUIT:
                    running = False

            self.__board.removeRow()
            self.display.fill((255,255,255))

            for i in range(self.__board.height):
                for j in range(self.__board.width):
                    if (i, j) in self.__block.printBlock():
                        self.drawBlock(self.__block.blockType, i, j)
                    else:
                        self.drawBlock(self.__board.get_boardCell(i,j), i, j)

            scoreSurface = self.scoreFont.render(str(self.__board.points), False, 'Green')
            self.display.blit(scoreSurface, (12, 7))
            pygame.display.update()
            self.clock.tick(60)


