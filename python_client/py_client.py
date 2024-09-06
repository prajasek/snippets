import socket 
from random import randint

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("connecting")
sock.connect(("localhost", 8080))
print("connected...")
sock.send(b'this is from Python client ' + bytes(str(randint(1,10000)), 'utf-8'))
print("sent...")

sock.shutdown(socket.SHUT_RDWR)
