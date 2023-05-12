<h1 align="center">Chessey</h1>
<p align="center">Xadrez em linha de comando com C</p>

![Chessey](https://github.com/nadjiel/chessey/assets/97067805/a4b6ac74-50ef-47f7-998f-4e881adc4315)

## ♟️ Sobre
Chessey foi um projeto feito em uma GameJam informal entre eu e meu irmão [@DaveJosef](https://github.com/DaveJosef).

O prazo da competição foi de aproximadamente 1 mês e os jogos tinham que atender as condições de serem preto e branco e não terem sons.

Esse foi o primeiro jogo que fiz. Na época estava no primeiro período da faculdade de Análise e Desenvolvimento de Sistemas, aprendendo a linguagem de programação C.

O jogo é feito para ser jogado por dois jogadores em uma mesma máquina, o jogador 1 controlando as peças brancas (representadas pelo número 1), e o jogador 2, as peças pretas (representadas pelo número 2).

## 🎮 Como jogar
No começo do jogo é pedido que se informe os nicknames dos jogadores, primeiro o 1, depois o 2. Depois disso, a partida começa.

Para interagir com o jogo usa-se um sistema de endereços - combinações de uma letra e um número (por exemplo **a2**, onde começa o primeiro Peão preto da esquerda para direita, ou **e8**, onde começa o Rei branco), então para realizar os movimentos das peças os jogadores serão perguntados qual o endereço de origem e de destino da peça a qual desejam mover.

Para representar as peças, o jogo utiliza dois caracteres: uma letra e um número. A letra indica qual é a peça e o número indica qual é o jogador dono dela, o jogador branco ou o preto.
A seguir estão os significados das letras que representam as peças:

- **p**: Peão;
- **t**: Torre;
- **c**: Cavalo;
- **b**: Bispo;
- **D**: Dama ou Rainha;
- **R**: Rei.

Assim, como exemplo, pode-se dizer que a peça **D1** é a Rainha do jogador branco e a peça **c2** é um dos cavalos do jogador preto.

Ademais, para representar casas vazias no tabuleiro, são usadas duas underlines.

### Eventos especiais
A seguir estão descritos alguns eventos especiais que podem ocorrer no jogo e como lidar com eles:

- Captura en-passant: Para realizar uma captura en-passant basta mover o peão capturador para o endereço o qual o peão que será capturado pulou ao andar duas casas consecutivas.

- Roque: Já para realizar um roque, deve-se mover o Rei duas casas em direção a Torre com a qual se deseja realizar tal movimento. Com isso a torre automaticamente vai realizar seu movimento também.

- Promoção: Quando um peão chega na extremidade oposta do tabuleiro, ele poderá realizar uma promoção. O jogo perguntará em qual peça o peão deverá se transformar. Nesse momento o jogador em questão deve responder com **t** (Torre), **c** (Cavalo), **b** (Bispo) ou **D** (Dama), que são as pessas disponíveis para a promoção.

## 👇 Instalação
Se você quiser experimentar o jogo, pode baixar a versão 64bit para Windows por meio do executável das releases do projeto aqui no Github (a [release v2.0.0](https://github.com/nadjiel/chessey/releases/tag/v2.0.0) compreende a versão completa), ou compilar o código fonte você mesmo se estiver em outro sistema operacional.

## ✍️ Autor
Este projeto foi desenvolvido com ❤️ por [@Nadjiel](https://github.com/nadjiel)
