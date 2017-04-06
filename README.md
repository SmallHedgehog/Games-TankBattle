# 经典坦克大战游戏

## 开发环境与依赖

 - IDE: Virtual Studio 2012
 - 依赖库: SDL2（下载地址: https://www.libsdl.org/download-2.0.php）
 - 开发语言: C++

## 实现效果图
 - 坦克大战游戏实现效果图
![坦克大战游戏实现效果图](C:\Users\yangcaifei\Desktop\res\ProjectPictures\5.png)
![坦克大战游戏实现效果图](C:\Users\yangcaifei\Desktop\res\ProjectPictures\6.png)
_ _ _
 - 关卡编辑器实现效果图
![关卡编辑器效果图](C:\Users\yangcaifei\Desktop\res\ProjectPictures\7.png)

## 文件描述
 - StageEditor：关卡编辑器（Qt5开发）
 - res：程序中使用的资源文件
 - stage：关卡文件（由关卡编辑器程序生成）

## 类文件描述
 - BarrierClass：游戏中的障碍物类（四种障碍物类型）
 - Bullet：子弹类
 - Tank类派生DoubleTank、NormalTank、PlayerTank、TDoublesTank等类
 - Game：管理着游戏中的所有对象
 - Window：负责窗口绘制、游戏对象的绘制