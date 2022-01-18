#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void decodeblock(unsigned char in[], char *clrstr) {
  char out[4];
  out[0] = in[0] << 2 | in[1] >> 4;
  out[1] = in[1] << 4 | in[2] >> 2;
  out[2] = in[2] << 6 | in[3] >> 0;
  out[3] = '\0';
  strncat(clrstr, out, strlen(out));
}

void b64_decode(char *b64src, char *clrdst) {
  int c, phase, i;
  unsigned char in[4];
  char *p;

  clrdst[0] = '\0';
  phase = 0; i=0;
  while(b64src[i]) {
    c = (int) b64src[i];
    if(c == '=') {
      decodeblock(in, clrdst);
      break;
    }
    p = strchr(b64, c);
    if(p) {
      in[phase] = p - b64;
      phase = (phase + 1) % 4;
      if(phase == 0) {
        decodeblock(in, clrdst);
        in[0]=in[1]=in[2]=in[3]=0;
      }
    }
    i++;
  }
}

/* encodeblock - encode 3 8-bit binary bytes as 4 '6-bit' characters */
void encodeblock( unsigned char in[], char b64str[], int len ) {
    char out[5];
    out[0] = b64[ in[0] >> 2 ];
    out[1] = b64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? b64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? b64[ in[2] & 0x3f ] : '=');
    out[4] = '\0';
    strncat(b64str, out, strlen(out));
}

/* encode - base64 encode a stream, adding padding if needed */
void b64_encode(char *clrstr, char *b64dst) {
  unsigned char in[3];
  int i, len = 0;
  int j = 0;

  b64dst[0] = '\0';
  while(clrstr[j]) {
    len = 0;
    for(i=0; i<3; i++) {
     in[i] = (unsigned char) clrstr[j];
     if(clrstr[j]) {
        len++; j++;
      }
      else in[i] = 0;
    }
    if( len ) {
      encodeblock( in, b64dst, len );
    }
  }
}

int main(int argc, char** argv) {
  if ((argc != 3) && ((strcmp(argv[1], "-e")!= 0) || (strcmp(argv[1], "--encode")!= 0) || (strcmp(argv[1], "-d")!= 0) || (strcmp(argv[1], "--decode")!= 0))) {
    printf("./base64 [OPTION] [string]\nUsage:\n\t-e --encode [string]--->encode a string\n\t-d --decode [string]--->decode a string \n\n");
    exit(0);
  }
  char mysrc[1024];
  char myb64[1024] = "";
  char mydst[1024] = "";
  if ((strcmp(argv[1], "-e")== 0) || (strcmp(argv[1], "--encode")== 0)) {
    strncpy(mysrc, argv[2], 1023);
    b64_encode(mysrc, myb64);
    printf("Your string:'%s' encodes into base64 as:'%s'\n", mysrc, myb64);
    printf("\n");

  } else {
    strncpy(mydst, argv[2], 1023);
    b64_decode(mydst, myb64);
    printf("Your string:'%s' decodes from base64 as:'%s'\n", mydst, myb64);

  }
  return 0;
}