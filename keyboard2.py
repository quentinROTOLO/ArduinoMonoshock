from time import sleep
import mouse
import keyboard
import win32api, win32con

#win32api.SetCursorPos((10,10))
win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,0,100,0,0)

#keyboard.write("Python is an amazing programming language.")
#keyboard.press_and_release("z")
#keyboard.press_and_release("q")
#keyboard.press_and_release("s")
#keyboard.press_and_release("d")
#keyboard.press("shift")
#keyboard.release("shift")
#keyboard.press_and_release("alt")


#arg1 = X (>0 == right, <0 == left)

#arg2 = Y (>0 == up , <0 == down)

#mouse.move(0,100,absolute=False, duration = 0.1)
#keyboard.press("up")
#sleep(2)
#keyboard.release("up")
                     