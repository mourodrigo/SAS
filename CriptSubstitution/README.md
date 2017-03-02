# Cifra de substituição

Em criptografia, uma cifra de substituição é um método de criptografia que opera de acordo com um sistema pré-definido de substituição. Para criptografar uma mensagem, unidades do texto - que podem ser letras isoladas, pares ou outros grupos de letras - são substituídas para formar a cifra. As cifras de substituição são decifradas pela substituição inversa. Todavia, se a unidade de substituição estiver ao nível de palavras inteiras ou frases, como PORTA-AVIÕES ou ATAQUE ÀS 06H20M, o sistema é habitualmente dito ser um código, não uma cifra.

Uma cifra de substituição contrasta com uma cifra de transposição. Nestas últimas, as unidades do texto a cifrar são rearranjadas numa ordem diferente e habitualmente complexa, mas não modificadas. Por contraste, numa cifra de substituição, as unidades do texto são mantidas na mesma ordem, mas elas próprias são alteradas.

No terminal: ./main [opção] [arquivo de entrada] [arquivo de sada] [offset]

Opções: C - Criptografar D - Decriptografar

Ex:

./main c /Users/home/Developer/SAS/examplefile.txt /Users/home/Developer/SAS/exampleEncrypted.txt
./main c /Users/home/Developer/SAS/exampleEncrypted.txt /Users/home/Developer/SAS/exampleDencrypted.txt
