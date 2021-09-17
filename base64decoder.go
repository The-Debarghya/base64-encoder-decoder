package main

import (
  "fmt"
  "log"
  "encoding/base64"
)

func main()  {
  encoding := base64.StdEncoding
  data := []byte(``)
  //for string decoding
  //var data string
  /*decoded, err := base64.StdEncoding.DecodeString(data)
	if err != nil {
		log.Fatal(err)
	}*/
  fmt.Printf("Enter base64 encoded data:")
  fmt.Scanf("%s", &data)
  decoded := make([]byte, encoding.DecodedLen(len(data)))
	n, err := encoding.Decode(decoded, data)
	if err != nil {
		log.Fatal(err)
	}
  decoded = decoded[:n]
	fmt.Println("`%s`", decoded)
}
