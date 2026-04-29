Este projeto foi criado como parte do
currículo da 42 por <dapinhei> Danilo Pinheiro, <ranhaia-> Renato Anhaia Flud Pacheco

# cub3D - Descrição

Implementação de um motor gráfico simples em C baseado em **raycasting**, inspirado em jogos como *Wolfenstein 3D*.
O projeto foi desenvolvido utilizando a **MiniLibX**, com foco em parsing robusto, validação de mapa e gerenciamento correto de memória.

---

##  Objetivo

Renderizar um ambiente 3D a partir de um mapa 2D (`.cub`), permitindo movimentação do jogador, colisão com paredes e interação básica.
* Flood fill (verificação de mapa fechado)
* Gerenciamento manual de memória
* Manipulação de eventos (teclado e mouse)

---


---

##	Instruções:

##  Tecnologias utilizadas

* Linguagem: C
* Biblioteca gráfica: MiniLibX
* Sistema: Linux
* Ferramentas:

  * Valgrind (análise de memória)
  * Norminette (padronização de código)

---

##  Conceitos aplicados

* Raycasting (projeção 3D a partir de mapa 2D)
* Parsing de arquivos
* Validação estrutural de dados
* Flood fill (verificação de mapa fechado)
* Gerenciamento manual de memória
* Manipulação de eventos (teclado e mouse)

---

##  Estrutura do projeto

```
.
├── main.c
├── parse/
│   ├── parse.c
│   ├── parse_map.c
│   ├── parse_texture.c
│   ├── parse_color.c
│   ├── validate_map.c
│   └── parse_utils.c
├── raycasting.c
C 225,30,0
```

### Mapa

```
111111
100001
├── player.c
├── textures.c
├── draw_utils.c
├── map.c
├── includes/
│   ├── mlx/
│   ├── libft/
│   └── get_next_line/
└── maps/
```

---

##  Formato do mapa (.cub)

O arquivo `.cub` contém:

### Texturas

```
NO ./path_to_texture
SO ./path_to_texture
WE ./path_to_texture
EA ./path_to_texture
```

### Cores

```
F 220,100,0
C 225,30,0
```

### Mapa

```
111111
100001
10N001
111111
```

---

##  Parser

O parser foi dividido em duas etapas:

### 1. Leitura

* Identificação de linhas de textura, cor e mapa
* Armazenamento dinâmico das linhas

### 2. Validação

* Cálculo de dimensões (`width`, `height`)
* Normalização do mapa (retangular)
* Validação de caracteres
* Verificação de player único
* **Flood fill** para garantir mapa fechado

---

##  Validação do mapa

O projeto utiliza **flood fill** a partir da posição do jogador:

* Se atingir:

  * borda do mapa
  * espaços (`' '`)
    → o mapa é considerado inválido

Isso evita:

* vazamentos
* mapas abertos
* buracos internos

---

##  Controles

| Tecla | Ação            |
| ----- | --------------- |
| W / S | Frente / trás   |
| A / D | Strafe          |
| ← / → | Rotação         |
| Mouse | Rotação (bonus) |
| F     | Interação       |
| ESC   | Sair            |

---

##  Raycasting

Para cada coluna da tela:

1. Um raio é lançado no mapa
2. Calcula interseções horizontais e verticais
3. Determina a distância até a parede
4. Corrige efeito de distorção (fish-eye)
5. Renderiza a parede com textura

---

##  Gerenciamento de memória

* Todos os caminhos de erro possuem liberação adequada
* `error_exit_parser` garante cleanup completo
* Testado com **Valgrind**

Resultado:

```
All heap blocks were freed -- no leaks are possible
```

---

## ▶ Como executar

### Compilar

```bash
make
make bonus
```

### Executar

```bash
./cub3D maps/map.cub
```

---Autores

Danilo Pinheiro
Renato Anhaia Flud Pacheco

##  Testes

* Mapas válidos e inválidos
* Casos de erro no parser
* Validação estrutural do mapa
* Análise de memória com Valgrind

---

##  Limitações

* Não possui sistema avançado de iluminação
* Performance não otimizada paraAutores

Danilo Pinheiro
Renato Anhaia Flud Pacheco mapas grandes

---

##  Conclusão

O projeto cumpre os requisitos do cub3D com:

* Parser robusto e seguro
* Validação completa de mapa
* Renderização funcional em tempo real
* Gerenciamento correto de memória

---

## Recursos

### Referências utilizadas

* Lode's Computer Graphics Tutorial (Raycasting)
* Permadi Raycasting Tutorial
* Documentação da MiniLibX
* Subject do cub3D (42 School)
* Man pages do Linux

---

### Uso de Inteligência Artificial

A IA foi utilizada como ferramenta de apoio durante o desenvolvimento, auxiliando principalmente em:

* Correção de bugs, indicando possíveis pontos de falha na lógica
* Revisão de código, sugerindo melhorias em trechos repetitivos
* Apoio na identificação de problemas de implementação

Todas as decisões finais, implementação e entendimento do código foram realizados manualmente.

Renato Anhaia Flud Pacheco
