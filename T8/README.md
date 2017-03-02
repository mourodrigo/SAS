Mecanismo de geração de chaves para a cifra RSA:

xed = x (mod N)

Onde e é a chave de cifragem e d e’ a chave de decifragem.

Como xφ(N) = 1 (mod N)  (prova em [1]) segue que xφ(N) + 1 = x (mod N) 

Como xφ(N) + 1 = x (mod N) e xed = x (mod N), entao φ(N) + 1 = ed


Aplicando o modulo φ(N) em φ(N) + 1 = ed temos 1 = ed (mod φ(N)) 

Ou seja e e d são um número e seu inverso multiplicativo modulo φ(N)

Para calcular pares de números e e d:

[1]https://en.wikipedia.org/wiki/Proofs_of_Fermat%27s_little_theorem#Proofs_using_modular_arithmetic
[2]http://math.stackexchange.com/questions/192452/whats-the-proof-that-the-euler-totient-function-is-multiplicative/918043#918043
