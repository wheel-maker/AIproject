# -*- coding: utf-8 -*-

from judge import *
import numpy as np
from random import randint
import time


class Evaluation:
    def __init__(self):
        self.score=0
        self.gameResult=0 # 0,1,2，黑棋赢，白赢，和棋


# 坐标x，y
class pointer:
    def __init__(self,x,y):
        self.x=x
        self.y=y


class Gobang_AI:
    def __init__(self):
        self.chessboard = np.zeros([15, 15])
        self.dec = pointer(0, 0)
        self.eval = Evaluation()

    def reset(self):
        self.chessboard = np.zeros([15, 15])
        self.dec = pointer(0, 0)
        self.eval = Evaluation()

    def random_20(self, options):
        length = len(options)
        results = []
        positions = []
        for _ in range(20):
            pos = randint(0, length - 1)
            if pos not in positions:
                results.append(options[pos])
                positions.append(pos)
        return results

    # 找到当前局势下可选择的较优的点
    def seekpoints(self, board):
        options = []                              # 将棋子周围的空位标记为可选择下的位置
        for i in range(15):
            for j in range(15):
                if board[i][j] != CONST.NONEC:
                    for row in range(-1, 2):
                        if 0 <= i + row < 15:
                            for col in range(-1, 2):
                                if 0 <= j + col < 15:
                                    if board[i+row][j+col] == CONST.NONEC:
                                        options.append(pointer(i+row, j+col))
        options = self.random_20(options)
        return options

    # analyse 函数，作用是进行Alpha,Beta剪枝,剪枝操作用递归形式完成
    def analyse(self, board, depth, alpha, beta):
        chessboard = board.copy()
        t_a = alpha
        t_b = beta
        if(depth == 0):
            self.eval = evaluate(board)
            return self.eval.score
        else:                                                   # 找到可用的10个后继节点
            points = self.seekpoints(board)

        for i in range(len(points)):                                     # 对每个结点下棋后，再递归，最后清除
            chessboard[points[i].x][points[i].y] = CONST.WHITEC if depth % 2 == 0 else CONST.BLACKC
            score = self.analyse(chessboard, depth - 1, t_a, t_b)
            if depth % 2 == 0:
                if score > t_a:
                    t_a = score
                    if t_a > t_b:
                        return t_b
                    else:
                        self.dec.pos = points[i]
            else:
                if score < t_b:
                    t_b = score
                    if t_a > t_b:
                        return t_a
                    else:
                        self.dec.pos = points[i]
            chessboard[points[i].x][points[i].y] = CONST.NONEC

        if depth % 2 == 0:
            return t_a
        else:
            return t_b









        
        
    
    

