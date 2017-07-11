# mllib
写点垃圾代码，全当个人爱好。

<br><br>
# 主要功能

## matrix.h

* 基本矩阵操作，加减乘除转置啥的
* HouseHolder变换进行QR分解
* 单边Jacobi进行SVD分解
* 使用初等行列式变换求逆
* SVD分解求伪逆

## softmax_regression.h

* 逻辑回归多分类器
* 带L2正则项的逻辑回归多分类器

## optimizer.h

* 随机梯度下降
* 动量（momentum）梯度下降
* adadelta调参的梯度下降
* 牛顿法