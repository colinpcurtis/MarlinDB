import socket
import json
import random
import string
import pytest


def send_message(data):
    host = '127.0.0.1'
    message_size = 2000
    port = 7000 # The same port as used by the server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    serialized = json.dumps(data)
    s.sendall(bytes(serialized, encoding='ascii'))

    data = s.recv(message_size)
    s.close()
    print(f"Received: {json.loads(data.decode('ascii'))}")
    return json.loads(data.decode('ascii'))


LETTERS = string.ascii_letters

NUM_TESTS = 20

TESTS = [
    (''.join(random.choice(LETTERS) for _ in range(random.randrange(1, 10))), ''.join(random.choice(LETTERS) for _ in range(random.randrange(1, 100)))) for _ in range(NUM_TESTS)
]

@pytest.mark.parametrize("key,value", TESTS)
def test_insert(key, value):
    data = {
        "operation": "SET",
        "key": key,
        "value": value
    }

    response = send_message(data)

    assert response["status"] == "OK"
    assert response["data"] == value


@pytest.mark.parametrize("key,value", TESTS)
def test_get(key, value):
    data = {
        "operation": "GET",
        "key": key,
    }

    response = send_message(data)

    assert response["status"] == "OK"
    assert response["data"] == value


@pytest.mark.parametrize("key,value", TESTS)
def test_update(key, value):
    to_update = ''.join(random.choice(LETTERS) for _ in range(random.randrange(1, 100)))
    data = {
        "operation": "UPDATE",
        "key": key,
        "value": to_update
    }
    # update key to random string

    response = send_message(data)

    assert response["status"] == "OK"
    assert response["data"] == to_update

    # now return the test to its original state
    data = {
        "operation": "UPDATE",
        "key": key,
        "value": value
    }
    # update key to random string

    response = send_message(data)

    assert response["status"] == "OK"
    assert response["data"] == value 


@pytest.mark.parametrize("key,value", TESTS)
def test_delete(key, value):
    #TODO: figure out a way to separate these tests

    data = {
        "operation": "DELETE",
        "key": key,
    }

    response = send_message(data)

    assert response["status"] == "OK"
    assert response["data"] == value 

