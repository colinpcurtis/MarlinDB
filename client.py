import socket

def main():
    host = '127.0.0.1'
    message_size = 2000
    port = 7000 # The same port as used by the server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    s.sendall(f'SET hi there'.encode('ascii'))
    data = s.recv(message_size)
    s.close()
    print(f"Received: {data.decode('ascii')}")

if __name__ == "__main__":
    main()
