# http-client

Continious http client that feeds input from the user in the form of a endpoint and sends them to a pre-configured host.

## Background & Purpose

While testing the logic of a backend service on my HTTP server I had the need to easily send HTTP requests towards different endpoints from the CLI and get the response. I also wanted to practice more low-level C programming where I get to interface towards linux libraries. This was the perfect match. There are probably much better way of achieving this goal. Treat this as a hobby C project for learning purposes.


# Installation

make

see Makefile and [gnu.org/software/make](https://www.gnu.org/software/make/manual/make.html) for further details

# Configuration

HOST and PORTS for the destination to send requests towards can be configured as environment variables

| NAME    | TYPE    | DEFAULT |  DESCRIPTION    |
| ---------------- |---------------- | --------------- | --------------- |
| HTTP_HOST    | String    | "127.0.0.1"    | The hostname to send requests towards | 
| HTTP_PORT    | Integer   | 8080           | The port to send requests towards     | 


# Usage

The user will be prompted to enter the endpoint to send the request towards

```bash
127.0.0.1:8080/
Response:
HTTP/1.1 200 OK
Content-Type: application/json
Date: Tue, 04 Mar 2025 14:54:27 GMT
Content-Length: 17
Connection: close

{"message":"OK"}
```

and can after recieveing the response keep entring different endpoints and get the results.

# Limitation

As of right now all requests are GET responses with a set HEADER. Trying to figure out the best UX to achieve this.
