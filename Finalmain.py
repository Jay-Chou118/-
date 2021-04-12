import sensor, image, time,pyb
from pyb import UART

#Red_led = pyb.LED(1)
#Green_led = pyb.LED(2)
#red_threshold=（0，0，0，0，0，0）分别代表LAB三个最大值和最小值
green_threshold   = [(2, 53, -69, -10, -12, 127)] #绿色块颜色区间
red_threshold = [(5, 100, 12, 127, -22, 33)]   #红色块颜色区间
blue_threshold = [(5, 100, -128, 127, -81, -13)]   #蓝色块颜色区间


sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 格式为 RGB565.
sensor.set_framesize(sensor.QVGA) # 使用 QQVGA 速度快一些
sensor.skip_frames(time = 1500) # 跳过2000s，使新设置生效,并自动调节白平衡
sensor.set_auto_gain(False) # 关闭自动自动增益。默认开启的，在颜色识别中，一定要关闭白平衡。
sensor.set_auto_whitebal(False)
clock = time.clock()

uart = UART(3,115200)  #串口初始化
uart.init(115200,bits=8,parity=None,stop=1,timeout_char = 1000)  #波特率115200 8位发送，停止位1位


def max_blob(blobs): #求最大色块
    max_s = 0
    max_b = 0
    for b in blobs:
        if max_s < b.w() * b.h():
            max_s = b.w() * b.h()
            max_b = b
    return max_b

def find_color_blobs():
    clock.tick() # 跟踪每帧之间的毫秒数
    img = sensor.snapshot().lens_corr(1.4)
    blobs = img.find_blobs(red_threshold,x_stride = 5,y_stride = 5,merge=True)  #寻找红色块
    max_red= max_blob(blobs)
    if(max_red):
        img.draw_rectangle(max_red.rect())  #画框
        img.draw_cross(max_red.cx(),max_red.cy(),color = (255,0,0)) #画红十字
       # print("红杠宽度值:"+str(max_red.w()))
        uart.write(pack_data_1(1))

    blobs_2 = img.find_blobs(green_threshold,x_stride = 5,y_stride = 5,merge=True)  #寻找绿色块
    max_green = max_blob(blobs_2)
    if(max_green):
        img.draw_rectangle(max_green.rect())  #画框
        img.draw_cross(max_green.cx(),max_green.cy(),color = (0,255,0)) #画绿十字
       # print("绿杠宽度值:"+str(max_green.w()))
        uart.write(pack_data_1(2))
    blobs_3 = img.find_blobs(blue_threshold,x_stride = 5,y_stride = 5,merge=True)  #寻找蓝色块
    max_blue = max_blob(blobs_3)
    if(max_blue):
        img.draw_rectangle(max_blue.rect())  #画框
        img.draw_cross(max_blue.cx(),max_blue.cy(),color = (0,0,255)) #画蓝十字
      #  print("蓝杠宽度值:"+str(max_blue.w()))
        uart.write(pack_data_1(3))


def pack_data_1(flag): # #过程一 通信协议
    img = sensor.snapshot().lens_corr(1.4)
    datalist = [0xAA,0X55,flag,1,1,1,1,1,1,0x99]#0xAA 10101010 0x55 01010101
    data = bytearray(datalist)

    for code in img.find_qrcodes():
        #print(code[4])
        gg=code[4].split("+")
        if(len(gg)==2):
            if(len(gg[0])==3):
                datalist = [0xAA,0X55,flag,int(gg[0][0]),int(gg[0][1]),int(gg[0][2]),int(gg[1][0]),int(gg[1][1]),int(gg[1][2]),0x99]#0xAA 10101010 0x55 01010101
                #datalist.append(sum_checkout(datalist))
                data = bytearray(datalist)


    print(data)
    return data


def sum_checkout(data_list):  #校验和
    data_sum = 0
    for temp in data_list:
        data_sum += temp
    return (data_sum)


class receive(object):  #串口接收类
    uart_buf = []
    state = 0
    rx_data=0

R=receive()

def rx_receive(data): #串口接收函数
    if R.state==0:#如果接收的数据为0
        if data == 0xAA:
            R.state = 1
            R.uart_buf.append(data)
        else:
            R.state = 0
    elif R.state==1:#如果接收的数据为1
        if data == 0x55:
            R.state = 2
            R.uart_buf.append(data)
        else:
            R.state = 0
    elif R.state==2:#如果接收的数据为2
        if data == 19:
            R.state = 3
            R.uart_buf.append(data)
        else:
            R.state = 0
    elif R.state==3:#如果接收的数据为3
        if data == 0x01:
            R.state = 4
            R.uart_buf.append(data)
        else:
            R.state = 0
    elif R.state==4:#如果接收的数据为4
        R.state =5
        R.uart_buf.append(data)
    elif R.state==5:#如果接收的数据为5
        if data== (R.uart_buf[0] + R.uart_buf[1] + R.uart_buf[2] + R.uart_buf[3] + R.uart_buf[4])%256 :
            R.state = 0
            R.uart_buf.append(data)
            R.rx_data=R.uart_buf[4]
            R.uart_buf=[]
        else:
            R.state = 0


def uart_read_buf(uart):
    i = 0
    buf_size = uart.any()
    while i<buf_size:
        rx_receive(uart.readchar())
        i = i + 1

def uart_mode_seclet(): #返回模式
    find_mode = R.rx_data
    R.rx_data = 0
    return find_mode

while(True):
    #pyb.delay(30)
    find_color_blobs()






