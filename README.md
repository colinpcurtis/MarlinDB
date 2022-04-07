# MarlinDB 🐟: a simple in-memory key-value database

MarlinDB provides redis-type functionality at a much smaller scale while still being very easy to use and fast.

It has two main components.
1. A TCP-based server that holds the database and processes client messages.
2. A simple CLI that allows us to interact with the server.

## Building
MarlinDB depends on the `json-c` library.  Its installation instructions can be found on [this GitHub repo](https://github.com/json-c/json-c).  The script `install.sh` installs the json-c library.
To build MarlinDB, run the following commands

```bash
git clone https://github.com/colinpcurtis/MarlinDB.git
cd MarlinDB
make install            # install json-c
make                    # builds the CLI
make marlin-server      # builds the server
```

The `make clean` command removes all executables and object files, and the `make fresh` command simiarly removes all executables and object files and also removes the `json-c` and `json-c-build` directories.

## Usage
To start the server, run `./marlin-server`.  It by default runs on address `127.0.0.1` and port `7000`.

To access the CLI, run `./marlin-cli <server-address> <port>`.

Then you can type commands into the prompt and get responses from the server.

## Functionality
The following operations are supported in MarlinDB.

All data is passed in JSON form with the following schema
```json
{
    "operation": "<operation>",
    "key": "<key>",
    "value": "<value>",
}
```

where `"operation"` is one of the following.

Also, if `"value"` is not needed for an operation, then we can either not pass it at all in the JSON or leave it as the empty string.


The data returned from the server to the client is also the following JSON form
```json
{
    "status": "<status>",
    "value": "<value>"
}
```
where "<status>" is either "OK" (request processed successfully) or "NOT_FOUND" (the key was not found in the database).

Similarly, the returned "<value>" is value that corresponds to the lookup key in the database, through a SET, GET, UPDATE, or DELETE request to the server.  There are no guarantees about the value of "value" when status is "NOT_FOUND".

<b>SET</b>

Creates a key-value pair in the database.

<b>GET</b>

Retrieves a value from the database by key.

<b>UPDATE</b>

Updates the value for a particular key in the database.

<b>DELETE</b>

Deletes a key-value pair from the database.

## Testing
There are many tests for the SET, GET, UPDATE, and DELETE operation on the database.  The server can be tested by invoking the 
`pytest` command and the testing suite is located in the `test/test_server.py` file.

The marlin-server must be running before pytest is invoked.

The testing suite also serves as a good benchmark of the number of requests that the server is able to handle at a time,
since if there are too many tests set, then multiple tests will fail with connection refused.

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
- multithreaded server for higher throughput when making requests to server
- improve hash function
