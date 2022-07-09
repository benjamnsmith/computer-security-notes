DESCRIPTION
===========
Because of the truncation, we can try usernames one character at a time to slowly recover the key. 
If we hash a 19 character username, the last letter of the input will be the first character of the key. 

H(aaaaaaaaaaaaaaaaaaa (19 a's) || K ) (but only the first char of K since the input is truncated)

Once we have discovered the first character of the key, we can use it as our 19th character of 
our inputted string, and once again try 256 chars as our 20th character until we get something that
would match the H(aaaaaaaaaaaaaaaaaa (18 a's) || K) (but only the first two chars of K).
Since the 19th character is the first known character of the key, the 20th character will be the next char of K.

We can repeat this process, shortening our fixed username string each time and replacing the end characters with 
the characters of the key we already know to be true, until we have all 20 characters of the key. 

Finally, we can verify that the key we found is equal to the true key by comparing the hashes of the empty string and
of the key we found: 

H("" || K)       = H(K) = c69ee912601d7d731f50db6e848d65aff7aea820
H(lWxZqu28wjKzyeUH9hPO) = c69ee912601d7d731f50db6e848d65aff7aea820


SERVER'S SECRET KEY
===================
lWxZqu28wjKzyeUH9hPO
