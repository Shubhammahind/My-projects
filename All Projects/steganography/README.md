## Steganography

Developed a steganography tool for encoding and decoding hidden messages within images.
In this project we use Least Significant Bit (LSB) technique for embedding data.

## Feactures
- Encode text messages into images (BMP).
- Decode hidden message from the BMP image.
- Preserves image quality while hiding data using LSB(Least Significant Bit) technique

## How to Run
### 1. Encoding
./a.out -e beautiful.bmp secret.txt stego.bmp

### 2. Decoding
```bash
./a.out -d stego.bmp output.txt

