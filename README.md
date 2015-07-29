#Segurança e Auditoria de Sistemas

### Algoritmo de Cesar
A [Cifra de César](https://pt.wikipedia.org/wiki/Cifra_de_C%C3%A9sar), também conhecida como cifra de troca, código de César ou troca de César, é uma das mais simples e conhecidas técnicas de criptografia. É um tipo de cifra de substituição na qual cada letra do texto é substituída por outra, que se apresenta no alfabeto abaixo dela um número fixo de vezes. Por exemplo, com uma troca de três posições, A seria substituído por D, B se tornaria E, e assim por diante. O nome do método é em homenagem a Júlio César, que o usou para se comunicar com os seus generais.

[https://github.com/mourodrigo/SAS/tree/master/CriptCesar/CriptCesar](https://github.com/mourodrigo/SAS/tree/master/CriptCesar/CriptCesar)

**Implementação.**
O código foi implementado em C++ utilizando bibliotecas string, fstream e iostream.

**Utilização.**
./main [opção] [caminho do arquivo de entrada] [caminho do arquivo de saida] [offset]

Opções: 
C - Criptografar
D - Decriptografar

Ex: 

./main c /Users/home/Developer/SAS/examplefile.txt /Users/home/Developer/SAS/exampleEncrypted.txt<br>
./main c /Users/home/Developer/SAS/exampleEncrypted.txt /Users/home/Developer/SAS/exampleDencrypted.txt
