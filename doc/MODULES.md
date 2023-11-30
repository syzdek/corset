
Corset Firewall
Copyright (C) 2023 David M. Syzdek <david@syzdek.net>.
All rights reserved.

Module Notes
============

Module Life Cycle
-----------------

   1. Load module
      a. mod_load()

   3. Create module context (references module)
      a. mod_initialize()

   4. Connect module (references connection)
      a. mod_connect()

   5. perform action (references context)

   6. Disconnect module
      a. mod_disconnect()

   7. Destroy module context
      a. mod_destroy()

   9. Unload module
      a. mod_unload()


Module Usages
-------------

   1. trigger
   2. cache
   3. authen (authentication)
   4. author (authorization)
   5. acct (accounting)
   6. conn (shared connection)


Proposed Modules
----------------

   * Development
     - dummy (test/prototype module)
   * System
     - ipset (Linux)
     - nfacct (Linux)
     - nfqueue (Linux)
     - pcap
   * Databases
     - LDAP
     - MySQL
     - MariaDB
     - Redis
   * Miscellaneous
     - 6RD
     - TOTP Knock
