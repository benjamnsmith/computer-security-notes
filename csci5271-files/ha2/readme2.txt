DESCRIPTION
===========
The password cracker takes in a plaintext file of passwords (one per line) and hashes them according to RFC 2617,
then compares the hashes to the hash sent in the HTTP packet. 

For each password, the cracker:
1) Combines it with other info in the packet to create a long string to be hashed, according to RFC 2617. 
    a) H(A1) = MD5(username || realm || password)
    b) H(A2) = MD5(method || uri)
    c) str_to_hash = H(A1) || nonce || nc || cnonce || qop || H(A2)
  * each string concatanation above (||) combines the given string with a colon character in the middle
  * for example, username || realm would evaluate to: username:realm
2) Computes MD5(str_to_hash) and compare it to the hash retrieved from the HTTP packet.

PASSWORD
========
concept