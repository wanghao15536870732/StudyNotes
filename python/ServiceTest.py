import socket
import json
import numpy as np
import time

def getip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("www.baidu.com", 0))
        ip = s.getsockname()[0]
        print(ip)
    except:
        ip = "x.x.x.x"
    finally:
        s.close()
    return ip


print("start socket: TCP...")
socket_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

HOST_IP = getip()
HOST_PORT = 7653

print("tcp server listen @ %s:%d!" % (HOST_IP, HOST_PORT))
host_addr = (HOST_IP, HOST_PORT)
socket_tcp.bind(host_addr)
socket_tcp.listen(1)

while True:
    print("waiting for connection...")
    socket_con, (client_ip, client_port) = socket_tcp.accept()
    print("connectionaccepted from %s." % client_ip)

    # socket_con.send(b"welcome!")

    while True:
        try:
            data = socket_con.recv(999999)
            datastr = data.decode()
            print(datastr)
            if datastr == "3":
                print(datastr)

                sendData = {
                    '1': 3,
                    '2': "应用端退出",
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "6":
                print(datastr)

                sendData = {
                    '1': 6,
                    '2': "连接中断",
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "4":
                print(datastr)
                sendData = {
                    '1': 4,
                    '2': "这是椅子，确信度为87.6%"
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "5":
                print(datastr)
                sendData = {
                    '1': 5,
                    '2': "前方有障碍物",
                    '3': "左下方，距离1.33米"
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "53":
                print(datastr)
                sendData = {
                    '1': 5,
                    '2': "前方有障碍物",
                    '3': "左下方，距离1.33米"
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "7":
                print(datastr)
                sendData = {
                    '1': 7,
                    '2': "关闭系统",
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "8":
                print(datastr)
                sendData = {
                    '1': 8,
                    '2': "重启系统",
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "90":
                print(datastr)

                sendData = {
                    '1': 90,
                    '2': "开始记录",
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)
            if datastr == "91":
                print(datastr)
                sendData = {
                    '1': 91,
                    '2': "记录结束",
                }
                print(sendData)
                messagestr = json.dumps(sendData)
                message = bytes(messagestr, encoding="utf8")
                socket_con.send(message)

        except:
            print("cash one !")



