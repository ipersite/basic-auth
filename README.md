Basic Auth Program - for Squid Proxy
=======================

A program to give basic authentication based on file and (maybe in the future) database queries. In particular it is written for Squid Proxy.

Capabilities
-----

Now it has the capability to parse configuration file that contains the path of log files and the credentials file path, in order to give a file-based authentication.
Install script doesn't copy any configuration file for now, but you can check the syntax by opening them (you can find them in the "conf" directory).

TODO
-----

* Configurator class to parse configuration file (almost done)
  * Implementing GNU Bison to parse configuration file.
* Improving logger to have a similar prototype like sprintf() for example.
