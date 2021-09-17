package main

import (
	"encoding/base64"
	"fmt"
)

//const data = `abcd`

func main() {
  var data string
  fmt.Printf("Enter the string to encode:")
  fmt.Scanf("%s", &data)
	//encoding := base64.StdEncoding
  str := base64.StdEncoding.EncodeToString([]byte(data))
  fmt.Println(str)
	//encoded := make([]byte, encoding.EncodedLen(len(data)))
	//encoding.Encode(encoded, []byte(data))
	//fmt.Printf("%s", encoded)

}
