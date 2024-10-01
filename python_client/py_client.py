import socket

# A minimal TCP IPV4 client that sends a message
# and saves the response in a flat file. 

# Default server connection parameters
ADDRESS = "localhost"
PORT = 8000
SERVER_INFO = tuple(ADDRESS, PORT)

# Client socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
sock.connect(SERVER_INFO)

# User sends a message to server. 
user_input = input("Input a string to send: ")
if user_input == "quit" or user_input == "Quit":
    break
user_input_bytes = bytes(user_input, "utf-8")
sock.send(user_input_bytes)
print(">> ", user_input_bytes)

# End of message token to know when to close connection. 
# The server may also send message length before-hand.
# This implementation assumes agreed up EOF token. 
EOF_TOKEN = b"----------xyzEOF"

# This is needed to know if we received the message to completion.
EOF = False
data_recv = b""
while not EOF:
    response = sock.recv(1000)
    # server closed connection
    if not response: 
        break
    # Received full message
    if b"----------xyzEOF" in response:
        EOF = True
        break
    data_recv += response
    
if EOF:
    file = open("output.txt", "ab")
    file.write(data_recv)
    file.write(b"\n--------------------------------------------\n")
    file.close()
        
# Close socket and end connection.
sock.shutdown(socket.SHUT_RDWR)
sock.close()
