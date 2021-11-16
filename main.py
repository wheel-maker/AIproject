"""
此文件为UI文件，与五子棋算法的接口有：
    GoBang类中：
        self.ai_cal               此参数表示AI是否计算完毕，如果计算完毕置为True,否则置为False
        self.ai_piece()           此函数返回AI计算后的坐标值，为（0，0）--（14，14）
        self.game_over()          此函数返回棋局是否结束
"""
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import Qt
import numpy as np
from gobang_algoritnm import *
from judge import *

# 背景图片相关参数
BG_WIDTH = 929
BG_HEIGHT = 620

# 棋盘相关参数
BOARD_WIDTH = 540
BOARD_HEIGHT = 540
BOARD_X = 60
BOARD_Y = 50

# 按钮相关参数
BUTTON_WIDTH = 230
BUTTON_HEIGHT = 135
BUTTON_X = 650
BUTTON_Y1 = 120
BUTTON_Y2 = BUTTON_Y1 + 120
BUTTON_Y3 = BUTTON_Y2 + 120

# 其他参数
MARGIN = 22
GRID = (BOARD_WIDTH-2*MARGIN)/14
PIECE = 34

# 表示轮到谁下棋
COMPUTER = 0
PEOPLE = 1


# 棋盘类
class CheckBoard(object):
    def __init__(self):
        self.board = np.zeros((15, 15))

    def reset(self):
        for i in range(15):
            for j in range(15):
                self.board[i][j] = 0


class GoBang(QWidget):
    def __init__(self):
        super().__init__()
        self.chessboard = CheckBoard()
        self.AI = Gobang_AI()

        self.black = QPixmap("img/black.png")
        self.black2 = QPixmap("img/black2.png")
        self.white = QPixmap("img/white.png")
        self.white2 = QPixmap("img/white2.png")

        self.board_img = QLabel(self)
        self.button1 = QPushButton(self)
        self.button2 = QPushButton(self)
        self.button3 = QPushButton(self)

        self.pieces = [QLabel(self) for i in range(225)]

        self.ai_cal = True   # 表示AI已经计算完毕，可以着棋，否则鼠标按键无作用
        self.turn = PEOPLE
        self.numbers = 0
        self.win = True
        self.over = False

        self.init_ui()

    def init_ui(self):
        # 设置窗口属性
        self.resize(BG_WIDTH, BG_HEIGHT)
        self.setFixedSize(BG_WIDTH, BG_HEIGHT)
        self.setWindowTitle("五子棋游戏")

        # 绘制背景图片
        palette_back = QPalette()                               # step1:创建一个palette
        brush = QBrush(QPixmap("img/background.jpg"))           # step2:创建用于绘制背景的笔刷
        palette_back.setBrush(self.backgroundRole(), brush)     # step3:设置好调色板的笔刷
        self.setPalette(palette_back)                           # step4:设置好widget的调色板

        # 绘制五子棋棋盘
        self.board_img.setPixmap(QPixmap("img/chessboard.png"))
        self.board_img.setGeometry(BOARD_X,BOARD_Y,BOARD_WIDTH,BOARD_HEIGHT)
        self.board_img.setCursor(QCursor(QPixmap("img/black.png")))

        # 绘制三个按钮
        font_style = QFont("楷体", 20, QFont.Bold)

        self.button1.setText("新游戏")
        self.button1.setFont(font_style)
        self.button1.setStyleSheet("QPushButton{border-image:url(img/button.png)}"
                                   "QPushButton:hover{border-image:url(img/button2.png)}")
        self.button1.setGeometry(BUTTON_X, BUTTON_Y1, BUTTON_WIDTH, BUTTON_HEIGHT)
        self.button1.setCursor(Qt.PointingHandCursor)
        self.button1.clicked.connect(self.new_game)

        self.button2.setText("认输")
        self.button2.setFont(font_style)
        self.button2.setStyleSheet("QPushButton{border-image:url(img/button.png)}"
                                   "QPushButton:hover{border-image:url(img/button2.png)}")
        self.button2.setGeometry(BUTTON_X, BUTTON_Y2, BUTTON_WIDTH, BUTTON_HEIGHT)
        self.button2.setCursor(Qt.PointingHandCursor)
        self.button2.clicked.connect(self.surrender)

        self.button3.setText("退出")
        self.button3.setFont(font_style)
        self.button3.setStyleSheet("QPushButton{border-image:url(img/button.png)}"
                                   "QPushButton:hover{border-image:url(img/button2.png)}")
        self.button3.setGeometry(BUTTON_X, BUTTON_Y3, BUTTON_WIDTH, BUTTON_HEIGHT)
        self.button3.clicked.connect(self.close)
        self.button3.setCursor(Qt.PointingHandCursor)

        # 修改鼠标形状
        self.setMouseTracking(True)
        self.setCursor(Qt.ArrowCursor)

        # 修改棋子样式
        for i in range(225):
            self.pieces[i].raise_()

        self.show()

    # 重写鼠标点击事件
    def mousePressEvent(self, event):
        if event.buttons() == Qt.LeftButton and self.ai_cal is True:         # 如果按下鼠标左键且AI计算完毕
            point = event.pos()
            new_point = self.convert_position(point)
            x = new_point[0]
            y = new_point[1]

            if 0 <= x < 15 and 0 <= y < 15:         # 如果满足要求，则绘制棋子
                if self.chessboard.board[x][y] == CONST.NONEC:
                    self.draw_piece(x, y)

                    if self.over is False:                  # 如果游戏未结束，则AI下棋
                        ai_x, ai_y = self.ai_piece()
                        self.draw_piece(ai_x, ai_y)

    # 静态方法，转换坐标
    @staticmethod
    def convert_position(point):
        x = int(round((point.x()-MARGIN-BOARD_X)/GRID))
        y = int(round((point.y()-MARGIN-BOARD_Y)/GRID))
        return x, y

    # 绘制棋子，上一步棋子用对应的红色棋子标记出
    def draw_piece(self, x, y):
        self.chessboard.board[x][y] = CONST.BLACKC if self.turn == PEOPLE else CONST.WHITEC
        self.pieces[self.numbers].setPixmap(self.black2 if self.turn == PEOPLE else self.white2)
        self.pieces[self.numbers].setGeometry(int(x*GRID+MARGIN+BOARD_X-PIECE/2), int(y*GRID+MARGIN+BOARD_Y-PIECE/2),
                                              PIECE, PIECE)
        if self.numbers > 0:
            self.pieces[self.numbers-1].setPixmap(self.black if self.turn == COMPUTER else self.white)
        self.numbers += 1
        self.turn = 1 - self.turn

        self.game_over()
        if self.over is True:
            attention = "Congratulations!" if self.win is True else "You lost!"
            option = QMessageBox.question(self, attention, "New game?")
            if option == QMessageBox.Yes:
                self.new_game()
            else:
                self.close()

    # 开始新游戏
    def new_game(self):
        self.chessboard.reset()
        self.AI.reset()
        self.ai_cal = True
        self.turn = PEOPLE
        self.numbers = 0
        self.win = True
        self.over = False
        for piece in self.pieces:
            piece.clear()

    def surrender(self):
        QMessageBox.information(self, "surrender", "You are lost!")
        self.close()

    def ai_piece(self):
        self.ai_cal = False
        score = self.AI.analyse(self.chessboard.board,  2, -CONST.MAX, CONST.MAX)
        x = self.AI.dec.pos.x
        y = self.AI.dec.pos.y
        self.ai_cal = True
        return x, y

    def game_over(self):
        if self.AI.eval.gameResult == CONST.BLACKWIN or self.AI.eval.gameResult == CONST.BLACKWIN:
            self.over = True
            if self.AI.eval.gameResult == CONST.WHITEWIN:
                self.win = False
        else:
            self.over = False


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = GoBang()
    sys.exit(app.exec_())
