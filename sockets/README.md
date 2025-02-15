# Sockets

For this project I will be building a simple HTTP REST API in C.  It is going to allow me to manage a list of things to do (aka a TODO list).  It will not have any persistent memory. Therefore everytime I spin up my server it will be an empty list of todos. <br>

During this project my learning objectives are to understand:
- What a socket is and how it is represented on a Linux/UNIX system
- What are the different types of sockets
- What are the different socket domains
- How to create a socket
- How to bind a socket to an address/port
- How to listen and accept incoming traffic
- How to connect to a remote application
- What is the HTTP protocol
- How to create a simple HTTP server
<br>

A todo contains at least the following fields:

- id -> Positive integer, starting from 0
- title -> String
- description -> String
Here are the different routes that will have to be implemented:

- /todos
  - POST -> Creates a new todo
  - GET -> Retrieve all the todos
- /todos?id={id} (where {id} is a positive integer)
  - GET -> Retrieve the todo with the corresponding id
  - DELETE -> Delete the todo with the corresponding id
