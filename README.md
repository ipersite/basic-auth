Basic Auth Program - for Squid Proxy
=======================

**Current version: 2.7b**

A program to give basic authentication based on file and (maybe in the future) database queries. In particular it is written for Squid Proxy.

Capabilities
-----

Now it has the capability to parse configuration file that contains the path of log files and the credentials file path, in order to give a file-based authentication.
Install script doesn't copy any configuration file for now, but you can check the syntax by opening them (you can find them in the "conf" directory).

What's new in version 2.7b
-----

* New logger with argument list like printf() and similar.

TODO
-----

* Correct the important bug.
* Configurator class to parse configuration file (almost done)
  * Implementing GNU Bison to parse configuration file.
* Write documentation for Doxygen.
* Solve issue in authenticator class: when the class issue the command to reload credentials it doesn't print if the user got authenticated or not.

Notes
-----

There's a important bug in this version: if the user got authenticated correctly, if you change the password, the user can log in again using the old password until he tries to log in again with a wrong password.
