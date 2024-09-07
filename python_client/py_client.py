import socket 
from random import randint
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("connecting")
x= sock.connect(("localhost", 8080))

while (True):
    strng = input("Input a string to send: ")
    if (strng == 'quit' or strng == 'Quit'):
        break
    raw = bytes(strng, 'utf-8')
    sock.send(raw)
    print(">> ", raw)
    data = b""
    
    EOF = False
    while not EOF:
        response=sock.recv(1000)
        if not response:  # server closed connection
            break
        if b"----------xyzEOF" in response:  
            print("---- ", response)
            EOF=True
            break
        data += response 
        print ("---- ", response)
    if EOF: 
        file = open("output.txt", 'ab')
        file.write(data)
        file.write(b"\n------------------------------------------------------\n")
        file.close()
        break

sock.shutdown(socket.SHUT_RDWR)
sock.close()
