#include <SPI.h>
#include <Ethernet.h>

const int SPEAKER_IN = 2;
const int DOT = 400;
const int DASH = DOT * 3;
const int BETWEEN_CHARACTER = DOT;
const int BETWEEN_LETTER = DOT * 3;
const int BETWEEN_WORDS = DOT * 7;
const int BUZZ = 1200;

String message = "Hello. I'm Scott.";

byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xFE, 0x02
};

EthernetClient tempClient;
EthernetServer server(80); 
IPAddress ip(192, 168, 7, 177);
char serverIP[] = "192.168.7.50";

boolean currentLineIsBlank = true;
boolean inJson = false;
String response = "";

void setup() {
  // Speaker pin  
  pinMode(SPEAKER_IN, INPUT);
  Serial.begin(9600);
  // this check is only needed on the Leonardo:
  Serial.println("Almost started!");

  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Connected...");
  // print your local IP address:
  printIPAddress();
//  message = formatMessage(message);
//  Serial.println(message);

// give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
//  server.begin();
//  Serial.print("server is at ");
//  Serial.println(Ethernet.localIP())

  // if you get a connection, report back via serial:
  while(!tempClient.connect(server, 3000)){
    Serial.println("Connection failed. Retrying...");
    delay(2000);
  }
  tempClient.println("GET /connect HTTP/1.1");
  tempClient.println("Host: 192.168.7.50");
  tempClient.println("Connection: close");
  tempClient.println();
//  if(client.connect(server, 3000)) {
//    Serial.println("connected");
//    // Make a HTTP request:
//    client.println("GET /connect HTTP/1.1");
//    client.println("Host: 192.168.7.50");
//    client.println("Connection: close");
//    client.println();
//  } else {
//    // if you didn't get a connection to the server:
//    Serial.println("connection failed");
//  }
}

void loop() {
//  for(int i = 0; i < sizeof(message); i++){
//    playCharacter(message[i]);
//  }

//  if (client.available()) {
//    char c = client.read();
//    Serial.print(c);
//  }
//
//  // if the server's disconnected, stop the client:
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
//
//    // do nothing forevermore:
//    while (true);
//  }
     // an http request ends with a blank line
    
    if (tempClient.available()) {
      char c = client.read();
      //Serial.write(c);
      // if you've gotten to the end of the line (received a newline
      // character) and the line is blank, the http request has ended,
      // so you can send a reply
      if(c == '}'){
        inJson = false;
        Serial.println("JSON: " + response);
        tempClient.stop();
      }
      
      if(inJson){
        response = response + c;
      }
      
      if(c == '{'){
        inJson = true;
      }
      
      if (c == '\n' && currentLineIsBlank) {
        // send a standard http response header
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        
      }
      if (c == '\n') {
        // you're starting a new line
        currentLineIsBlank = true;
      } else if (c != '\r') {
        // you've gotten a character on the current line
        currentLineIsBlank = false;
      }
    }

    // Server stuff
    EthernetClient client = server.available();
    if (client) {
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();

          if(c == '}'){
            inJson = false;
            Serial.println("JSON: " + response);
          }
      
          if(inJson){
            response = response + c;
          }
      
          if(c == '{'){
            inJson = true;
          }
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          if (c == '\n' && currentLineIsBlank) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");  // the connection will be closed after completion of the response
            client.println();
            break;
          }
          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          } else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
        }
      }
      // give the web browser time to receive the data
      delay(1);
      // close the connection:
      client.stop();
      Serial.println("client disconnected");
    }
}

String formatMessage(String message){ 
  char arr[message.length()+1];
  message.toCharArray(arr, message.length() + 1);
  for(int i = 0; i < sizeof(arr); i++){
    char character = arr[i];
    if((character < 65 || character > 122 || (character > 90 && character < 97)) && character != 32){
      arr[i] = '_';
      continue;
    } 
    if(character == 32) {
      continue;
    }
    if(character < 91){
      arr[i] = character + 32;
    }
  } 
  return String(arr);
}

void playCharacter(char character){
  // fix upper/lower case
  switch(character){
   case 'a':
      dot();
      dash();
      break; 
   case 'b':
      dash();
      dot();
      dot();
      dot();
      break; 
   case 'c':
      dash();
      dot();
      dash();
      dot();
      break; 
   case 'd':
      dash();
      dot();
      dot();
      break; 
   case 'e':
      dot();
      break; 
   case 'f':
      dot();
      dot();
      dash();
      dot();
      break; 
   case 'g':
      dash();
      dash();
      dot();
      break; 
   case 'h':
      dot();
      dot();
      dot();
      dot();
      break; 
   case 'i':
      dot();
      dot();
      break; 
   case 'j':
      dot();
      dash();
      dash();
      dash();
      break; 
   case 'k':
      dash();
      dot();
      dash();
      break; 
   case 'l':
      dot();
      dash();
      dot();
      dot();
      break; 
   case 'm':
      dash();
      dash();
      break; 
   case 'n':
      dash();
      dot();
      break; 
   case 'o':
      dash();
      dash();
      dash();
      break; 
   case 'p':
      dot();
      dash();
      dash();
      dot();
      break;
   case 'q':
      dash();
      dash();
      dot();
      dash();
      break; 
   case 'r':
      dot();
      dash();
      dot();
      break; 
   case 's':
      dot();
      dot();
      dot();
      break; 
   case 't':
      dash();
      break; 
   case 'u':
      dot();
      dot();
      dash();
      break; 
   case 'v':
      dot();
      dot();
      dot();
      dash();
      break; 
   case 'w':
      dot();
      dash();
      dash();
      break; 
   case 'x':
      dash();
      dot();
      dot();
      dash();
      break;
   case 'y':
      dash();
      dot();
      dash();
      dash();
      break;
   case 'z':
      dash();
      dash();
      dot();
      dot();
      break;
   case ' ':
     delay(BETWEEN_WORDS);
     break;
   default:
     return;
   delay(BETWEEN_LETTER);
  }
}

void dash(){
  tone(SPEAKER_IN, BUZZ);
  delay(DASH);
  noTone(SPEAKER_IN);
  delay(BETWEEN_CHARACTER);
}

void dot(){
  tone(SPEAKER_IN, BUZZ);
  delay(DOT);
  noTone(SPEAKER_IN);
  delay(BETWEEN_CHARACTER);
}

void printIPAddress(){
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}


