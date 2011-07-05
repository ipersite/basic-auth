Basic Authentication Program - for Squid Proxy
=======================

**Current version: 3.0**

A program to give basic authentication based on sqlite database. In particular it is written for Squid Proxy Server.

Capabilities
-----

It parses the configuration file (YAML syntax) and then it opens a sqlite database connection. If everything gone well, it starts waiting for username and passwords on stdin.
The expected syntax is:
	[username][space][password][return]

Configuration file and an empty database can be found in the root directory of the project.

What's new in version 3.0b
-----

* Various code checks, corrections and improvements.
* Complete rewrite of class authenticator.
* Added sqlite database support.
* YAML syntax in configuration file.
