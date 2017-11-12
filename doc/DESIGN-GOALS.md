
Corset Firewall
Copyright (C) 2017 David M. Syzdek <david@syzdek.net>.
All rights reserved.

Design Goals
============

Kernel Sub-system Integration:
   [ ] iptables/ip6tables (firewall)
   [ ] ipset (firewall)
   [ ] nfacct (flow accounting)
   [ ] tc (traffic policer/controller)
   [ ] iproute2 (routing)

User Space Integration:
   [ ] Syslog
   [ ] Files (local provisioning templates)
   [ ] RADIUS
   [ ] DHCPD
       [ ] ISC DHCP
       [ ] Kea DHCP
   [ ] LDAP
   [ ] SQL
       [ ] iODBC
       [ ] MariaDB
       [ ] Postgres
       [ ] SQLite


Module Types
----------------

 * Trigger (trigger) [core, netfilter_queue]
 * Authentication (authen) [radius]
 * Authorization (author) [radius]
 * session DB (db) [file]
 * provision (prov) [sql, script, netfilter, ipset, iproute2, netfilter_acct]
 * accounting poll (acct-poll) [netfilter_acct]
 * accounting push (acct-record) [radius]

