import SocketServer
import MySQLdb
import json
from subprocess import call, check_output
import time
import datetime

class MyTCPHandler(SocketServer.BaseRequestHandler):
    """
    The request handler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        # self.request is the TCP socket connected to the client
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
        try:
            self.data = self.request.recv(1024).strip()
            print st, "{} sent:".format(self.client_address[0])
            print self.data
            data = self.data.split()
        except:
            print("Error reading input")
        if data[0] == "q":
            db = MySQLdb.connect(host="localhost", user="rcswitch", passwd="rcswitch", db="rcswitch")
            cursor = db.cursor()
            res = []
            resDict = {}
            #cursor.execute("SET NAMES utf8")
            #cursor.execute("SET CHARACTER SET utf8")
            #cursor.execute("SET character_set_connection=utf8")
            query = "SELECT * FROM switches"
            try:
                cursor.execute(query)
                results = cursor.fetchall()
                for i in range(len(results)):
                    res.append(list(results[i]))
                for x in res:
                    namn = x[0]
                    namnIso = namn.decode('iso-8859-1')
                    resDict[str(x[2])] = {"name":namnIso, "pin":x[1], "active":x[3]} 
            except:
                print("Error: Unable to fetch data.")
            db.close()
            self.request.sendall(json.dumps(resDict))
        elif data[0] == "!":
            db = MySQLdb.connect(host="localhost", user="rcswitch", passwd="rcswitch", db="rcswitch")
            cursor = db.cursor()
            res = []
            resDict = {}
            #cursor.execute("SET NAMES utf8")
            #cursor.execute("SET CHARACTER SET utf8")
            #cursor.execute("SET character_set_connection=utf8")
            query = "SELECT pin FROM switches"
            try:
                cursor.execute(query)
                results = cursor.fetchall()
                #print(results[1])
                for x in range(len(results)):
                    try:
                        op = ["gpio", "-g", "read", str(results[x][0])]
                        pin_mode = check_output(op)
                        #print(op)
                    except:
                        print("Error: Unable to get pin modes")
                    try:
                        resDict[str(x)] = {"pin":int(results[x][0]), "state": int(pin_mode)}
                        #resDict[int(results[x][0])] = int(pin_mode)
                    except:
                        print("Error: Unable to save data to dictionary")
            except:
                print("Error: Unable to fetch data.")
            db.close()
            #print(resDict)
            self.request.sendall(json.dumps(resDict))
        else:
            if data[0].isdigit():
                pin = data[0]
            else:
                pin = "0"
            if int(check_output(["gpio", "-g", "read", pin])) == 0:
                mode = "1"
            else:
                mode = "0"
            op = ["gpio", "-g", "write", pin, mode]
            call(op)
        #call(["gpio", "-g", "write", pin, mode])
        # just send back the same data, but upper-cased
        #self.request.sendall(self.data.upper())
        #print self.data
if __name__ == "__main__":
    HOST, PORT = "192.168.1.19", 9999

    SocketServer.TCPServer.allow_reuse_address = True
    # Create the server, binding to localhost on port 9999
    server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    try:
        server.serve_forever()
    except:
        server.server_close()
