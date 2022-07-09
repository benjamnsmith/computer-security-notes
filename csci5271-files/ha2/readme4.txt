DESCRIPTION
===========
The web server uses the user's input directly in the SQL query. Because of this, a SQL injection 
is possible. The creators tried to subvert this by only giving a user interface for SQL requests
via a HTML form that submits a POST request. However, the packet can be intercepted and modified
to provide any user chosen string to the database. The SQL query most likely looks like some
form of the following: 

SELECT Username, Picture, Thought FROM Database WHERE Picture='$INPUT' AND username='aditya'

Note in the above SQL requests the single quotes around the input variable are a part of the request.
To craft our malicious reuqest, we first have to "escape" the string that our request is placed in, 
then create a new SQL parameter that will return the thought of alice. The webpage displays a table
upon a successful request, and we can assume that the SQL database is set up in a similar way. Thus,
we can assume that the users are stored in a column called user, users, or username. With some trial
and error, we can figure out the correct column name and get alice's thoughts. 

SQL REQUEST USED
==============
char-kway-teow.jpg'OR username='alice''

When we insert this into the supposed query: 

SELECT Username, Picture, Thought FROM Database WHERE Picture='char-kway-teow.jpg'OR username='alice'''

Note the double single quote at the end of the input string, which matches with the end single quote
already present in the SQL query.
This request returns both aditya and alice's thoughts on char-kway-teow.jpg


ALICE'S SECRET THOUGHT
======================
The best char kway teow is Penang char kway teow (lat: 5.411135 / lng: 100.330455)