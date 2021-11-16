import CONST
import numpy as np

# 原则1：相邻两个等级之间相差20倍，防止低级棋形的积累影响大局
# 原则2：眠棋要比活棋价值小很多，一般和减一的活棋价值相当
# 原则3：同等棋形，己方价值的绝对值要小于敌方价值的绝对值，保证防守的价值大于进攻，设置为两倍的差距

CONST.WHITEWIN = 1000000
CONST.BLACKWIN = -10000000
CONST.flex4_w = 50000
CONST.flex4_b = -100000
CONST.flex3_w = 400
CONST.flex3_b = -8000
CONST.flex2_w = 20
CONST.flex2_b = -50
CONST.flex1_w = 1
CONST.flex1_b = -3

CONST.block4_w = 400
CONST.block4_b = -100000
CONST.block3_w = 20
CONST.block3_b = -100
CONST.block2_w = 1
CONST.block2_b = -3

CONST.OTHER = 0

CONST.MAX = 9999999999999   # 记一个最大值
# 米字型搜索方向
CONST.RIGHT_DIR = 0     # 右方向
CONST.RIGUP_DIR = 1     # 右上方向
CONST.UPION_DIR = 2     # 上方向
CONST.LFTUP_DIR = 3     # 左上方向
# 每处棋子状况
CONST.NONEC  = 0    # 没有棋子
CONST.BLACKC = 1    # 黑棋
CONST.WHITEC = 2    # 白棋

CONST.Draw = 2      #平棋，不分胜负


class Evaluation:
    def __init__(self):
        self.score=0
        self.gameResult=0 # 0,1,2，黑棋赢，白赢，和棋

# 判断单个六元组的棋形，因为考虑到不连续的棋形，如000_00的价值与冲四相同，如果使用五元组，则考虑不到
def single_evaluate(sixchess):

    value_str = ""
    for i in range(6):
        value_str += str(int(sixchess[i]))
    # 连五
    if "11111" in value_str:
        return CONST.BLACKWIN
    if "22222" in value_str:
        return CONST.WHITEWIN

    # 连四
    if "1111" in value_str:
        if value_str == "011110":                       # 黑活四
            return CONST.flex4_b
        flex4 = ["11011", "01111", "11110"]
        for i in flex4:
            if i in value_str:                          # 黑冲四
                return CONST.block4_b
    if "2222" in value_str:
        if value_str == "022220":                       # 白活四
            return CONST.flex4_w
        flex4 = ["22022", "02222", "22220"]
        for i in flex4:
            if i in value_str:                          # 白冲四
                return CONST.block4_w

    # 连三
    if "111" in value_str or "1101" in value_str or "1011" in value_str:
        if "01110" in value_str:                        # 黑活三
            return CONST.flex3_b
        if "21112" not in value_str:
            return CONST.block3_b                   # 黑眠三
    if "222" in value_str or "2202" in value_str or "2022" in value_str:
        if "02220" in value_str:                        # 白活三
            return CONST.flex3_w
        if "12221" not in value_str:
            return CONST.block3_w                   # 白眠三

    # 连二
    if "11" in value_str or "101" in value_str:
        if "0110" in value_str:
            return CONST.flex2_b                   # 黑活二
        if "2112" not in value_str:
            return CONST.block2_b                   # 黑眠二
    if "22" in value_str or "202" in value_str:
        if "0220" in value_str:
            return CONST.flex2_w                   # 白活二
        if "1221" not in value_str:
            return CONST.block2_w                   # 白眠二

    # 连一
    if "010" in value_str:
        return CONST.flex1_b                       # 黑活一
    if "020" in value_str:
        return CONST.flex1_w                        # 白活一

    return CONST.OTHER


# 扩展棋盘
def board_extend(board):
    board_wall = np.zeros([17, 17])
    for i in range(1, 16):
        for j in range(1, 16):
            board_wall[i][j] = board[i-1][j-1]
    for i in range(17):
        board_wall[0][i] = 3
        board_wall[16][i] = 3
        board_wall[i][0] = 3
        board_wall[i][16] = 3
    return board_wall


# 计算棋盘的评估值
def evaluate(board):
    board_wall = board_extend(board)
    scores = 0
    eval = Evaluation()
    eval.gameResult = CONST.Draw
    # 横向搜索
    for i in range(17):
        for j in range(11):
            row_chess = []
            for k in range(6):
                row_chess.append(board_wall[i][j+k])
            scores = single_evaluate(row_chess)
            if scores == CONST.WHITEWIN:
                eval.gameResult = CONST.WHITEWIN
            if scores == CONST.BLACKWIN:
                eval.gameResult = CONST.BLACKWIN
            eval.score += scores

    # 纵向搜索
    for i in range(11):
        for j in range(17):
            col_chess = []
            for k in range(6):
                col_chess.append(board_wall[i+k][j])
            scores = single_evaluate(col_chess)
            if scores == CONST.WHITEWIN:
                eval.gameResult = CONST.WHITEWIN
            if scores == CONST.BLACKWIN:
                eval.gameResult = CONST.BLACKWIN
            eval.score += scores
    # 右上向搜索
    for i in range(6, 17):
        for j in range(11):
            right_up_chess = []
            for k in range(6):
                right_up_chess.append(board_wall[i-k][j+k])
            scores = single_evaluate(right_up_chess)
            if scores == CONST.WHITEWIN:
                eval.gameResult = CONST.WHITEWIN
            if scores == CONST.BLACKWIN:
                eval.gameResult = CONST.BLACKWIN
            eval.score += scores
    # 左下向搜索
    for i in range(11):
        for j in range(11):
            left_up_chess = []
            for k in range(6):
                left_up_chess.append(board_wall[i+k][j+k])
            scores = single_evaluate(left_up_chess)
            if scores == CONST.WHITEWIN:
                eval.gameResult = CONST.WHITEWIN
            if scores == CONST.BLACKWIN:
                eval.gameResult = CONST.BLACKWIN
            eval.score += scores

    return eval

