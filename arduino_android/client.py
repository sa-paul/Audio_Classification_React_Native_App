import socket
# Create a socket object
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Get the IP address of the local machine using the host name
host = socket.gethostbyname(socket.gethostname())
# Specify the port number
port = 8080
# Connect to the server
client.connect((host, port))
# Send data to the server
response = client.recv(1024)
# Print the server's response
print(f"Server: {response.decode('utf-8')}")
# Close the client socket
client.send(b"Hello!! I am client written in python.")
# Receive the response from the server (up to 1024 bytes)
client.close()
