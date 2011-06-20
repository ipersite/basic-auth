Basic Auth Program - for Squid Proxy
=======================

**Current version: 2.76b**

A program to give basic authentication based on file and (in the next version) database queries. In particular it is written for Squid Proxy.

Capabilities
-----

Now it has the capability to parse configuration file that contains the path of log files and the credentials file path, in order to give a file-based authentication.
Install script doesn't copy any configuration file for now, but you can check the syntax by opening them (you can find them in the "conf" directory).

What's new in version 2.76b
-----

* Various code checks, corrections and improvements.
* Now the building system is CMake.

TODO
-----

* Configurator class to parse configuration file (almost done)
  * Implementing GNU Bison to parse configuration file. (next version)
* Set up sqlite database interaction. Users and accesses will be saved in the database. (next version)
* Implementing MD5 hashing technologies. (next version)
* (later) Write documentation for Doxygen.
