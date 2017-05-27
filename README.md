# UTJS
Universal Train Journey System /   
Unbelievable Tricking Joy System ;-)

## 1. 引言
>**And God said, Let there be light: and there was light.**
the third verse of the Book of Genesis
### 1.1 项目简介

**通用火车旅行系统(Universal Train Journey System)**是utjs小组提交的[ACM班2017年数据结构课](https://acm.sjtu.edu.cn/wiki/Data_Structures_2017)的大作业项目。
![logo](https://github.com/Evensgn/UTJS/raw/master/manual_images/logo.png)

### 1.2 项目结构
项目实现了包含**自行编写的数据结构库**，**GUI**，**前后端分离**，**用户管理**等模块以提供用户完整的火车订票体验。

---

##2. 使用描述
>**让妈妈开心的礼物，开了又开**（让助教订票的系统，订了又订）
Apple store 中国官方网站（*Unbelivable Tricking Joy System* Team）

### 2.1 功能概述
- 对用户：
1. 登录、注册账号
2. 根据起点、终点和日期查询所有可供选择的车次、票价以及可售座位相关信息。
3. 查看自己的车票；购买、退订某日某车次车票若干功能。
4. 修改用户信息

- 对管理员
1. 前端登录添加、修改、删除运行计划
2. 设置某车次某日的开始和结束发售
3. 查询用户购票退票等信息
4. 服务器工具：导入输入格式（见下面）的文本文件
5. 服务器工具：读取日志

### 2.2 使用教程
#### 2.3.1 用户使用
- 欢迎画面
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/1.gif)
- 登录
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/2.gif)
- 已购车票、退票
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/3.gif)
- 查票、购票
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/5.gif)
- 修改密码
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/6.gif)
#### 2.3.2 管理员客户端使用
- 管理员界面
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/7.gif)
- 修改运行计划、修改发售信息
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/8.gif)
- 管理用户信息
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/9.gif)

#### 2.3.3 管理员服务器端使用
- 客户端一览
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/10.gif)
- 日志系统
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/11.gif)
- 服务器启动
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/12.gif)
- 从文本导入火车、订票信息
![gid](https://github.com/Evensgn/UTJS/raw/master/manual_images/13.gif)

### 2.3 性能

设备|性能
---|---
客户端、服务器 | 5s内启动
客户端 | 操作延时仅取决于网络延迟
服务器 | 4Mb火车数据 **4s导入**
服务器 | 80Mb订票数据 **50s导入**

---

##3. 程序结构

### 3.1 输入输出

>"**烫烫烫烫烫烫烫烫烫烫烫烫烫烫烫屯屯屯屯屯屯屯**",
visual studio说。
"�■■■■■■���■■■�����",
Qt说。

#### 3.1.1 输入

本程序的输入主要有：

- 客户端的操作（网络）
- 服务器端的文件导入
- data.bin文件的读写（用做备份或操作记录）

在客户端**不存有任何数据**，需要时向服务器进行申请，修改也向服务器提交
在服务器端程序启动时会自动读取同目录下的data.bin，若未找到则默认数据为空，找到则自动将其导入
服务器端支持文本格式的导入（导入火车车次或导入操作列表），具体的格式为：

##### 3.1.1.1 火车车次格式
```
格式：
<火车编号>
站名,日期,到达时间,停车时间,里程,<车座类型一>,<车座类型二/空>,<车座类型三/空>
<起点站名>,<yyyy-MM-dd>,起点站,<mm:ss>,0km,-,-,-
<经停站>,<yyyy-MM-dd>,<mm:ss>,<mm:ss>,<公里数km>,¥<money>,¥<money>,¥<money>
...
<经停站>,<yyyy-MM-dd>,<mm:ss>,<mm:ss>,<公里数km>,¥<money>,¥<money>,¥<money>
<终到站名>,<yyyy-MM-dd>,<mm:ss>,终到站,<公里数km>,¥<money>,¥<money>,¥<money>

样例:
C2002
站名,日期,到达时间,停车时间,里程,二等座,一等座,特等座
天津,2017-03-28,起点站,06:05,0km,-,-,-
北京南,2017-03-28,06:40,终到站,127km,¥54.5,¥65.5,¥93.5
```

##### 3.1.1.2 操作列表格式
```
格式：
<人名> <id> <bought/refunded> <票数> tickets of <火车编号> from <站点一> to <站点二> in <y-M-d>

样例：
鲁技 047066000 bought 16 一等座 tickets of G8903 from 古田北 to 福州 in 2017-4-4
```

#### 3.1.2 输出
本程序的输出主要有:

 - 前端用户界面各种查询修改页
 - 后端的logs显示具体的带时间操作记录

关于前端用户界面的输入方式**已在界面一览中介绍**。
后端日志支持的功能有：

 - 记录程序的打开关闭
 - 显示记录的读取情况
 - 记录服务的开启结束
 - 记录通信方的ip以及连接维持情况
 - 显示每次通信的协议以及部分细节
 - 记录本地文件的导入过程
 - 存放出现异常的细节

需要注意的是，所有的日志**被保存在同文件夹下的"logs.txt"**中，可以通过服务器端程序访问，也可以直接打开txt查看，为简洁考虑，**10s内的操作记录会合并为同一时间戳**。
 
 
### 3.2 数据结构
使用到的数据结构**utjs_stl**包含: `sjtu::vector` , `sjtu::set` , `sjtu::map`

#### 3.2.1  `sjtu::vector`
模板类
支持迭代器
支持push_back操作
支持中括号重载
**支持不定长二进制流输出**

#### 3.2.2  `sjtu::set`
模板类
内部实现为AVL树
支持迭代器
支持插入删除操作
**支持lower_bound**
支持按秩查找
**支持不定长二进制流输出**

#### 3.2.3  `sjtu::map`
模板类
内部实现为AVL树，使用 `sjtu::pair` 进行键-值对应
支持迭代器
支持插入删除操作
支持中括号重载
支持按秩查找
**支持不定长二进制流输出**

### 3.3 前端(GUI)
#### 3.3.1 设计哲学
>**一个致力于变好看的火车票系统——**
在这个看脸的时代，我们的UTJS酱不仅要效率高高，还要变得更好看才行呢。
UTJS酱最喜欢用**可爱**的图标按钮来让大家**愉快地**操作♪ 
没错那些**圆圆的**最可爱啦。
UTJS酱喜欢化熊猫妆，很重的那种。
**黑黑白白**的超帅的哦。
UTJS酱在用户操作成功的时候会异常兴奋。
但是操作失败的时候UTJS酱会**很伤心**呐。
UTJS酱还有好多不完善的地方。
请多多包涵哦。

>UI designer 施晓钰

#### 3.3.2 设计师心路历程
- 2017.3.30
大概是这天吧。弱鸡美工没有收到美工的任务，而是收到了一个学习github并且教会小伙伴们的任务。成就达成，虽然后面弱鸡美工并没有用到它。
- 2017.4.12
UTJS酱的第一个窗口诞生啦。一个完全没接触过QT的弱鸡美工直接开始对着QT和百度摸索出了制作窗口的正确方式。于是弱鸡美工画出了几个英文版的弹窗，为了娱乐大众还去OJ上故意输错密码提取素材。
- 2017.4.13
“UTJS酱没有图片怎么行”，于是弱鸡美工找来了大批icon并且把它们往新窗口里丢。“哇这个自带的图标真丑”，于是弱鸡美工自己琢磨着把图标给换了。
- 2017.4.14
美工隐约记得开组会的时候大家说过窗口大小不固定的话把窗口拖大之后特别丑。于是美工自己研究了一晚上把组件们重新排了个版固定了格局然后愉悦地看着它们随着窗口的变化一起挪动然后开开心心地睡觉去了。
- 2017.4.15
美工开了一个组会，得知了这个格局很丑，要把窗口固定大小，顺便还得知了英文版的窗口中国用户不友好。于是美工心塞地把组件复了原并把文字都设成了中文。为了娱乐大众美工思考了很久怎么让窗口看起来不无聊。于是美工决定让UTJS酱卖萌。
……画窗口改窗口画窗口改窗口反正都是繁琐又不怎么需要动脑的事……
- 2017.5.6
丑陋的方方的按钮被吐槽了。美工自己找了个模版画了堆按钮把所有按钮都给换了。于是UTJS酱就拥有无文字图标按钮。美工还发现macos上非常美丽的文字和排版在windows下奇丑无比并且显示不全。于是美工切到了windows系统下把文字都改了一遍。结果因为电脑分辨率不同又调了一遍（绝望.jpg。
- 2017.5.7
大家都在写代码，美工同志不会写代码（也不能两个人一起改ui）于是美工同志无聊地画起了小组自己的icon。画完以后大家还在写代码。于是美工同志又做了个动图准备做启动软件的动画。然后弱鸡美工收到了第一个代码任务！搞一个好看的listwidget出来！
- 2017.5.10
任务失败。弱鸡美工转搞tablewidget并宣称能做出一样好看的东西。然后因为不会把函数连到ui上就丢了个半成品给小伙伴。
- 2017.5.13
现在弱鸡美工在写这个文档并且表示不知道大家组装完UTJS酱之后还要做什么微小的美化工作。

#### 3.3.3 前端使用控件一览
窗口	|	所用控件
---|---
添加运行计划	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	QLineEdit
---	|	QTextEdit
---	|	Line
购买车票	|	QWidget
---	|	QPushButton
---	|	QLabel
---	|	QComboBox
---	|	QGraphicsView
---	|	QSpinBox
---	|	Line
购票失败	|	QWidget
---	|	QGraphicsView
---	|	QLabel
购票成功	|	QWidget
---	|	QGraphicsView
---	|	QLabel
管理员修改运行计划界面	|	QWidget
---	|	QCommandLinkButton
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	Line
删除车次	|	QWidget
---	|	QPushButton
---	|	QDateButton
---	|	QGraphicsView
---	|	QLabel
---	|	QLineEdit
---	|	Line
登陆界面	|	QWidget
---	|	QPushButton
---	|	QLineEdit
---	|	QCommandLinkButton
---	|	QGraphicsView
---	|	QLabel
登陆失败	|	QWidget
---	|	QGraphicsView
---	|	QLabel
---	|	QPushButton
管理员界面	|	QWidget
---	|	QPushButton
---	|	QCommandLinkButton
---	|	QGraphicsView
---	|	QLabel
---	|	Line
用户界面	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	Line
修改密码	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	QLineEdit
---	|	Line
修改发售信息	|	QWidget
---	|	QPushButton
---	|	QDateButton
---	|	QGraphicsView
---	|	QLabel
---	|	QLineEdit
---	|	Line
修改运行计划	|	QWidget
---	|	QPushButton
---	|	QDateButton
---	|	QGraphicsView
---	|	QLabel
---	|	QLineEdit
---	|	QTextEdit
---	|	Line
我的订单	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	QTableWidget
---	|	Line
退订失败	|	QWidget
---	|	QGraphicsView
---	|	QLabel
退订成功	|	QWidget
---	|	QGraphicsView
---	|	QLabel
注册	|	QWidget
---	|	QPushButton
---	|	QLineEdit
---	|	QGraphicsView
---	|	QLabel
---	|	Line
注册失败	|	QWidget
---	|	QGraphicsView
---	|	QLabel
---	|	QPushButton
火车票查询	|	QWidget
---	|	QPushButton
---	|	QLineEdit
---	|	QCheckBox
---	|	QDateButton
---	|	QGraphicsView
---	|	QLabel
---	|	QCommandLinkButton
---	|	Line
车票列表	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	QTableWidget
---	|	QCommandLinkButton
用户信息	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	QTableWidget
---	|	Line
查询用户	|	QWidget
---	|	QPushButton
---	|	QGraphicsView
---	|	QLabel
---	|	QLineEdit
---	|	Line

#### 3.3.4 前端编码心路历程

##### 3.3.4.1 开始阶段
接到了组内美工丢来的一堆名为“NEW!大框框.ui”、 “Oops.ui”、 “哈哈.ui”的ui文件，内心十分崩溃，由于Qt Designer设计出的ui文件均为裸的ui文件，无法进行调用。于是遇到了本次GUI修仙之旅中的第一个坑：“如何向Qt项目中添加一个已存在的ui文件，并进行调用”。
由于在Qt设计模式下，要调用一个ui窗口，首先得将ui封装为一个继承的类，定义出该类对象后再在main.cpp中调用。
于是我去博客中学习得以下几种可行方法：
1.	为已存在的ui文件新建.h文件和.cpp文件，根据ui的基类写好继承类的代码将其封装为类。
**（由于新建的.h和.cpp文件几乎为空文件，要自己填写代码，共27个ui文件代码量很大，复制粘帖加修改也很耗时）**
2.	在项目中新建Qt设计师类：
**（会同时生成.h和.cpp文件，用起来很舒适）**
a)	创建同名类，将其中.ui文件替换
**（由于已存在的ui中有图片素材，出现异常报错，在开始阶段还未理解素材添加机制的情况下，实践存在困难）**
b)	让美工新建Qt设计师类重新画一次窗体
由于觉得上述做法都不简单，在查遍了资料之后（此时就不得不吐槽将同一篇文章转了又转的博主们，不知道是什么心态），去咨询了卢思迪助教， 得到的结果却是：
![logo](http://littleround.cn/pictures/duihua.png)
查阅资料发现，每一个都很难实现。
鉴于向美工提出了构想2)b)之后迟迟没有回复，只能采用方法1)完成了所有ui的添加工作。
（该过程中还尝试过用uic.exe直接编译.ui文件，过程繁琐且效果并不好，于是放弃。在添加ui之后，不清楚Qt的构建编译顺序，还纠结了一段时间，在陈竞潇同学的帮助下解决，在此感谢）
	获得了27个可调用的ui之后，首先被qmake坑到，由于文件所在路径中不能存在中文字符，类似“哈哈.ui”之类的文件全部报错。打开ui之后，又看到输入窗口的变量名为默认的“linEdit_*”，而对应的内容却为“id，姓名，密码，重复密码”，这样的命名方式显然不利于后期的编程，于是花费一个晚上的时间将所有ui及控件重命名。

##### 3.3.4.2 窗体链接阶段
到了窗体链接调用环节，学习了Qt的信号槽机制后，为每一ui文件设定信号与槽，对于每一个信号，都需要在.h中声明，.cpp中实现，main.cpp中定义、引用及链接，这个过程虽然机械，但是做的时候有多爽每一位联结前端的同学都会明白。（微笑脸）

##### 3.3.4.3 前后端交互阶段
确定了交互协议之后，首先将信息从各个ui之中提取出来并封装完毕，等待后端完成之后，实现了发送与接收。除了后端变量类型char*与前端的QString转换有些繁琐，其他并未遇到太多困难。

##### 3.3.4.4 测试后优化阶段
显示车票的窗口原本画的是QListWidget，这样的显示并不优美，所以我们选择了更为复杂的QTableWidget，美工绘制好后并不会使用函数调整界面，于是上网学习之后解决了该问题。

##### 3.3.4.5 结束阶段
最后，在全部整合好之后，遇到了一些文字编码的问题，主要是中文乱码问题，在变量中可用toUtf8()之类的函数解决，显示上更换了更高版本的Qt得以解决。
至此前端已实现。

**感想:**
**1. 	前端的绘制与链接若交由一个人来做，使用方法2)b)省时省力，并且能够兼顾代码和designer两种途径来优化界面，应该会更为高效。**
**2. 	要勤于添加qDebug()，大佬打日志的好习惯大大节省了Debug的时间，令人钦佩。**



### 3.4 后端
#### 3.4.1 类定义

使用结构清晰的 OOP 的设计模式，本程序定义了以下的类：

* `Date` ： 日期类，存储 `年/月/日` 信息；
* `Time` ： 时间类，存储 `小时/分钟` 信息；
* `User` ： 存储用户信息，包括用户的 id ，姓名，分配给用户的 Hash 盐（详见 3.4.3），以及 Hash 之后的用户密码；
* `Ticket` ： 订单类，存储用户的订票或退票结果；
* `TrainStation` ： 车站类，存储列车经过的站点信息，包括到站时间、离站时间、距始发站距离、路段票价等；
* `Train` ： 列车类，存储列车信息，内部嵌套有 `TrainStation` 类型的成员；
* `TicketQuery` ： 票务查询类，用于存储用户的一次查询请求信息，包括日期、起点、终点与接受的车次类型列表。 

其中，需要进行直接传输或文件读写的类均重载了流运算符 `<<` 与 `>>` 以实现**二进制 I/O** 。

**特别的，**为了传输过程的方便，还设计了

* `Bint`
* `Bchar<int>`

两类来辅助转换标准的int与char\* 以实现**二进制 I/O** 

#### 3.4.2 数据的存储结构

后端程序将数据分存在三个自定义数据结构 `sjtu::set` 中，分别为：

* `sjtu::set<User> users` ： 用以维护用户集的数据结构，支持以用户 id 为索引进行注册用户、删除用户和修改用户信息等操作；
* `sjtu::set<Train> trains` ： 用以维护车次集的数据结构，支持按照指定条件筛选车次，按照车次 id 进行对车次的添加、删除、修改和更新发售状态等操作；
* `sjtu::set<Ticket> tickets` ： 用以维护用户订单的数据结构，绑定购票与退票操作进行更新，支持以用户 id 为索引检索订单。

#### 3.4.3 对用户密码进行安全存储

##### 3.4.3.1 对用户密码进行 Hash（SHA-256） 后存储

若将用户密码明文存储在服务器端存储，一旦服务器被入侵，攻击者将直接获得所有用户的密码。而用户很可能在多个网站的账号使用相同密码，密码泄露造成的影响范围并不局限在单个程序/网站中。因此，必须将密码进行 Hash 后存储在服务器中。需要注意的是，不能使用普通的 Hash 散列函数，而必须使用**密码学安全的加密 Hash 函数**，本程序选用了 `SHA-256` 算法。

##### 3.4.3.2 为密码 Hash 加盐（Salt）

> **每天只吃六克盐，健康清淡好生活。**  
> 减盐宣传标语

使用安全的 Hash 算法对密码进行加密后，获得密码存储文件的攻击者仍然能够通过字典破解、暴力破解、彩虹表等方式尝试破解用户密码。因此需要对密码 Hash 加盐，即在新用户注册时，使用密码学安全的随机数生成器为其生成一个盐，并将用户的密码接在盐上进行 Hash 。这样，两个具有相同密码的用户，由于他们具有不同的盐，密码的 Hash 结果也是不同的，无法通过上面的反向查表等方式进行破解。当用户修改密码时，也应重新为其生成新的盐。

下面这段代码展示了一个新用户注册的过程：

```c++
bool MainWindow::RegisterUser(const User &userToReg) {
    User newUser(userToReg);
    if (users.count(newUser) != 0) return false;
    char newHashSalt[65];
    GenerateHashSalt(newHashSalt);
    strcpy(newUser.hashSalt, newHashSalt);
    strcpy(newUser.passWord, HashPassWord(userToReg.passWord, newUser.hashSalt));
    users.insert(newUser);
    return true;
}
```

#### 3.4.4 后端功能函数

本程序的各项功能均在服务器端进行具体实现，并将操作结果发回给客户端。后端实现的功能函数原型如下：

```c++
bool RegisterUser(const User &userToReg);                                 // 注册用户
User Login(const User &userLogin);                                        // 登录尝试
bool ChangePassWord(const User &userToChg);                               // 修改密码
bool DeleteUser(const char *id);                                          // 删除用户
sjtu::vector<Ticket> GetTicketByUserId(const char *id);                   // 获取特定用户的订单
bool CancelTicket(const Ticket &ticketToCan);                             // 退票
sjtu::vector<Train> QueryTicket(const TicketQuery &ticketToQue);          // 查询车次
bool BuyTicket(const Ticket &ticketToBuy);                                // 购票
bool AddTrain(const Train &trainToAdd);                                   // 添加车次
bool DelteTrain(const Train &trainToDel);                                 // 删除车次
bool ModifyTrain(const Train &trainToMod);                                // 修改车次
bool StopTrainSale(const Train &trainToChange);                           // 停止车次发售
bool StartTrainSale(const Train &trainToChange);                          // 开始车次发售
bool CancelTicket2(const Ticket &ticketToCan);                            // 退票
void WriteLog(QString newLog);                                            // 添加日志
```

### 3.5 前后端通信

本程序调用了 `QtNetwork` 组件，通过**TCP连接**的方式来进行前后端的交互。

#### 3.5.1 交互过程

交互的过程分为**六个阶段**：
```flow
s0=>start: 建立连接
s1=>operation: 发送包大小
s2=>operation: 发送验证码
s3=>operation: 发送协议号
s4=>operation: 发送具体数据（自动分包）
s5=>inputoutput:  接收包大小
s6=>operation: 接收具体数据
s7=>end: 断开连接
s0->s1->s2->s3->s4->s5->s6->s7
```

#### 3.5.2 交互协议
具体的协议号以及对应的操作如下：

协议号	|	操作	|	前端发送类型	|	后端返回类型
---|
1	|	注册用户	|	User	|	bool
2	|	登录	|	User	|	User
3	|	修改密码	|	User	|	bool
4	|	查询本人订单	|	Bchar<17>	|	sjtu::vector<Ticket>
5	|	查询车次	|	TicketQuery	|	sjtu::vector<Train>
6	|	购票	|	Ticket	|	bool
7	|	退票	|	Ticket	|	bool
8	|	添加新车次	|	Train	|	bool
9	|	修改车次	|	Train	|	bool
10	|	删除车次	|	Train	|	bool
11	|	发售车次	|	Train	|	bool
12	|	暂停车次	|	Train	|	bool
13	|	查看用户信息	|	Bchar<17>	|	User && sjtu::vector<Ticket>

#### 3.5.3 关于验证码机制

* 验证码通过登录获得，由服务器生成
* 验证码在服务器端生存时间有限
* 登录于注册时使用特定的验证码（特定验证码**只能用于**登录或注册）
* 验证码**不包含**用户信息
* 验证码会临时的储存在客户端（对用户隐蔽）

#### 3.5.4 关于通信实现
通过下面的实现，在通信时只需**像做文件I/O一样**进行**<<**或**>>**即可完成数据的传递。 
下面给出通信的一些具体流程：

##### 3.5.4.1 服务器端
* 服务器端维护一个缓冲区，在接到连接请求时将其刷入输入缓冲区并将其转入一个**stringstream**中
* 验证验证码，不通过则不应答，读取协议号，找不到协议则不应答
* 从stringstream中通过**各数据结构支持的二进制操作**直接刷入协议所需变量
* 对后端数据结构进行相应的修改
* 将结果转为二进制刷入stringstream再放入缓冲区，并将缓冲区内容发到客户端

##### 3.5.4.2 客户端
客户端调用写好的 `communication.h` `communication.cpp` 
其中定义了 ``Communication类`` 来完成相应操作，其中提供了（非完全代码）:
```c++
class Communication : public QObject
{
public:
    QByteArray i, o;
    //two buffer
signals:
    void finishDownload();
    //a signal to remind that QByteArray o is filled
public slots:
    void communicate();
    //call this to trigger the swap of data
private:
    //some private member variables
};
```

---

##4. 开发流程
    
> **A man who dares to waste one hour of time has not discovered the value of life.**
volume I, chapter VI: "The Voyage", page 266; letter to sister Susan Elizabeth Darwin (4 August 1836)

### 4.1 开发人员

| 姓名| 角色 |  负责模块  |
| --------   | -----:  | :----:  |
| 范舟     | 组长 | 后端主体（数据处理相关），架构设计，密码安全（SHA-256） |
| 刘啸远 | 组员 | 数据结构，前后端分离，后端部分（界面、从文本导入、日志） |
| 李怿恺 | 组员 | 前端编码（按钮链接、页面跳转、发送数据），输入检查 |
|施晓钰 |组员 | 界面设计（格局规划，UI创建），美工，代码管理|


### 4.2 开发经过
```gantt
    title 项目开发流程
    section 前期学习
        目标分析       :done,a1, 2017-4-7, 7d
        模块划分     :done,after a1, 7d
        学习相关知识       : done,7d
    section 编码
        确认编码规范 :done, a2, 2017-4-7  , 7d
        各自编写相应模块 :done, a3, after a2, until 2017-5-5
        编码交流 :4d
        代码组合 :after a3, 7d
        编写文档 :2017-5-9, 4d
```
