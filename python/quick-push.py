import os
import sys

if (len(sys.argv) < 2):
    print("Err: too few arguments")
    exit(1)

if (sys.argv[1] == "--help"):
    print("""
USAGE
    {sys.argv[0]} file.txt}
DESCRIPTION
    Will transfer over a file or directory to your sever mirroring the path
    on your local machine.
    $HOME/path/to/file -> $HOME/external-drive/path/to/file

    Don't use it for massive file transfers.
    """)
file_to_transfer  = sys.argv[1]
user_home         = os.getenv("HOME")
server_home       = '/home/tyler/external-drive'

current_directory = os.getcwd()
server_directory  = f"{server_home}/{current_directory[len(user_home) + 1: ]}"
server_address    = os.getenv("SERVER_ADDRESS")
server_host       = os.getenv("SERVER_HOST")
server_port       = os.getenv("SERVER_PORT")


# remove_file = f"ssh -P {server_port}"
# send_file = f"rsync --delete -Prve 'ssh -p {server_port}' {file_to_transfer}/* {server_address}:{server_directory}/{file_to_transfer}"
send_file = f"rsync -Prve 'ssh -p {server_port}' {file_to_transfer}/* {server_address}:{server_directory}/{file_to_transfer}"
print(send_file)
os.system(send_file)
