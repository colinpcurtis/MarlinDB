# MarlinDB 🐟: a simple in-memory key-value database

MarlinDB provides redis-type functionality at a much smaller scale while still being very easy to use and fast.

It has two main components.
1. A TCP-based server that holds the database and processes client messages.
2. A simple CLI that allows us to interact with the server.

## Building
MarlinDB depends on the `json-c` library.  Its installation instructions can be found on [this GitHub repo](https://github.com/json-c/json-c)
To build MarlinDB, run the following commands

```bash
git clone https://github.com/colinpcurtis/MarlinDB.git
cd MarlinDB
make        # builds the CLI
make server # builds the server
```

## Usage
To start the server, run `./server`.  It by default runs on address `127.0.0.1` and port `7000`.

To access the CLI, run `./marlin-cli <server-address> <port>`.

Then you can type commands into the prompt and get responses from the server.

## Functionality
The following operations are supported in MarlinDB.

All data is passed in JSON form with the following schema
```json
{
    "operation": <operation>,
    "key": <key>,
    "value": <value>
}
```

where `"operation"` is one of the following.

Also, if `"value"` is not needed for an operation, then we can either not pass it at all in the JSON or leave it as the empty string.

<b>SET</b>

Creates a key-value pair in the database.
Returns a string of the form `SET <key> <value>`

<b>GET</b>

Retrieves a value from the database by key.
Returns a string of the form `GET <key> <value>`

<b>UPDATE</b>

Updates the value for a particular key in the database.
Returns a string of the form `UPDATE <key> <value>`

<b>DELETE</b>

Deletes a key-value pair from the database.
Returns the deleted pair in the form `DELETE <key> <value>`


## Design
The key-value pairs in MarlinDB are stored as structs in a hash table with no chaining.  The size of the hash table is constant, and set at a large prime number.  These were chosen to prioritize a simple implementation with minimal technical overhead. Additionally, the index is chosen for the hash table based on the hash of the key.

On the server side, messages are passed through TCP as a JSON string.  This was chosen as opposed to a more complicated protocol like HTTP because it's much simpler to decode a message serialized in this form because we don't have to worry about request types.

This also means it's incredibly simple to make requests to  MarlinDB from other languages since we just have to send a TCP request to the server. The `client.py` demonstrates how to use sockets in other languages to call MarlinDB.

<!-- ## Very simple benchmarks
| Operation      | Time (s)             |
| -----------    | -----------          |
| SET            | $9.6\cdot10^{-5}$    |
| GET            | 75          |
| UPDATE         | 78          |
| DELETE         | 89          | -->


## In progress
The following functionality is going to be implemented in MarlinDB soon
- return json from server
- make script to install json-c
- multithreaded server for higher throughput when making requests to server
- improve hash function
