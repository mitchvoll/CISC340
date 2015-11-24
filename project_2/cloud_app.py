import requests
import json
import time
import datetime
import thread

from flask import Flask, request, render_template

phone_number = '6133015848'

def get_data(thread_name, delay):
        global phone_number
	last_value = 0
	temp_count = 100
	url = 'https://api-http.littlebitscloud.cc/devices/00e04c223d3e/input'
	headers = {'Authorization': 'Bearer 6a42d1269457bc650b5730c88b53c75e69cae9cc031a91b8ca96e21694bbe36b','Accept':'application/vnd.littlebits.v2+json'}

	r = requests.get(url, headers=headers, stream=True)

	for line in r.iter_lines(): 
                print "phone_number: " + phone_number
                if line and line[:5] == 'data':
			current_value = json.loads(line[5:])['payload']['percent']
			#print current_value

			# write current time to file
			if current_value > 90 and last_value < 90:
				#print "writing time"
				f = open('time_file.txt', 'a')
				f.write(str(int(time.time())) + "\n")
				f.close()
                                requests.get("http://tw.mitchvollebregt.com/call/" + phone_number)
			# current_value is a temperature. Write to file every 20 times
			elif temp_count == 100:
				#print "writing temp"
				f = open("temp_file.txt", 'a')
                                f.write(str(int(time.time())) + ' : ' + str(current_value) + '\n')
				f.close()
				temp_count = 0
			elif current_value < 90:
                                # post temp to cloudbit
			        requests.post('https://api-http.littlebitscloud.cc/devices/00e04c223d3e/output', headers=headers, data={'percent' : current_value})

			last_value = current_value
			temp_count = temp_count + 1
			
		

# Create data read thread as follows
try:
   t = thread.start_new_thread(get_data, ("Thread-1", 1))
except:
   print "Error: unable to start thread"

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('index.html', name=None)

@app.route("/time")
def get_time():
	with open('time_file.txt') as f:
		content = f.readlines()
		return json.JSONEncoder().encode(content)

@app.route("/temp")
def get_temp():
	with open('temp_file.txt') as f:
		content = f.readlines()
		return json.JSONEncoder().encode(content)


@app.route("/test")
def test():
	return "test"

@app.route("/change_num/<number>")
def change_number(number):
    global phone_number
    print "old: " + phone_number
    phone_number = number
    print "new: " + phone_number
    return phone_number

@app.route("/get_num")
def get_num():
    global phone_number
    return phone_number

if __name__ == "__main__":
    app.run(debug=True, threaded=True)
