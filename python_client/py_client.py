import socket 
from random import randint

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("connecting")
sock.connect(("localhost", 8080))

while (True):
    strng = input("Input a string to send: ")
    if (strng == 'quit' or strng == 'Quit'):
        break
    raw = bytes(strng, 'utf-8')
    print(raw)
    sock.send(raw)

sock.shutdown(socket.SHUT_RDWR)
sock.close()
