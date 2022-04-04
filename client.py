import socket
import json

def main():
    host = '127.0.0.1'
    message_size = 2000
    port = 7000 # The same port as used by the server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    data = {
        "operation": "SET",
        "key": "hello",
        "value": "howdy partner"
    }
    serialized = json.dumps(data)
    s.sendall(bytes(serialized, encoding='ascii'))

    data = s.recv(message_size)
    s.close()
    print(f"Received: {data.decode('ascii')}")

if __name__ == "__main__":
    main()
