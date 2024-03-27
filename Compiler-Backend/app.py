from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)  # This will enable CORS for all domains on all routes

@app.route('/compile', methods=['POST'])

@app.route('/compile', methods=['POST'])
def compile_code():
    try:
        # Extract the J-- code from the request
        code = request.json['code']

        # Define the path for the temporary file
        temp_file_path = 'temp.jmm'

        # Save the processed code to the temporary file
        with open(temp_file_path, 'w') as file:
            file.write(code)

        # Define the compiler command with the path to the temporary file
        command = ["../Compiler-engine/parser", os.path.abspath(temp_file_path)]

        # Execute the compiler command
        result = subprocess.run(command, capture_output=True, text=True)

        print(result.stdout)

        # Clean up by removing the temporary file
        os.remove(temp_file_path)

        if result.returncode == 0:
            # Successfully compiled, return assembly
            return jsonify(assembly=result.stdout)
        else:
            # Compilation failed, return error message
            return jsonify(error=result.stderr)
    except Exception as e:
        # Handle unexpected errors
        return jsonify(error=str(e)), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
