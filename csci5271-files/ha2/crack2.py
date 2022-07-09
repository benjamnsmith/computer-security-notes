import hashlib
import sys

#    DEFINITIONS FROM RFC 2617    #
# KD(secret, data) = H(concat(secret, ":", data))
# H(data) = MD5(data)
# request-digest = <"> KD(H(A1), unq(nonce-value) ":" nc-value ":" unq(cnonce-value) ":" unq(qop-value) ":" H(A2)) <">
# A1 = unq(username-value) ":" unq(realm-value) ":" passwd
# A2 = Method ":" digest-uri-value


# RAW INFO FROM PACKET
username = "travis7"
realm = "Cheese"
nonce = "opdwqpPSBQA=d120d826af562c9b115bed0533d620c9389f1bae"
uri = "/secret/cheese"
cnonce = "OTZjMzJlNDY5OTFkNTZhNmQyYThjN2U2NWJmMDdiYjU="
nc = "00000001"
qop = "auth"
uri = "/secret/cheese"

response = "eca7d20b6541fb51eb98aa3f0b70c785"


def create_response(password):
    a1 = username + ":" + realm + ":" + password
    a2 = "HEAD" + ":" + uri
    HA1 = hashlib.md5(a1.encode()).hexdigest()
    HA2 = hashlib.md5(a2.encode()).hexdigest()
    str_to_hash = HA1 + ":" + nonce + ":" + nc + ":" + cnonce + ":" + qop + ":" + HA2
    return hashlib.md5(str_to_hash.encode()).hexdigest()

def file_mode(fd):
    count = misses = lines = 0
    for l in fd:
        lines += 1
    fd.seek(0)
    print("\nWOW! Found", lines, "passwords to try.")
    print("Now trying passwords...")
    while (count + misses) < lines:
        try:
            try:
                pw = fd.readline()
                pw = pw.lower()
                if pw[-1] == '\n':
                    pw = pw[0:-1]
                hash = create_response(pw)
                if hash == response:
                    print("H4CK3D! PASSWORD:", pw)
                    return
                count += 1
            except UnicodeDecodeError:
                misses += 1
                continue
        except KeyboardInterrupt:
            print("\nOk, let's be done. You tried:", count, "passwords.")
            return
    print("\nDarn, no passwords found out of the", count, "words tried.")


def interactive_mode():
    count = 0
    while True:
        try:
            pw = input("\nPlease enter your guess: ")
            hash = create_response(pw)
            print("guess:", pw)
            print("hash: ", hash)
            print("goal: ", response)
            if hash == response:
                print("H4CK3D! PASSWORD:", pw)
                count += 1
                raise KeyboardInterrupt
            else:
                print(pw, "is not correct")
            count += 1
        except KeyboardInterrupt:
            print("\nOk, let's be done. You tried:", count, "passwords.")
            return

### DRIVER CODE ###
if len(sys.argv) == 1:
    print("* INTERACTIVE MODE *")
    interactive_mode()
if len(sys.argv) == 2:
    print("* FILE INPUT MODE *")
    filename = sys.argv[1]
    print("opening file " + filename + "...")
    fd = open(filename, "r")
    file_mode(fd)