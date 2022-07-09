PROCESS
=======
I reverse engineered the loginAuth cookie from my own user account. 
I created an account "ben" and looked at the cookie format used when I was logged
into this account:
ben2021-12-07T21%3A29%3A17Z

My cookie has the format:
(USERNAME)(YEAR)-(MONTH)-(DAY)T(HOUR)%3A(MINUTE)%3A(SECOND)T

where values in () are replaced with information about account creation, accessible from the
https://SERVER/private/profile.php?username=(USERNAME). %3A is the escape char for ':'. 

By accessing the profile page for Stephen which contains all of the necessary account creation info, 
we can reverse engineer my cookie to create a Stephen cookie:
Stephen2019-11-03T12%3A44%3A21Z

Finally, we just have to change the loginAuth cookie that currently identifies me (the ben user)
to identify Stephen by replacing its contents with that of our crafted cookie. 

The website now idenitifies me as Stephen, and the contents of https://SERVER/private/admin are accessible.

WEBSITE CONTENTS 
================
Welcome back, Stephen!
You have 5 new messages.

From	            Subject
Richard Stallman	Stuck on HA2 problem 3
Patrick Bateman	    Re: Did you return the textbook?
Lil Wayne	        Recommendation on papers?
Travis Carlson	    Delay on grading HA2
Brad DeLong	        The Ultimate Thanksgiving Movie Is: Addams Family Values

< a GIF about hacking, src='../img/hacking.gif' >


