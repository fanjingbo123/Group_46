
//超声输入初始化
const int trig1 = 7;
const int echo1 = 6;
const int trig2 = 5;
const int echo2 = 4;
const int trig3 = 3;
const int echo3 = 2;

//电机输入输出初始化
int inputL1=8;
int inputL2=9;
int inputR1=10;
int inputR2=11;

//设定危险阈值（单位cm）
const int d_wall = 15;
const int lr_wall = 7;

//设定左右速度
const int SL = 90;
const int SR = 99;

void setup() {
  
  //所有引脚初始化输入输出模式
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  
  pinMode(inputL1,OUTPUT);
  pinMode(inputL2,OUTPUT);
  pinMode(inputR1,OUTPUT);
  pinMode(inputR2,OUTPUT);

}

//超声距离读取函数
int distance(int trigPin,int echoPin)
{
  long duration;
  int distance;
  //发射超声波
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //获取对应距离
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  //返回距离
  return distance;
}

//超声重置函数
void reset()
{
  digitalWrite(trig1, LOW);
  digitalWrite(echo1,LOW);
  digitalWrite(trig2, LOW);
  digitalWrite(echo2,LOW);
  digitalWrite(trig3, LOW);
  digitalWrite(echo3,LOW);
}

//电机运动函数
void run(int M1, int M2, int E)
{
  analogWrite(M1,E);
  analogWrite(M2,0);
}

//电机停止函数
void stop()
{
  analogWrite(inputL1,0);
  analogWrite(inputL2,0);
  analogWrite(inputR1,0);
  analogWrite(inputR2,0);
}

void loop() {

  //超声波1,2,3分别对应前、右、左
  //首先，根据超声波决定往哪边走
  //设定一个阈值，如果在这个阈值内则视为有墙壁

  
  //获取三个distance
  int d1,d2,d3;
  d1 = distance(trig1,echo1);
  d2 = distance(trig2,echo2);
  d3 = distance(trig3,echo3);

  if(d1 > d_wall+8)//如果正面没有障碍，前进一点
  {

    run(inputL1,inputL2,SL);
    run(inputR1,inputR2,SR);
    delay(200);
    stop();
        //在前进回进行靠墙测试
    if(d2 <= lr_wall)//如果贴右边墙
    {
      //倒车直到脱离危险区
      run(inputL2,inputL1,SL);
      run(inputR2,inputR1,SR);
      delay(400);
      stop();
      delay(100);
      //微量原地左转
      run(inputL2,inputL1,SL);
      delay(80);
      stop();
      //微量前进
      run(inputR1,inputR2,SR*1.2);
      run(inputL1,inputL2,SL);
      delay(500);
      stop();
      //左轮正位
      run(inputL1,inputL2,SL);
      delay(50);
      stop();
    }
    if(d3 <= lr_wall)//如果贴左边墙
    {
      //倒车直到脱离危险区
      run(inputL2,inputL1,SL);
      run(inputR2,inputR1,SR);
      delay(400);
      stop();
      delay(100);
      //微量原地右转
      run(inputR2,inputR1,SR);
      delay(80);
      stop();
      //微量前进
      run(inputR1,inputR2,SR);
      run(inputL1,inputL2,SL*1.2);
      delay(500);
      stop();
      //右轮正位
      run(inputR1,inputR2,SR);
      delay(50);
      stop();
    }
  }
  else if(d2 > d_wall+5 || d3 > d_wall+5)//如果正面有障碍但是左右有一侧没有，就准备转弯
  {
    while(d1 <= d_wall)//没有转到正就不准给我停！！！！
    {
      d1 = distance(trig1,echo1);
      if(d2 > d_wall+5)
      {
        //微量倒退
        run(inputL2,inputL1,SL);
        run(inputR2,inputR1,SR);
        delay(10);
        stop();
        //右转
        run(inputL1,inputL2,SL*1.5);
        run(inputR2,inputR1,SR*1.5);
        delay(30);
        stop();
        //微量前进
        run(inputL1,inputL2,SL);
        run(inputR1,inputR2,SR);
        delay(10);
        stop();
      }
      else if(d3 > d_wall+5)
      {
        //微量倒退
        run(inputL2,inputL1,SL);
        run(inputR2,inputR1,SR);
        delay(10);
        stop();
        //左转
        run(inputL2,inputL1,SL*1.5);
        run(inputR1,inputR2,SR*1.5);
        delay(40);
        stop();
        //微量前进
        run(inputL1,inputL2,SL);
        run(inputR1,inputR2,SR);
        delay(20);
        stop();
      }
    }
  }
  else//如果发现都不行
  {
    //如果确实到三面没有路径了
    if(d1 <= d_wall+3 && d2 <= d_wall+1 && d3 <= d_wall+1)
    {
      stop();
      delay(1000);
      while(d1 <= d_wall+5)
      {
        d1 = distance(trig1,echo1);
        run(inputL1,inputL2,SL);
        run(inputR2,inputR1,SR);
        delay(20);
        stop();
      }
      stop();
      delay(500);
    }
    else//其他情况
    {
      //微量低速前进
      run(inputL1,inputL2,SL);
      run(inputR1,inputR2,SR);
      delay(10);
      stop();
    }
  }
  stop();
}
