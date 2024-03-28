import requests

# The URL for your Flask API endpoint
url = 'http://localhost:5000/compile'

# Example J-- code to compile
jmm_code = """main() {
        prints("Hello, world!\\n");
}"""

# The payload to send in the POST request
payload = {'code': jmm_code}

# Sending a POST request to the Flask API
response = requests.post(url, json=payload)

# Checking if the request was successful
if response.status_code == 200:
    print("Compilation Successful:")
    print(response.json().get('assembly', 'No assembly code returned.'))
else:
    print(f"Compilation Failed with status code {response.status_code}:")
    print(response.json().get('error', 'No error message provided.'))