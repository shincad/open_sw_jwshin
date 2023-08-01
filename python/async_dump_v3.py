'''
485 packet 모니터링을 위한 program.
모니터링해서 상위 서버로 전송 
485 to ethernet converter에 소켓 클라이언트로 접속
parsing 한 데이터를 상위 소켓 서버로 접속하여 데이터 전송
설정 파일은 config-485.ini를 참조
config-485.ini 내용 
[monitoring]
ip_address = 10.10.10.199
port = 6100
[data]
send_ip_address = 10.10.10.180
send_port = 5000

raspberry pi (Linux) 실행폴더
/home/dnpsys/test/async_dump_v3.py
2023 / 05 written by jwshin
'''

import asyncio
import socket
import time
import psutil
import configparser
import sys
import os
import datetime
import re

# Client 클래스
class Client:
    #이더넷 중, eth0라는 이름을 가진 이더넷 어댑터를 찾아서 그 어댑터의 ip address를 취득
    def get_ip_address(self):
        for interface, addrs in psutil.net_if_addrs().items():
            if "eth0" in interface:
                for addr in addrs:
                    if addr.family == socket.AF_INET:
                        return addr.address
        return None

    # 클래스 초기 init 값
    def __init__(self, ip_address, port, send_ip_address, send_port):
        self.ip_address = ip_address
        self.port = port
        self.send_ip_address = send_ip_address
        self.send_port = send_port
        self.is_synced = False
        self.start_time = time.time()
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #self.send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #self.send_socket.connect((self.send_ip_address, self.send_port))
        self.send_socket = None
        self.host_address = self.get_ip_address()
        self.previous_third_and_fourth_value = None
        self.previous_fifth_and_sixth_value = None
        self.client_socket.settimeout(3)  # timeout 설정


    # 비동기 소켓 접속 함수
    async def connect(self):
        if self.client_socket:
            self.client_socket.close()
            self.is_synced = False
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.settimeout(3)  # timeout 설정
        if not self.is_synced:
            try:
                self.client_socket.connect((self.ip_address, self.port))
                self.is_synced = False
            except Exception as e:
                print(f"Error connecting to {self.ip_address}:{self.port}: {str(e)}")
                #if self.send_socket.fileno != -1:
                #    self.send_socket.send(f'PROBLEM-Linuxip:{self.host_address}|PROBLEM-Convip::{self.ip_address}'.encode())
                self.is_synced = False
                self.client_socket.close()
                await asyncio.sleep(1)
                await self.connect()

    # 데이터 취득 함수 ()
    async def handle_data(self, data):
        while len(data) >= 8:
            byte_data = data[:8]
            data = data[8:]

            if not self.is_synced:
                if (byte_data[:2] == b'\x90\x25') or (byte_data[:2] == b'\x90\x30'):
                    self.is_synced = True
                else:
                    synced_time = time.time() - self.start_time
                    if synced_time >= 5:
                        print('Packet synchronization. Reconnecting...')
                        self.client_socket.close()
                        await asyncio.sleep(1)
                        await self.connect()
                        self.is_synced = False
                        self.start_time = time.time()
                        continue 
                    else:
                        print('Packet synchronization. Reconnecting2...')
                        continue
            #print(byte_data.hex())
            if byte_data[0] in [0x00, 0x20, 0x01, 0x21, 0x02, 0x22, 0x03, 0x23, 0x04, 0x24, 0x05, 0x25, 0x06, 0x26,
                                0x07, 0x27, 0x08, 0x28, 0x09, 0x29]:
                byte_index = [0x00, 0x01, 0x20, 0x21, 0x02, 0x22, 0x03, 0x23, 0x04, 0x24, 0x05, 0x25, 0x06, 0x26,
                              0x07, 0x27, 0x08, 0x28, 0x09, 0x29].index(byte_data[0])
                # print(f"byte_data[0] = {byte_data[0]:02x}, 순서값 = {byte_index + 1}")
                # 2nd bytes table
                valid_values = [0x0f,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xaf,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9]
                if byte_data[1] == 0x20:
                    
                    #if (byte_data[2] == 0x0f) or (byte_data[2] == 0xaf) or (byte_data[2] == 0x01) or (byte_data[2] == 0x02) or (byte_data[2] == 0x03) or (byte_data[2] == 0xa1) or (byte_data[2] == 0xa2) or (byte_data[2] == 0xa3):
                    if byte_data[2] in valid_values:
                        # hex 값으로 출력
                        # print(byte_data.hex())

                        # 8개의 바이트로 나누기
                        first_byte = byte_data[0]
                        second_byte = byte_data[1]
                        third_and_fourth_byte = byte_data[2:4]
                        fifth_and_sixth_byte = byte_data[4:6]
                        seventh_byte = byte_data[6]
                        eighth_byte = byte_data[7]

                        third_and_fourth_value = third_and_fourth_byte.hex()
                        fifth_and_sixth_value = fifth_and_sixth_byte.hex()

                        if self.send_socket is not None:
                            try:
                                if (third_and_fourth_value != self.previous_third_and_fourth_value):
                                    current_time = datetime.datetime.now()
                                    formatted_time = current_time.strftime("%Y-%m-%d:%H:%M:%S.%f")
                                    formatted_time = formatted_time.replace(" ", "")
                                    formatted_time = formatted_time[:-4]
                                    # 정규식을 사용하여 숫자 추출
                                    third_and_fourth_numbers = re.findall(r'\d+', third_and_fourth_value)
                                    third_and_fourth_numbers = ''.join(third_and_fourth_numbers)
                                    # 맨 앞자리 숫자가 0이면 제거
                                    if third_and_fourth_numbers.startswith('0'):
                                        third_and_fourth_numbers = third_and_fourth_numbers[1:]
                                    self.send_socket.send(f'type:sindo4|datetime:{formatted_time}|LocalAddress:{self.host_address}|ConverterAddress:{self.ip_address}|WaitCount:{third_and_fourth_numbers}'.encode())
                                    print(f'type:sindo4|datetime:{formatted_time}|LocalAddress:{self.host_address}|ConverterAddress:{self.ip_address}|WaitCount:{third_and_fourth_numbers}')
                                    self.previous_third_and_fourth_value = third_and_fourth_value
                                if (fifth_and_sixth_value != self.previous_fifth_and_sixth_value):
                                    current_time = datetime.datetime.now()
                                    formatted_time = current_time.strftime("%Y-%m-%d:%H:%M:%S.%f")
                                    formatted_time = formatted_time.replace(" ", "")
                                    formatted_time = formatted_time[:-4]
                                    # 정규식을 사용하여 숫자 추출
                                    third_and_fourth_numbers = re.findall(r'\d+', third_and_fourth_value)
                                    third_and_fourth_numbers = ''.join(third_and_fourth_numbers)
                                    # 맨 앞자리 숫자가 0이면 제거
                                    if third_and_fourth_numbers.startswith('0'):
                                        third_and_fourth_numbers = third_and_fourth_numbers[1:]
                                    fifth_and_sixth_numbers = re.findall(r'\d+', fifth_and_sixth_value)
                                    fifth_and_sixth_numbers = ''.join(fifth_and_sixth_numbers)
                                    # 맨 앞자리 숫자가 0이면 제거
                                    if fifth_and_sixth_numbers.startswith('0'):
                                        fifth_and_sixth_numbers = fifth_and_sixth_numbers[1:]
                                    self.send_socket.send(f'type:sindo4|datetime:{formatted_time}|LocalAddress:{self.host_address}|ConverterAddress:{self.ip_address}|WaitCount:{third_and_fourth_numbers}|TellerID:{byte_index + 1}|CallNo:{fifth_and_sixth_numbers}'.encode())
                                    print(f'type:sindo4|datetime:{formatted_time}|LocalAddress:{self.host_address}|ConverterAddress:{self.ip_address}|WaitCount:{third_and_fourth_numbers}|TellerID:{byte_index + 1}|CallNo:{fifth_and_sixth_numbers}')
                                    self.previous_third_and_fourth_value = third_and_fourth_value
                                    self.previous_fifth_and_sixth_value = fifth_and_sixth_value
                            except ConnectionRefusedError:
                                print("Could not connect to server. Retrying in 5 seconds...")
                                await asyncio.sleep(5)
                            except Exception as e:
                                print('Data send error:', e)
                                print('Reconnecting...')
                                self.send_socket.close()
                                self.send_socket = None
                        else:
                            try:
                                self.send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                                self.send_socket.connect((self.send_ip_address, self.send_port))
                            except Exception as e:
                                print('Could not connect to server. Retrying in 5 seconds...')
                                await asyncio.sleep(5)

    
    async def run(self):
        await self.connect()
        while True:
            try:
                data = self.client_socket.recv(4096)
                await self.handle_data(data)
            except socket.timeout:
                print("No data received for 3 seconds")
                #self.send_socket.send(f'PROBLEM-Linuxip:{self.host_address}|PROBLEM-Convip::{self.ip_address}'.encode())
                self.is_synced = False
                self.client_socket.close()
                await asyncio.sleep(1)
                await self.connect()
            except (ConnectionResetError, ConnectionAbortedError, BrokenPipeError, TimeoutError) as e:
                print(f"Socket connection closed due to {e.__class__.__name__}: {str(e)}")
                #self.send_socket.send(f'PROBLEM-Linuxip:{self.host_address}|PROBLEM-Convip::{self.ip_address}'.encode())
                self.is_synced = False
                self.client_socket.close()
                await asyncio.sleep(1)
                await self.connect()
            except ConnectionRefusedError as e:
                print(f"Socket connection closed due to {e.__class__.__name__}: {str(e)}")
                #self.send_socket.send(f'PROBLEM-Linuxip:{self.host_address}|PROBLEM-Convip::{self.ip_address}'.encode())
                self.is_synced = False
                self.client_socket.close()
                await asyncio.sleep(1)
                await self.connect()
    async def watchdog(self):
        while True:
            if self.is_synced:
                print("Either client_socket or send_socket is not connected. Restarting the program...")
                if self.client_socket:
                    self.client_socket.close()
                    self.client_socket = None
                if self.send_socket:
                    self.send_socket.close()
                    self.send_socket = None
                os.execv(sys.executable, ['python'] + sys.argv)
            await asyncio.sleep(5)                 

if __name__ == "__main__":
    # read configuration from config.ini
    config = configparser.ConfigParser()
    config.read('/home/dnpsys/test/config-485.ini')

    # 서버의 IP 주소와 포트 번호
    ip_address = config.get('monitoring', 'ip_address')
    port = config.getint('monitoring', 'port')

    # 데이터를 전송할 서버의 IP 주소와 포트 번호
    send_ip_address = config.get('data', 'send_ip_address')
    send_port = config.getint('data', 'send_port')
    client = Client(ip_address, port, send_ip_address, send_port)
    loop = asyncio.get_event_loop()
    loop.create_task(client.run())
    loop.create_task(client.watchdog())
    loop.run_forever()

