#Criptografia de Transposição

Na criptografia clássica, uma cifra de transposição procede à mudança de cada letra (ou outro qualquer símbolo) no texto a cifrar para outro (sendo a decifração efectuada simplesmente invertendo o processo). Ou seja, a ordem dos caracteres é mudada. Matematicamente trata-se da aplicação de uma função bijectiva para cifrar e da respectiva função inversa para decifrar.

No terminal: ./main [opção] [arquivo de entrada] [arquivo de sada] [offset]

Opções: C - Criptografar D - Decriptografar

Ex:

./main c /Users/home/Developer/SAS/examplefile.txt /Users/home/Developer/SAS/exampleEncrypted.txt
./main c /Users/home/Developer/SAS/exampleEncrypted.txt /Users/home/Developer/SAS/exampleDencrypted.txt
