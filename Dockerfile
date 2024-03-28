# Start with the official Python Alpine base image
FROM python:3.9-alpine

# Install g++, bison, flex, and make (assuming make is needed) with apk
RUN apk add --no-cache \
    g++ \
    bison \
    flex \
    make

# Note: pip is included with the Python images, but we can upgrade it
RUN pip install --upgrade pip

# Install Python packages
RUN pip install Flask flask_cors

# Set the working directory in the container
WORKDIR /app

# Copy your compiler engine and backend into the container
COPY Compiler-engine ./Compiler-engine
COPY Compiler-Backend ./Compiler-Backend

# Optionally, run make if your project requires it
RUN make -C ./Compiler-engine/


# Make the parser executable
RUN chmod +x ./Compiler-engine/parser

# Expose the port your app runs on
EXPOSE 5000

# Command to run your Flask app
CMD ["python3", "./Compiler-Backend/app.py"]

