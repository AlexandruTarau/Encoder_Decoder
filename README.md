# Encoder_Decoder

## Short Description
Encoder_Decoder is a program that can encode or decode any string in 2 ways:
  - CodificareA(EncodingA): uses a matrix where we will store a key on the first line. The text to be encoded is stored starting from the 2nd line (the last line can be completed with ' ' if the text is too short). We use "selection sort" to interchange the columns in ascending order after the key's letters. We put together each column from left to right and we get the encoded text.
  - CodificareB(EncodingB): the key (nr) here is the number of characters we want to encode from right to left (example: text="My cat has 2 kittens.", nr=10 => text_to_encode="2 kittens." | last nr characters). Then for each char we add nr and cycle its value until it's again in ASCII code.
