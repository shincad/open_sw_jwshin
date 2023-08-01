from flask import Flask, request, render_template
import configparser
import requests
from datetime import datetime

app = Flask(__name__)

config = configparser.ConfigParser()
config.read('conf2.ini')
host = config['SERVER']['host']
port = int(config['SERVER']['port'])
whost = config['SERVER']['whost']
wport = int(config['SERVER']['wport'])

@app.route('/', methods=['GET', 'POST'])
def receive_data():
    if request.method == 'POST':
        data_str = request.data.decode('utf-8')
        data_list = data_str.split('\n')
        data_list = [data.split('&') for data in data_list]
        data_dict_list = [dict(item.split('=') for item in data) for data in data_list]

        print(data_dict_list)  # Print data to the server console

        # Generate XML content
        xml_content = '<?xml version="1.0" encoding="UTF-8" ?>\n'
        xml_content += '<GroupSet>\n'
        #xml_content += f'<Today>{datetime.now().strftime("%Y-%m-%d")}</Today>\n'
        #xml_content += '<Status>0</Status>\n'  # You can modify the status value as needed

        for data in data_dict_list:
            wait_count = data.get("WaitCount")
            if wait_count is not None:
                wait_count = wait_count.strip('"')
            call_no = data.get("CallNo")
            if call_no is not None:
                call_no = call_no.strip('"')
            xml_content += f'<datetime>{data.get("datetime")}</datetime>\n'
            xml_content += f'<LocalAddress>{data.get("LocalAddress")}</LocalAddress>\n'
            xml_content += f'<ConverterAddress>{data.get("ConverterAddress")}</ConverterAddress>\n'
            xml_content += '<Group>\n'
            xml_content += f'<GroupNo>{data.get("GroupNo")}</GroupNo>\n'
            xml_content += f'<WaitCount>{wait_count}</WaitCount>\n'
            xml_content += f'<CallNo>{call_no}</CallNo>\n'
            xml_content += f'<TellerID>{data.get("TellerID")}</TellerID>\n'
            xml_content += '</Group>\n'

        xml_content += '</GroupSet>'

        print(xml_content)  # Print XML content to the server console

        # Save data as output.xml
        with open('output.xml', 'w') as f:
            f.write(xml_content)

        # Send stored XML data to Web
        url = f'http://{whost}:{wport}'
        headers = {'Content-Type': 'application/xml'}
        with open('output.xml', 'r') as f:
            xml_data = f.read()
        response = requests.post(url, data=xml_data, headers=headers)

        return data_dict_list

if __name__ == '__main__':
    app.run(host=host, port=port, debug=True)
