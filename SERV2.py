
from distutils.command.clean import clean
from os.path import exists
import socket
import os
import struct
import time

import mouse
import keyboard
import win32api, win32con
#pywin32

print("Program started")
s = socket.socket()       

joystickrange = 128
 
#s.bind(('192.168.56.1', 8090 ))
s.bind(('192.168.32.148', 8090 ))
s.listen(0)                 
#s.settimeout(30)
liste_addr = []

while True:
 
    client, addr = s.accept()
    liste_addr.append(addr) 
    
    
    while True:
        # ________Joystick  1________
        #___X___
        content_1 = client.recv(1) #recois 1 bytes   
        #content_1 += client.recv(1)
        #___Y___
        content_2 = client.recv(1) #recois 1 bytes   
        #content_2 += client.recv(1)

        # ________Joystick 2________
        #___X2 ___
        content_4 = client.recv(1) #recois 1 bytes   
        #content_4 += client.recv(1)
        #___Y2___
        content_5 = client.recv(1) #recois 1 bytes   
        #content_5 += client.recv(1)

        # #______Buttons______
        content_11 = client.recv(1)

        printed = struct.unpack('b', content_1)
        printed += struct.unpack('b', content_2)
        printed += struct.unpack('b', content_4)
        printed += struct.unpack('b', content_5)
        temp = struct.unpack('b', content_11)
        printed += ( int(temp[0]) & 0x01,               #J1
                            (int(temp[0]) & 0x02) >> 1,     #J2
                            (int(temp[0]) & 0x04) >> 2,     #DOWN
                            (int(temp[0]) & 0x08) >> 3,     #LEFT
                            (int(temp[0]) & 0x10) >> 4,     #UP
                            (int(temp[0]) & 0x20) >> 5 )    #RIGHT

       # os.system("cls")
        print(printed, "\n")


        if printed[2]<=joystickrange  and printed[2] > 0:
            keyboard.press("s")
        elif printed[2]>=-joystickrange  and printed[2] < 0:            
            keyboard.press("z")
        else :
            keyboard.release("z")
            keyboard.release("s")

        if printed[3]<=joystickrange  and printed[3] > 0:
            keyboard.press("q")
        elif printed[3]>=-joystickrange  and printed[3] < 0:            
            keyboard.press("d")
        else :
            keyboard.release("q")
            keyboard.release("d")

        if printed[0]<=joystickrange  and printed[0] > 0: 
            win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, 0,30 * 2, 0, 0)
            #mouse.move(0,100, duration = 0)
        elif printed[0]>=-joystickrange  and printed[0] < 0:
            win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, 0,-30 * 2, 0, 0)       
            #mouse.move(0,-100, duration = 0)

        if printed[1]<=joystickrange  and printed[1] > 0:
            win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, -30 * 2, 0, 0, 0)
            #mouse.move(-100,0, duration = 0)
        elif printed[1]>=-joystickrange  and printed[1] < 0:            
            win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, 30 * 2, 0, 0, 0)
            #mouse.move(100,0, duration = 0)

        if printed[6] or printed[4]:  
            mouse.click('left')
        if printed[7] or printed[5]:
            keyboard.press('space')
        else: 
            keyboard.release('space')
        if printed[8]: 
            keyboard.press("shift")
        else: 
            keyboard.release('shift')

        #time.sleep(0.01)
        
        # get color value 
        if exists('~/arduinocouleur.txt'):
            fileColor = open("~/arduino/couleur.txt", "r")
            colorChar = fileColor.read(1)
        else:
            print("File couleur.txt does not exist!")

        #SEND 
        sended = "n"
        
        if (colorChar == "1"):
            sended = "g"
        elif (colorChar == "2"): 
            sended = "r"
        elif (colorChar == "3"): 
            sended = "b"
        client.send(bytes(sended, 'utf-8'))
