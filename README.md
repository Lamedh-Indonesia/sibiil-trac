[![Stories in Ready](https://badge.waffle.io/Lamedh-Indonesia/sibiil-trac.svg?label=ready&title=Ready)](http://waffle.io/Lamedh-Indonesia/sibiil-trac)

[![Throughput Graph](https://graphs.waffle.io/Lamedh-Indonesia/sibiil-trac/throughput.svg)](https://waffle.io/Lamedh-Indonesia/sibiil-trac/metrics)

# tra.c - Lightweight and scalable GVT-800 TCP server.

Welcome to tra.c (pronounced trac)! A lightweight TCP server for handling GVT-800 data sent by IoT devices and asynchronously save it to [redis](redis.io) server. This is part of larger Sibiil project, a complete system for tracking GPS devices.

tra.c only requires one thread to handle multi-thousand connections, thanks to libev for their cool library.
