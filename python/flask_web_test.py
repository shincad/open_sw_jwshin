from flask import Flask, request, render_template
import xml.etree.ElementTree as ET
import threading
import time
import configparser

app = Flask(__name__)

data_dict_list = []
lock = threading.Lock()

@app.route('/', methods=['GET', 'POST'])
def receive_data():
    global data_dict_list

    if request.method == 'POST':
        data_str = request.data.decode('utf-8')
        print(data_str)  # Print data to the server console

        # Parse the XML data
        root = ET.fromstring(data_str)
        data_dict = {}

        for element in root.iter():
            if element.tag in ['callno', 'tellerid', 'waitcount', 'branch_name','group_name','event_time']:
                data_dict[element.tag] = element.text

        if data_dict:
            with lock:
                update_data_dict_list(data_dict)

        return ''

    # Render the template with the data
    with lock:
        return render_template('index.html', data_list=data_dict_list)


def update_data_dict_list(new_data_dict):
    global data_dict_list

    for data_dict in data_dict_list:
        if data_dict.get('branch_name') == new_data_dict.get('branch_name') and data_dict.get('group_name') == new_data_dict.get('group_name'):
            data_dict['callno'] = new_data_dict.get('callno', data_dict.get('callno', ''))
            data_dict['tellerid'] = new_data_dict.get('tellerid', data_dict.get('tellerid', ''))
            data_dict['waitcount'] = new_data_dict.get('waitcount', data_dict.get('waitcount', ''))
            data_dict['event_time'] = new_data_dict.get('event_time', data_dict.get('event_time', ''))
            return

    data_dict = {}
    data_dict['tellerid'] = new_data_dict.get('tellerid', '')
    data_dict['callno'] = new_data_dict.get('callno', '')
    data_dict['waitcount'] = new_data_dict.get('waitcount', '')
    data_dict['branch_name'] = new_data_dict.get('branch_name', '')
    data_dict['group_name'] = new_data_dict.get('group_name', '')
    data_dict['event_time'] = new_data_dict.get('event_time', '')

    data_dict_list.append(new_data_dict)


if __name__ == '__main__':
    config = configparser.ConfigParser()
    config.read('conf.ini')
    host = config['SERVER']['host']
    port = int(config['SERVER']['port'])

    app.template_folder = 'templates'  # Set the template folder to current directory
    app.run(host=host, port=port, debug=True)

if __name__ == '__main__':
    # Refresh the data every 10 seconds
    def refresh_data():
        while True:
            with lock:
                data_dict_list.clear()
            time.sleep(10)


    refresh_thread = threading.Thread(target=refresh_data)
    refresh_thread.start()
