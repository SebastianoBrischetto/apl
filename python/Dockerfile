# Use an official Python runtime as a parent image
FROM python:3.11

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Install any needed packages specified in requirements.txt
RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt
RUN pip install Flask --upgrade

# Make port 80 available to the world outside this container
EXPOSE 80

ENV NAME World

# Run script.py when the container launches
CMD ["python", "./app.py"]
