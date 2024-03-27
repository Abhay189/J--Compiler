# Start with the official Ubuntu base image
FROM ubuntu:latest

# Install Python, pip, and other necessary packages
# Combine apt-get update, apt-get install, and cleanup into a single RUN to reduce image layers
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    g++ \
    bison \
    flex \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip
RUN python3 -m pip install --upgrade pip

# Install Python packages
RUN pip install Flask flask_cors

# Set the working directory in the container
WORKDIR /app

# Copy your compiler engine and backend into the container
COPY Compiler-engine/ /app/Compiler-engine
COPY Compiler-Backend/ /app/Compiler-Backend

# Run make in the Compiler-Backend directory
RUN make -C /app/Compiler-Backend

# Expose the port your app runs on
EXPOSE 5000

# Command to run your Flask app
CMD ["python3", "Compiler-Backend/app.py"]
