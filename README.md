# tra.c - Lightweight and scalable GVT-800 server.

Welcome to tra.c (pronounced trac)! A lightweight TCP server for handling GVT-8000 data sent by IoT devices and asynchronously save it to [redis](redis.io) server. This is part of larger Sibiil project, a complete system for tracking GPS devices.

tra.c only requires one thread to improve scalability, thanks to libev for their cool library.
