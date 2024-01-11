# Use an official Golang runtime as a parent image
FROM golang:latest

WORKDIR /golang

COPY src /golang

# Expose port 8080 for the Go server
EXPOSE 8080

# Run the Go server
CMD ["go", "run", "main.go"]
